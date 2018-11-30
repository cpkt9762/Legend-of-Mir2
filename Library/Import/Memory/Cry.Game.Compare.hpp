#pragma once
#include <Global>
#include <Helper>
#include <StringXor.h>
namespace Cry
{
	namespace Memory
	{
		class Masks
		{
		public:
			virtual ~Masks() = default;
		public:
			/// ������Դ��https://github.com/learn-more/findpattern-bench/blob/master/patterns/learn_more.h
			/// �޸����⣺������ĩβһ��������'\0'�����ڴ�����ʧ�ܵ������
			/// �Ż����ܣ�����int3�ϵ㡣
			/// �Ż��Ӿ������ڴ��Ժ���棬���������Զ�չ����
			/// ���˹۵㣺����˵��û�м����õĴ��롢�����������Ҽ�����������ڴ�������ʽ�ˡ�
			static u32 Execution(const u32 uBeginAddress, const u32 uEndAddress, lPCString lpszMasks, u32 uPos)
			{
				const char*		pbSearchBuffer		= lpszMasks;
				u8*				uResult				= 0;
				u32				Pos					= 0;
				ulong32			lpflOldProtect		= 0;
				ulong32			lpflNewProtect		= 0;
				u32				uProtceSize			= (uEndAddress - uBeginAddress);
				__try
				{
					if (VirtualProtectEx(INVALID_HANDLE_VALUE, reinterpret_cast<LPVOID>(uBeginAddress), uProtceSize, PAGE_EXECUTE_READWRITE, &lpflNewProtect))
					{
						for (u8 * pCur = reinterpret_cast<u8*>(uBeginAddress); pCur < reinterpret_cast<u8*>(uEndAddress); ++pCur)
						{
							if (*pCur == 0xCC || *pCur == 0x90)
							{
								continue;
							}
							if (CryVirtualQueryMemory(uint8_t, pbSearchBuffer) == ((u8)'\?') || *pCur == getByte(pbSearchBuffer))
							{
								if (!uResult)
								{
									uResult = pCur;
								}
								if (pbSearchBuffer += (CryVirtualQueryMemory(u16, pbSearchBuffer) == ((u16)'\?\?') || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) != ((u8)'\?')) ? 3 : 2; (!*pbSearchBuffer) || (!*(pbSearchBuffer - 1)) || (!*(pbSearchBuffer + 1)))
								{
									if (++Pos == uPos)
									{
										break;
									}
									else
									{
										continue;
									}
								}
							}
							else if (uResult)
							{
								pCur = uResult;
								pbSearchBuffer = lpszMasks;
								uResult = 0;
							}
						}
						if (!VirtualProtectEx(INVALID_HANDLE_VALUE, reinterpret_cast<LPVOID>(uBeginAddress), uProtceSize, lpflNewProtect, &lpflOldProtect))
						{
							DebugMsg("�ڴ��������ó��ִ���:%d\n", GetLastError());
							return 0;
						}
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
					DebugMsg("�����ڴ�����쳣\n");
				}
				return reinterpret_cast<u32>(uResult);
			}
			static u32 SearchMemory(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 uPos = 1)
			{
				return Execution(uBeginAddress, uEndAddress, Cry::Encrypt::Xor::Operate(lpszMasks).c_str(), uPos);
			}
			static u32 SearchMemoryEx(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 Offset = 0, u32 uPos = 1)
			{
				return Cry::Encrypt::Xor::Operate(CryVirtualQueryMemory(u32, Execution(uBeginAddress, uEndAddress, Cry::Encrypt::Xor::Operate(lpszMasks).c_str(), uPos) + Offset));
			}
		private:
			Masks() = default;
			Masks(const Masks &) = default;
			Masks &operator=(const Masks &) = default;
		};
	};
};