#if !defined(_HELPER_HEAD_)
/* Star */
#define _HELPER_HEAD_
#pragma once
// 公共帮助
#if !defined(_DEBUG)
	# define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#else
	# define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#endif
// 读写内存
# define CryWrite(_Type, x) *reinterpret_cast<_Type *>(const_cast<_Type>(x))
# define CryRead(t, x)  *reinterpret_cast<_Type *>(const_cast<_Type>(x))

#define MetaType(_Type) qRegisterMetaType<_Type>(#_Type);

/* End */
#endif