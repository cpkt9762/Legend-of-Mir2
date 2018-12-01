#pragma once
namespace Cry
{
	class DetourEngine;
	namespace Base
	{
		class DataBase;
	};
	namespace Game
	{
		class InterfaceEx;
		using lPInterfaceEx = InterfaceEx *;

		class Reflection
		{
		public:
			Reflection(lPInterfaceEx Interface);
			~Reflection();
		public:
		public:
			void VirtualTimerCallbackEx();
			void VirtualTimerCallback();
		private:
			lPInterfaceEx															m_InterfaceEx;
		private:
			Reflection() = default;
		};
		typedef Reflection * lPReflection;
	};
};