#pragma once
#include <memory>
#include <string>
namespace Cry
{
	class DetourEngine;
	namespace Base
	{
		class DataBase;
	};
	namespace Game
	{
		class Reflection;
		///*********************************************************************************************************///
		///*********************************************************************************************************///
		class Interface
		{
		public:
			Interface(std::shared_ptr<Base::DataBase> & DataBase);
			~Interface();
		public:
			u32 GetPointer(lPCString lpszString);
		private:
			std::shared_ptr<Base::DataBase>								m_DataBase;
		protected:
			Interface() = default;
			Interface(const Interface &) = default;
			Interface &operator=(const Interface &) = default;
		};
		///*********************************************************************************************************///
		///*********************************************************************************************************///
		class InterfaceEx
		{
		public:
			friend class Reflection;
		public:
			InterfaceEx(std::shared_ptr<Base::DataBase> & DataBase);
			~InterfaceEx();
		public:
			bool SendCmd(lPString lpszString);
		private:
			HANDLE														m_lpEventHandles;
		private:
			std::shared_ptr<Base::DataBase>								m_DataBase;
			std::shared_ptr<Game::Interface>							m_Interface;
			std::shared_ptr<DetourEngine>								m_DetourEngine;
			std::shared_ptr<Reflection>									m_Reflection;
		protected:
			InterfaceEx() = default;
			InterfaceEx(const InterfaceEx &) = default;
			InterfaceEx &operator=(const InterfaceEx &) = default;
		};
		typedef InterfaceEx* lPInterfaceEx;
		///*********************************************************************************************************///
		///*********************************************************************************************************///
	};
};