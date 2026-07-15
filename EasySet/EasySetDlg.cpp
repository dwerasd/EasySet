// EasySetDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "EasySet.h"
#include "EasySetDlg.h"

#include "MFCLoadString.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEasySetDlg 대화 상자
CEasySetDlg::CEasySetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEasySetDlg::IDD, pParent)
	, pLoadStringA(0)
	, pLoadStringW(0)
	, pLoadLibraryW(0)
	, pGetModuleHandleW(0)
	, pGetUserNameW(0)
	, pNetUserChangePassword(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEasySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, COMBO_ADAPTER, comboAdapters);
}

BEGIN_MESSAGE_MAP(CEasySetDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDOK, &CEasySetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEasySetDlg::OnBnClickedCancel)
	ON_BN_CLICKED(BTN_PRINTER_IP, &CEasySetDlg::OnBnClickedPrinterIp)
	ON_BN_CLICKED(BTN_START, &CEasySetDlg::OnBnClickedStart)
	ON_COMMAND(MENU_HELO_INFO, &CEasySetDlg::OnHeloInfo)
END_MESSAGE_MAP()


// CEasySetDlg 메시지 처리기

BOOL CEasySetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitFunc();			// 함수 주소들 세팅
	GetAdapterList();	// 어댑터 얻어오고

	CButton *pBtn = (CButton *)GetDlgItem(IDC_RADIO1);
	if (pBtn)
	{
		pBtn->SetCheck(TRUE);	// 업무망 선택
	}
	CEdit *pEdit = (CEdit *)GetDlgItem(EDIT_PRINTER_IP);
	if (pEdit)
	{
		pEdit->SetFocus();		// 프린터 아이피 입력에 포커스
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEasySetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEasySetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEasySetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
void CEasySetDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
*/
void CEasySetDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CEasySetDlg::OnBnClickedPrinterIp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPrintIp;
	GetDlgItemText(EDIT_PRINTER_IP, strPrintIp);

	char szBuffer[(1 << 8)];
	WCHAR wszBuffer[(1 << 8)];
	if (strPrintIp.GetLength() < 3)
	{
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2113, szBuffer, _countof(szBuffer));
		system(szBuffer);
		return;
	}
	if (strPrintIp.GetLength() > 7)
	{
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2113, szBuffer, _countof(szBuffer));
		system(szBuffer);
		return;
	}
	CString strIPBand;
	CButton *pBtn = (CButton *)GetDlgItem(IDC_RADIO1);
	if (pBtn->GetCheck())
	{
		pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2114, wszBuffer, _countof(wszBuffer));
		strIPBand = wszBuffer;
	}
	else
	{
		pBtn = (CButton *)GetDlgItem(IDC_RADIO2);
		if (pBtn->GetCheck())
		{
			pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2115, wszBuffer, _countof(wszBuffer));
			strIPBand = wszBuffer;
		}
	}
	ZeroMemory(wszBuffer, _countof(wszBuffer));
	CString strPrinterIPAddr = strIPBand + strPrintIp;	// 아이피대역 + 아이피주소, ex) 172.16. + 23.205

	char szPrinterIPAddr[(1 << 8)];
	WideCharToMultiByte(CP_ACP, 0, strPrinterIPAddr.GetString(), (int)strPrinterIPAddr.GetLength() + 1, szPrinterIPAddr, (int)_countof(szPrinterIPAddr), 0, 0);

	//cscript c:\windows\system32\printing_admin_scripts\ko-KR\prnport.vbs -a -r IP_192.168.0.22 -h 192.168.0.22 -o lpr -md -n 9100
	//cscript c:\windows\system32\printing_admin_scripts\ko-KR\prnport.vbs -a -r IP_192.168.0.22 -h 192.168.0.22 -o raw -md -n 9100

	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2116, szBuffer, _countof(szBuffer));

	char szType[(1 << 8)];
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2117, szType, _countof(szType));

	char szCommand[(1 << 10)] = { 0 };
	wsprintfA(szCommand
		, szType
		, szBuffer
		, szPrinterIPAddr
		, szPrinterIPAddr
	);
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2118, szBuffer, _countof(szBuffer));
	CMDPRINT(szBuffer, szPrinterIPAddr);
	ZeroMemory(szBuffer, _countof(szBuffer));
	system(szCommand);
	ZeroMemory(szCommand, _countof(szCommand));
}

void CEasySetDlg::OnBnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strComputerName, strGroupName, strPassword, strNetworkIp;
	char szComputerName[(1 << 8)] = { 0 }, szGroupName[(1 << 8)] = { 0 }, szPassword[(1 << 8)] = { 0 }, szNetworkIp[(1 << 8)] = { 0 };
	char szBuffer[(1 << 8)] = { 0 }, szCommand[(1 << 10)] = { 0 };
	wchar_t wszBuffer[(1 << 8)] = { 0 };

	GetDlgItemText(EDIT_USERNAME, strComputerName);
	GetDlgItemText(EDIT_GROUPNAME, strGroupName);
	GetDlgItemText(EDIT_PASSWORD, strPassword);
	GetDlgItemText(EDIT_IPV4_IP, strNetworkIp);
	
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2113, szBuffer, _countof(szBuffer));
	system(szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));

	CButton *pBtn = (CButton *)GetDlgItem(IDC_RADIO1);	// 업무망인지 인터넷망인지 판단을 위해
	char szCurrentUserName[(1 << 8)];
	if (0 != strComputerName.GetLength())
	{
		WideCharToMultiByte(CP_ACP, 0, strComputerName.GetString(), strComputerName.GetLength() + 1, szComputerName, (int)_countof(szComputerName), 0, 0);

		//////////////////////////////////////////////////////////////////////////
		// 컴퓨터 이름 변경

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2123, szBuffer, _countof(szBuffer));
		CMDPRINT(szBuffer, szComputerName);
		ZeroMemory(szBuffer, _countof(szBuffer));

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2124, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand, szBuffer, szComputerName);
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));	// 커맨드버퍼 비움

		//////////////////////////////////////////////////////////////////////////
		// 사용자 계정명 변경

		DWORD dwBufferSize = _countof(wszBuffer);
		pGetUserNameW(wszBuffer, &dwBufferSize);		// 윈도우 계정을 얻어온다.

		WideCharToMultiByte(CP_ACP, 0, wszBuffer, (int)wcslen(wszBuffer) + 1, szCurrentUserName, (int)_countof(szCurrentUserName), 0, 0);

		strcat_s(szComputerName, pBtn->GetCheck() ? "(업무망)" : "(인터넷망)");

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2127, szBuffer, _countof(szBuffer));
		CMDPRINT(szBuffer, szComputerName);
		ZeroMemory(szBuffer, _countof(szBuffer));

		// wmic UserAccount where Name=\"%s\" Set FullName=\"%s%s\"
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2128, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand
			, szBuffer
			, szCurrentUserName
			, szComputerName
			);
		memset(szBuffer, 0, _countof(szBuffer));
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));	// 커맨드버퍼 비움

	}

	if(0 != strGroupName.GetLength())
	{
		WideCharToMultiByte(CP_ACP, 0, strGroupName.GetString(), strGroupName.GetLength() + 1, szGroupName, (int)_countof(szGroupName), 0, 0);

		//////////////////////////////////////////////////////////////////////////
		// 작업 그룹 변경

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2125, szBuffer, _countof(szBuffer));
		CMDPRINT(szBuffer, szGroupName);
		ZeroMemory(szBuffer, _countof(szBuffer));

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2126, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand, szBuffer, szGroupName);
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));	// 커맨드버퍼 비움
	}
	

	if(0 == strPassword.GetLength())	// 만약 패스워드가 있다면 변환하고 없다면 "" 일 것이다.
	{
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2121, szPassword, _countof(szPassword));
	}
	else
	{
		WideCharToMultiByte(CP_ACP, 0, strPassword.GetString(), strPassword.GetLength() + 1, szPassword, (int)_countof(szPassword), 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////
	// 윈도우 패스워드 변경

	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2129, szBuffer, _countof(szBuffer));
	CMDPRINT(szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));

	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2130, szBuffer, _countof(szBuffer));
	wsprintfA(
		szCommand
		, szBuffer
		, szCurrentUserName
		, szPassword
		);
	ZeroMemory(szBuffer, _countof(szBuffer));
	//CMDPRINT("커맨드: %s", szCommand);
	system(szCommand);
	memset(szCommand, 0, _countof(szCommand));

	if(0 != strNetworkIp.GetLength())
	{
		WideCharToMultiByte(CP_ACP, 0, strNetworkIp.GetString(), strNetworkIp.GetLength() + 1, szNetworkIp, (int)_countof(szNetworkIp), 0, 0);

		//////////////////////////////////////////////////////////////////////////
		// 아이피를 입력하자.

		CString strAdapter;
		comboAdapters.GetLBText(comboAdapters.GetCurSel(), strAdapter);	// 변경할 어댑터 이름을 콤보박스에서 가져온다.

		char szAdapter[(1 << 8)] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, strAdapter.GetString(), (int)strAdapter.GetLength() + 1, szAdapter, (int)_countof(szAdapter), 0, 0);

		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2131, szBuffer, _countof(szBuffer));
		CMDPRINT(szBuffer, szAdapter);
		ZeroMemory(szBuffer, _countof(szBuffer));

		//////////////////////////////////////////////////////////////////////////
		// 나중에 변경할테니 하드코딩한다

		std::string strGateway = "10.96.";
		std::string strMainDNS = "10.1.1.5";
		std::string strSubDNS = "10.188.134.21";

		pBtn = (CButton *)GetDlgItem(IDC_RADIO2);
		if (pBtn->GetCheck())	// 만약 인터넷망이라면
		{
			strGateway = "172.16.";
			strMainDNS = "152.99.1.6";
			strSubDNS = "168.126.63.1";
		}
		std::string strIpAddr = strGateway;
		strIpAddr += szNetworkIp;
		CMDPRINT("아이피주소: %s", strIpAddr.c_str());

		char szSubnetMask[16] = { "255.255.255.0" };
		CMDPRINT("서브넷마스크: %s", szSubnetMask);

		char szTemp[16] = { 0 };
		memcpy_s(szTemp, _countof(szTemp), szNetworkIp, strlen(szNetworkIp));	// 입력받은 아이피를 복사함.
		*(LPSTR)(strstr(szTemp, ".") + 1) = 0;									// . 다음부터 짤라서 뒤 2자리중 앞의 ??. 을 얻음.
		strcat_s(szTemp, "250");												// 250을 붙여서 게이트웨이 뒤의 2자리 완성
		strGateway += szTemp;

		CMDPRINT("게이트웨이: %s", strGateway.c_str());

		//netsh interface ipv4 set address "로컬 영역 연결" static 172.16.13.100 255.255.255.0 172.16.13.250
		// netsh interface ipv4 set address \"%s\" static %s %s %s
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2132, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand
			, szBuffer
			, szAdapter
			, strIpAddr.c_str()
			, szSubnetMask
			, strGateway.c_str()
			);
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));

		CMDPRINT("기본 DNS: %s", strMainDNS.c_str());
		//netsh interface ipv4 set dns "로컬 영역 연결" static 152.99.1.6 primary no
		// netsh interface ipv4 set dns \"%s\" static %s primary no
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2133, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand
			, szBuffer
			, szAdapter
			, strMainDNS.c_str()
			);
		memset(szBuffer, 0, _countof(szBuffer));
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));


		CMDPRINT("보조 DNS: %s", strSubDNS.c_str());
		//netsh interface ipv4 add dns "로컬 영역 연결" 168.126.63.1 index=2 no
		// netsh interface ipv4 add dns \"%s\" %s index=2 no
		pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2134, szBuffer, _countof(szBuffer));
		wsprintfA(szCommand
			, szBuffer
			, szAdapter
			, strSubDNS.c_str()
			);
		//CMDPRINT("커맨드: %s", szCommand);
		system(szCommand);
		memset(szCommand, 0, _countof(szCommand));
	}
	
	//////////////////////////////////////////////////////////////////////////
	// 디스크 매니저를 띄우고

	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2135, szBuffer, _countof(szBuffer));
	system(szBuffer);
	memset(szBuffer, 0, _countof(szBuffer));

	//////////////////////////////////////////////////////////////////////////
	// 디스크 매니저가 닫히면 재부팅한다.

	// shutdown -r -f -t 0
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2136, szBuffer, _countof(szBuffer));
	system(szBuffer);
	memset(szBuffer, 0, _countof(szBuffer));
}

void CEasySetDlg::InitFunc()
{
	// user32
	CStringW strModuleName;
	strModuleName.LoadString(IDS_STRING2102);
	HMODULE hModule = GetModuleHandleW(strModuleName.GetString());
	if (0 == hModule)
	{
		hModule = LoadLibraryW(strModuleName.GetString());
	}
	CStringA strLoadStringA;
	strLoadStringA.LoadString(IDS_STRING2103);
	pLoadStringA = (LoadStringA_PROC)GetProcAddress(hModule, strLoadStringA.GetString());

	char szBuffer[(1 << 8)];
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2104, szBuffer, _countof(szBuffer));
	pLoadStringW = (LoadStringW_PROC)GetProcAddress(hModule, szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));

	wchar_t wszBuffer[(1 << 8)];
	pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2101, wszBuffer, _countof(wszBuffer));
	CMDINIT(wszBuffer);	// 콘솔창 생성.

	// kernel32
	pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2105, wszBuffer, _countof(wszBuffer));
	hModule = GetModuleHandleW(wszBuffer);
	if (0 == hModule)
	{
		hModule = LoadLibraryW(wszBuffer);
	}
	ZeroMemory(wszBuffer, _countof(wszBuffer));
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2106, szBuffer, _countof(szBuffer));
	pLoadLibraryW = (LoadLibraryW_PROC)GetProcAddress(hModule, szBuffer);

	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2107, szBuffer, _countof(szBuffer));
	pGetModuleHandleW = (GetModuleHandleW_PROC)GetProcAddress(hModule, szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));

	// advapi32
	pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2108, wszBuffer, _countof(wszBuffer));
	hModule = pGetModuleHandleW(wszBuffer);
	if (0 == hModule)
	{
		hModule = pLoadLibraryW(wszBuffer);
	}
	ZeroMemory(wszBuffer, _countof(wszBuffer));
	// GetUserNameW
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2109, szBuffer, _countof(szBuffer));
	pGetUserNameW = (GetUserNameW_PROC)GetProcAddress(hModule, szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));

	// netapi32
	pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2110, wszBuffer, _countof(wszBuffer));
	hModule = pGetModuleHandleW(wszBuffer);
	if (0 == hModule)
	{
		hModule = pLoadLibraryW(wszBuffer);
	}
	ZeroMemory(wszBuffer, _countof(wszBuffer));
	// NetUserChangePassword
	pLoadStringA(AfxGetInstanceHandle(), IDS_STRING2111, szBuffer, _countof(szBuffer));
	pNetUserChangePassword = (NetUserChangePassword_PROC)GetProcAddress(hModule, szBuffer);
	ZeroMemory(szBuffer, _countof(szBuffer));
}

void CEasySetDlg::GetAdapterList()
{
// 네트워크 어댑터 리스트를 얻어오자.
	CoInitialize(NULL); 
	INetConnectionManager *pNetConnectionManager = NULL; 
	HRESULT hr = CoCreateInstance(CLSID_ConnectionManager,
		NULL,
		CLSCTX_LOCAL_SERVER | CLSCTX_NO_CODE_DOWNLOAD, 
		IID_INetConnectionManager, 
		reinterpret_cast<LPVOID *>(&pNetConnectionManager)
	);
	if (SUCCEEDED(hr)) 
	{
		/*Get an enumurator for the set of connections on the system */
		IEnumNetConnection* pEnumNetConnection; 
		pNetConnectionManager->EnumConnections(NCME_DEFAULT, &pEnumNetConnection);
		ULONG ulCount = 0;
		BOOL fFound = FALSE; 
		hr = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND); 
		HRESULT hrT = S_OK;

		/*
		Enumurate through the list of adapters on the system and look for the one we want
		NOTE: To include per-user RAS connections in the list, you need to set the COM Proxy Blanket on all the interfaces. This is not needed for All-user RAS connections or LAN connections. 
		*/
		do
		{
			NETCON_PROPERTIES* pProps = NULL;
			INetConnection *pConn;

			/*
			Find the next (or first connection)
			*/
			hrT = pEnumNetConnection->Next(1, &pConn, &ulCount);

			if (SUCCEEDED(hrT) && 1 == ulCount)
			{
				/*
				Get the connection properties
				*/
				hrT = pConn->GetProperties(&pProps);

				if (S_OK == hrT)
				{
					comboAdapters.AddString(pProps->pszwName);
					if (1 == comboAdapters.GetCount())
					{
						comboAdapters.SetCurSel(0);
						wchar_t wszBuffer[(1 << 8)];
						pLoadStringW(AfxGetInstanceHandle(), IDS_STRING2112, wszBuffer, _countof(wszBuffer));
						CMDPRINT(wszBuffer, pProps->pszwName);
					}
					CoTaskMemFree (pProps->pszwName);
					CoTaskMemFree (pProps->pszwDeviceName);
					CoTaskMemFree (pProps); 
				}
				pConn->Release();
				pConn = NULL;
			}
		} 
		while (SUCCEEDED(hrT) && 1 == ulCount && !fFound);
		if (FAILED(hrT))
		{
			hr = hrT;
		}
		pEnumNetConnection->Release();
	}
	pNetConnectionManager->Release(); 
	CoUninitialize(); 
}

void CEasySetDlg::OnHeloInfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	

	CAboutDlg dlgAbout;
	dlgAbout.DoModal();

}

