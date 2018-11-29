#pragma once
#include <string>
#include <vector>
#include <unordered_map>
namespace Cry
{
	namespace Base
	{
		class DataBase
 		{
		public:
			using lPDataBase = DataBase;
			DataBase();
			~DataBase();
		public:
			// ��ʼ
			bool Initialize();
		public:
			// �������
			u32 Get(std::string Object);
		private:
			// �������������
			bool CheckSucess();
		public:
			lPDataBase & GetDataBase() { return *this; };
		public:
			std::unordered_map<std::string, u32>			m_PointerEx;
		};
	};
};