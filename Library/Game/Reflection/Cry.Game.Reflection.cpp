#include <Global>
#include <Game/Reflection/Cry.Game.Reflection.h>
#include <Game/Cry.Game.Interface.h>
#include <Game/Initialize/Cry.Game.Initialize.h>
namespace Cry
{
	namespace Game
	{
		extern thread_local lPReflection m_ConstThis = nullptr;
		Reflection::Reflection(lPInterfaceEx Interface) : m_InterfaceEx(Interface)
		{
			m_ConstThis = this;
		}
		Reflection::~Reflection()
		{

		}
		void Reflection::VirtualTimerCallbackEx()
		{
			DebugMsg("跳转中\n");
		}
		void ConstDeclspec Reflection::VirtualTimerCallback()
		{
			/// 0x00608CEE 原始地址
			/// 0x00608D24 发言地址
			/// ebp+0x0034 修改地址
			__asm
			{
				push    ebp
				mov     ebp, esp
				pushad
				pushfd
			}
			m_ConstThis->VirtualTimerCallbackEx();
			__asm
			{
				mov     eax, 0x00608D24
				mov     dword ptr ds : [ebp + 0x34], eax
				popfd
				popad
				mov     eax, 1
				mov     esp, ebp
				pop     ebp
				retn    0x0
			}
		}
	};
};