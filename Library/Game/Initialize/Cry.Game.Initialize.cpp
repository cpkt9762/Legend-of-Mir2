#include <Global>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
namespace Cry
{
	namespace Base
	{
		DataBase::~DataBase()
		{
			m_PointerEx.clear();
			DebugMsg("�ͷ�[%s]����\n", "Database");
		}
		bool DataBase::Initialize()
		{
			bool bSucess;

			try
			{
				///���ָ�� -> BE ? ? ? ? ? ? ? ? ? ? ? ? 8B 06 8B 08 FF ? ? ? ? 8B D0
				m_PointerEx.emplace(std::make_pair("\x82\x16\xAB\x4B\xB6\x05\xB5\x56\x00\x00", Cry::Memory::Masks::SearchMemoryEx(0x516000, 0x516FFF, "\x22\xF8\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x22\x9D\x50\x8B\x40\x85\x22\x9D\x50\x85\x40\xFB\x26\x9D\x5F\x82\x40\x82\x5F\x9D\x58\xFF\x40\xF9\x50\x00\x00")));
				///�ı�ָ�� -> 89 02 A1 ?? ?? ?? ?? 8B 56 ?? 8B 92
				m_PointerEx.emplace(std::make_pair("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00", Cry::Memory::Masks::SearchMemoryEx(0x516000, 0x516FFF, "\x58\x84\x40\x8D\x52\x9D\x21\x8C\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x22\x9D\x55\x8B\x40\x82\x5F\x9D\x58\xFF\x40\x84\x52\x00\x00")));

				
				bSucess = this->CheckSucess();
			}
			catch (std::exception & e)
			{
				DebugMsg("��ʼ���ݳ����쳣[%s]\n", e.what());
				bSucess = false;
				
			}
			return bSucess;
		}
		u32 DataBase::Get(std::string lpszObject)
		{
			try
			{
				if (!m_PointerEx.empty())
				{
					if (auto list = m_PointerEx.find(lpszObject); list != std::end(m_PointerEx))
					{
						return list->second;
					}
				}
				throw std::string("����[%s]ʧ��", Text::Xor::Operate(lpszObject).c_str());
			}
			catch (std::exception & e)
			{
				DebugMsg("�������ݳ����쳣[%s]\n", e.what());
			}
			return 0;
		}
		bool DataBase::CheckSucess()
		{
			bool bSucess = true;
			for (auto & [Object, Pointer] : m_PointerEx)
			{
				if (!Pointer)
				{
					DebugMsg("��Ϸ����[%s]��ʼʧ��\n", Text::Xor::Operate(Object).c_str());
					bSucess = false;
				}
				else
				{
					DebugMsg("��Ϸ����[%s]��ʼ�ɹ� [%p]\n", Text::Xor::Operate(Object).c_str(), Pointer);
				}
			}
			return bSucess;
		}
	};
};