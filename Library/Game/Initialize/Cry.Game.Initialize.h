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
			DataBase() = default;
			virtual ~DataBase();
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
			DataBase & GetDataBase() { return *this; };
		public:
			std::unordered_map<std::string, u32>			m_PointerEx;
		protected:
			DataBase(const DataBase &) = default;
			DataBase &operator=(const DataBase &) = default;
		};
	};
};