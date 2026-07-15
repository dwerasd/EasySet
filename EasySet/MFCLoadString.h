#pragma once


#include <afxstr.h>
#include <stdarg.h>





namespace mfc
{
	CStringA _LoadStringA(unsigned int _nId, ...);
	CStringW _LoadStringW(unsigned int _nId, ...);
}
