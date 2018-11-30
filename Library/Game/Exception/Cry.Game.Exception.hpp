#if !defined(_Exception_)
/* Star */
#define _Exception_
#pragma once
#include <string>
#include <Global>
namespace Cry
{
	namespace Game
	{
		/// ����򵥵��쳣��������������
		class Exception
		{
		public:
			Exception(const std::string & lpszString) : m_lpszString(lpszString)
			{

			};
			~Exception()
			{
				m_lpszString.clear();
			};
		public:
			static u32 ExceptionHandler(u32 dwExceptionCode)
			{
				u32 ExceptionCode = EXCEPTION_CONTINUE_SEARCH;
				switch (dwExceptionCode)
				{
				case EXCEPTION_ACCESS_VIOLATION:				DebugMsg("��д�ڴ��쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_DATATYPE_MISALIGNMENT:			DebugMsg("��������δ�����쳣��������룺%x\n", dwExceptionCode); break;
				case EXCEPTION_BREAKPOINT:						DebugMsg("�ж��쳣��������룺%x\n", dwExceptionCode); break;
				case EXCEPTION_SINGLE_STEP:						DebugMsg("�����ж��쳣��������룺%x\n", dwExceptionCode); break;
				case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:			DebugMsg("����Խ���쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_FLT_DENORMAL_OPERAND:
				case EXCEPTION_FLT_DIVIDE_BY_ZERO:
				case EXCEPTION_FLT_INEXACT_RESULT:
				case EXCEPTION_FLT_INVALID_OPERATION:
				case EXCEPTION_FLT_OVERFLOW:
				case EXCEPTION_FLT_STACK_CHECK:
				case EXCEPTION_FLT_UNDERFLOW:					DebugMsg("�����������쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_INT_DIVIDE_BY_ZERO:				DebugMsg("��0���쳣��������룺%x\n", dwExceptionCode);					ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_INT_OVERFLOW:					DebugMsg("��������쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_IN_PAGE_ERROR:					DebugMsg("ҳ�����쳣��������룺%x\n", dwExceptionCode);					ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_ILLEGAL_INSTRUCTION:				DebugMsg("�Ƿ�ָ���쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_STACK_OVERFLOW:					DebugMsg("��ջ����쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_INVALID_HANDLE:					DebugMsg("��Ч�䲡�쳣��������룺%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				default:
				{
					if (dwExceptionCode & (1 << 29))
						DebugMsg("�Զ��������쳣��������룺%x\n", dwExceptionCode);
					else
						DebugMsg("�����쳣��������룺%x\n", dwExceptionCode);
					break;
				}
				}
				// 
				return ExceptionCode;
			}
			std::string & Info() { return m_lpszString; };
		private:
			std::string				m_lpszString;
		};
	};
};
#endif