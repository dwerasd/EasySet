// EasySetDlg.h : 헤더 파일
//

#pragma once


#include <afxwin.h>



// CEasySetDlg 대화 상자
class CEasySetDlg : public CDialog
{
private:
	typedef int ( __stdcall *LoadStringA_PROC)(
		__in_opt HINSTANCE hInstance
		, __in UINT uID
		, __out_ecount(cchBufferMax) LPSTR lpBuffer
		, __in int cchBufferMax
	);
	LoadStringA_PROC pLoadStringA;
	typedef int (__stdcall *LoadStringW_PROC)(
		__in_opt HINSTANCE hInstance
		, __in UINT uID
		, __out_ecount(cchBufferMax) LPWSTR lpBuffer
		, __in int cchBufferMax
	);
	LoadStringW_PROC pLoadStringW;

	typedef HMODULE (__stdcall *LoadLibraryW_PROC)( __in LPCWSTR lpLibFileName );
	LoadLibraryW_PROC pLoadLibraryW;

	typedef HMODULE (__stdcall *GetModuleHandleW_PROC)( __in LPCWSTR lpModuleName );
	GetModuleHandleW_PROC pGetModuleHandleW;

	typedef BOOL (__stdcall *GetUserNameW_PROC) (LPWSTR , LPDWORD );
	GetUserNameW_PROC pGetUserNameW;

	typedef DWORD (__stdcall *NetUserChangePassword_PROC) (LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);
	NetUserChangePassword_PROC pNetUserChangePassword;

	void InitFunc();
	void GetAdapterList();

// 생성입니다.
public:
	CEasySetDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EASYSET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPrinterIp();
	afx_msg void OnBnClickedStart();
	CComboBox comboAdapters;
	afx_msg void OnHeloInfo();
};
