#pragma once
#if !defined(_Tag_)
#define _Tag_
#pragma once
#include <Port>
typedef struct tagString
{
	i32			StringSize;
	String		lpszString[MAX_PATH];
}*lPtagString;
#endif