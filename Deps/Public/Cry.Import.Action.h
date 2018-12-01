#if !defined(_Action_)
#define _Action_
#pragma once
#include <Port>
namespace Cry
{
	namespace Action
	{
		enum
		{
			基本设置 = 1 << 0,
			保护设置 = 1 << 1,
			发言设置 = 1 << 2,
			加速设置 = 1 << 3,
			职业设置 = 1 << 4,
		};
		enum
		{
			发送文本 = 1000,
			超级不卡 = 1001,
			攻击不卡 = 1002,
			移动不卡 = 1003,
			魔法不卡 = 1004,
			开启保护 = 1005,
		};
	};
};
#endif