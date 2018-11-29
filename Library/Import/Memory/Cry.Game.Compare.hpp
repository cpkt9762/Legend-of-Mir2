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
			static u32 SearchMemory(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 uPos)
			{
				const char*		pbSearchBuffer	= lpszMasks.data();
				u8*				uResult			= 0;
				u32				Pos				= 0;
				try
				{
					for (u8 * pCur = reinterpret_cast<u8*>(uBeginAddress); pCur <reinterpret_cast<u8*>(uEndAddress); ++pCur)
					{
						if (*pCur != 0xCC && CryVirtualQueryMemory(uint8_t, pbSearchBuffer) == ((u8)'\?') || *pCur == getByte(pbSearchBuffer))
						{
							if (!uResult)
							{
								uResult = pCur;
							}

							if (pbSearchBuffer += (CryVirtualQueryMemory(u16, pbSearchBuffer) == ((u16)'\?\?') || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) != ((u8)'\?')) ? 3 : 2; (!*pbSearchBuffer) || (!*(pbSearchBuffer - 1)) || (!*(pbSearchBuffer + 1)))
							{
								if (++Pos == uPos)
								{
									return reinterpret_cast<u32>(uResult);
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
							pbSearchBuffer = lpszMasks.data();
							uResult = 0;
						}
					}
				}
				catch (std::exception & e)
				{
					DebugMsg("�����ڴ�����쳣[%s]\n", e.what());
				}
				return 0;
			}
			static u32 SearchMemoryEx(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 uPos = 1)
			{
				return SearchMemory(uBeginAddress, uEndAddress, Cry::Text::Xor::Operate(lpszMasks), uPos);
			}
		private:
			Masks() = default;
			Masks(const Masks &) = default;
			Masks &operator=(const Masks &) = default;
		};
	};
};