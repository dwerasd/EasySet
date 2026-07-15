#include "stdafx.h"
#include "MFCLoadString.h"



namespace mfc
{
	CStringA _LoadStringA(unsigned int _nId, ...)
	{
		CStringA sID;

		sID.LoadString(_nId);
		va_list vl;

		va_start( vl, _nId );     /* Initialize variable arguments. */

		CStringA sMsg;
		sMsg.FormatV( sID, vl );
		va_end( vl );              /* Reset variable arguments.      */

		return sMsg;
	}

	CStringW _LoadStringW(unsigned int _nId, ...)
	{
		CStringW sID;

		sID.LoadString(_nId);
		va_list vl;

		va_start( vl, _nId );     /* Initialize variable arguments. */

		CStringW sMsg;
		sMsg.FormatV( sID, vl );
		va_end( vl );              /* Reset variable arguments.      */

		return sMsg;
	}
}
