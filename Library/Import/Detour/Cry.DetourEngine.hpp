#pragma once
#include <Global>
#include <functional>
#include <unordered_map>
#include <Detours.h>
namespace Cry
{
	class DetourEngine
	{
	public:
		DetourEngine() = default;
		~DetourEngine()
		{
			if (this->UninstallHookFunc())
			{
				m_DataBase.clear();
			}
			else
			{
				DebugMsg("ж��DetourEngine����\n");
			}
		}
	public:
		using lPointer = void *;
		struct tag
		{
			/// _Ty1
			lPointer ppPointer;
			/// _Ty2
			lPointer pDetour;
		};
	public:
		/// ����1��ǿ����ֵ[��]
		/// ����2��ǿ����ֵ[��]
		/// ����3����α���
		template<typename _Ty1, typename _Ty2, class... _Types>
		constexpr auto InstallHookFunc(const std::string & lpszDefined, _Ty1 && ppPointer, _Ty2 && pDetour, _Types &&... _Args)
		{
			if (bool bSucess = true)
			{
				if (bSucess &= this->Execution(ppPointer, pDetour); bSucess)
				{
					m_DataBase.emplace(std::make_pair(lpszDefined, tag{ std::move((*&(lPointer&)ppPointer)), std::move(*&(lPointer&)(std::bind(std::forward<_Ty2>(pDetour), std::forward<_Types>(_Args)...))) }));
					return bSucess;
				}
				else
				{
					DebugMsg("��װ[%s]ʱ���ֹ���\n", lpszDefined.c_str());
				}
			}
			return false;
		}
		/// ж������Hook
		bool UninstallHookFunc()
		{
			auto bSucess = true;
			for (auto &[m_lpszDefined, m_Tag] : m_DataBase)
			{
				if (m_Tag.ppPointer && m_Tag.pDetour)
				{
					bSucess &= this->Execution(m_Tag.pDetour, m_Tag.ppPointer);
				}
				else
				{
					/// ж�� m_lpszDefined ʧ��
					bSucess &= false;
					break;
				}
			}
			return bSucess;
		}
		/// ж��ĳһ��Hook
		bool UninstallHookFunc(const std::string & lpszDefined)
		{
			auto bSucess = true;
			for (auto &[m_lpszDefined, m_Tag] : m_DataBase)
			{
				if (m_lpszDefined == lpszDefined && m_Tag.ppPointer && m_Tag.pDetour)
				{
					bSucess &= this->Execution(m_Tag.pDetour, m_Tag.ppPointer);
				}
				else
				{
					/// ж�� m_lpszDefined ʧ��
					bSucess &= false;
					break;
				}
			}
			return bSucess;
		}
	protected:
		bool Execution(lPointer _Ty1, lPointer _Ty2)
		{
			auto bSucess = true;
			bSucess &= !DetourTransactionBegin();
			bSucess &= !DetourUpdateThread(GetCurrentThread());
			bSucess &= !DetourAttach(std::move((&(PVOID&)(_Ty1))), std::move(_Ty2));
			bSucess &= !DetourTransactionCommit();
			return bSucess;
		}
	private:
		std::unordered_map<std::string, tag>											m_DataBase;
	};
};