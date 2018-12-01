#include <Global>
#include <Import/Cry.Game.Tag.h>
#include <Game/Cry.Game.Interface.h>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <Game/Reflection/Cry.Game.Reflection.h>
#include <StringXor.h>
#include <Exception/Cry.Exception.hpp>
#include <Import/Detour/Cry.DetourEngine.hpp>
namespace Cry
{
	namespace Game
	{
		Interface::Interface(std::shared_ptr<Base::DataBase> & DataBase) : m_DataBase(DataBase)
		{

		}
		Interface::~Interface()
		{
			
		}
		u32 Interface::GetPointer(lPCString lpszString)
		{
			try
			{
				return m_DataBase->Get(lpszString);
			}
			catch (std::string & lpszExceptionString)
			{
				DebugMsg("%s:%s\n", __FUNCTION__, lpszExceptionString.c_str());
			}
			catch(Cry::Exception & ex)
			{
				DebugMsg("%s:%s\n", __FUNCTION__, ex.lpszString());
			}
			return 0;
		}
		InterfaceEx::InterfaceEx(std::shared_ptr<Base::DataBase> & DataBase) : 
			m_Interface(std::make_shared<Game::Interface>(DataBase)), 
			m_DataBase(DataBase), 
			m_DetourEngine(std::make_unique<DetourEngine>()),
			m_Reflection(std::make_unique<Reflection>(this))
		{
			m_lpEventHandles = CreateEvent(NULL, FALSE, FALSE, "Global\\Interface");
			CryVirtualQueryMemory(lPVoid, CryVirtualQueryMemory(u32, m_Interface->GetPointer("\x82\x16\xAB\x4B\xB6\x05\xB5\x56\x00\x00")) + 0x620) = *(&(lPVoid&)std::bind(&Reflection::VirtualTimerCallback));
		}
		InterfaceEx::~InterfaceEx()
		{
			m_DataBase = nullptr;
			m_Interface.reset();
			m_DetourEngine.reset();
			m_Reflection.reset();
		}
		
		bool InterfaceEx::SendCmd(lPString lpszString)
		{
			__try
			{
				thread_local static tagString TemptagString = { lstrlen(lpszString) };
				// 发言
				CryVirtualQueryMemory(lPCString, CryVirtualQueryMemory(u32, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00"))) = reinterpret_cast<lPString>(CopyMemory(reinterpret_cast<lPString>(&TemptagString.lpszString), lpszString, TemptagString.StringSize));
				/*
				switch (MsgWaitForMultipleObjects(1, &m_lpEventHandles, FALSE, -1, QS_ALLINPUT))
				{
				case WAIT_OBJECT_0 + 0: break;
				case WAIT_OBJECT_0 + 1: break;
				case WAIT_OBJECT_0 + 2: break;
				case WAIT_TIMEOUT: DebugMsg("向系统发送命令造成超时\n"); break;
				default: break;
				}
				*/
				// 结束
				//CryVirtualQueryMemory(lPtagString, CryVirtualQueryMemory(u32, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00"))) = 0;
				//CryVirtualQueryMemory(lPVoid, CryVirtualQueryMemory(u32, m_Interface->GetPointer("\x82\x16\xAB\x4B\xB6\x05\xB5\x56\x00\x00")) + 0x620) = 0;
			}
			__except (Cry::Exception::ExceptionHandler(GetExceptionCode()))
			{
				DebugMsg("Structured Exception Handling -> %s\n", __FUNCTION__);
			}
			return true;
		}
	};
};