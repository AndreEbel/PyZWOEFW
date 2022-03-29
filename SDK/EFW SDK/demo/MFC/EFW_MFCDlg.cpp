
// EFW_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EFW_MFC.h"
#include "EFW_MFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CEFW_MFCDlg 对话框




CEFW_MFCDlg::CEFW_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEFW_MFCDlg::IDD, pParent)
	, m_static_status(_T(""))	
	, m_check_unidirectional(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEFW_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILTERS, combo_filter);
	DDX_Control(pDX, IDC_COMBO_SLOTS, combo_slots);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_static_status);


	DDX_Check(pDX, IDC_CHECK_UNIDIRECTIONAL, m_check_unidirectional);
}
#define WM_MY_MSG  12321

BEGIN_MESSAGE_MAP(CEFW_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CEFW_MFCDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CEFW_MFCDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CEFW_MFCDlg::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_SLOTS, &CEFW_MFCDlg::OnCbnSelchangeComboSlots)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERS, &CEFW_MFCDlg::OnCbnSelchangeComboFilters)

	ON_MESSAGE(WM_MY_MSG, OnUpdateData)

	ON_BN_CLICKED(IDC_CHECK_UNIDIRECTIONAL, &CEFW_MFCDlg::OnBnClickedCheckUnidirectional)
END_MESSAGE_MAP()


// CEFW_MFCDlg 消息处理程序

BOOL CEFW_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	iSelectedID = -1;
	for(int i = 0; i < sizeof(EFW_cap)/sizeof(EFW_Cap); i++)
	{
		
		EFW_cap[i].Thr_getSlotNum = NULL;
		EFW_cap[i].Thr_getPos= NULL;
		EFW_cap[i].bThrGetSlotNumRun = false;
		EFW_cap[i].bThrGetPosRun = false;	
	
	}
	OnBnClickedButtonScan();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEFW_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEFW_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEFW_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEFW_MFCDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for(int i = 0; i < sizeof(EFW_cap)/sizeof(EFW_Cap); i++)
		closeEFW(i);
	CDialog::OnClose();
}
void CEFW_MFCDlg::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	int EFW_count = EFWGetNum();
	combo_filter.Clear();
	combo_filter.ResetContent();
	int id, iSelectedIndex = -1, iFirstOpened = -1, pos;
	CString cs;      
	EFW_INFO EFWInfoTemp;
	for(int i = 0; i < EFW_count; i++)
	{	
		EFWGetID(i, &id);
		EFWGetProperty(id, &EFWInfoTemp);
		
		if(iSelectedID == id)
			iSelectedIndex = i;
		if(EFWGetPosition(id, &pos) != EFW_ERROR_CLOSED)
			cs.Format("%s(ID %d opened)", EFWInfoTemp.Name, id);
		else
			cs.Format("%s(ID %d closed)", EFWInfoTemp.Name, id);
		
		combo_filter.AddString(cs);

	}
	
	if(iSelectedIndex == -1)//
	{
		if(EFW_count > 0)
			iSelectedIndex = 0;
		else
			iSelectedIndex = -1;
		iSelectedID = -1;
	}

	combo_filter.SetCurSel(iSelectedIndex);
	OnCbnSelchangeComboFilters();
	
}
void GetSlotsNumFunc(LPVOID params)
{
	CEFW_MFCDlg* dlg =(CEFW_MFCDlg*)params;
	int iID = dlg->iSelectedID;
	EFW_INFO info;
	EFW_ERROR_CODE err;
	while(dlg->EFW_cap[iID].bThrGetSlotNumRun)
	{
		err = EFWGetProperty(iID, &info);
		if(err != EFW_ERROR_MOVING)//如果已经关闭的话就结束线程
			break;
		Sleep(200);
	}
	dlg->EFW_cap[iID].bThrGetSlotNumRun = false;
	if(dlg->iSelectedID == iID)
		SendMessage(dlg->m_hWnd, WM_MY_MSG, WM_CHANGEUISTATE, TRUE);
	_endthread();

}
void MoveFunction(LPVOID params)
{
	CEFW_MFCDlg* dlg =(CEFW_MFCDlg*)params;
	int iID = dlg->iSelectedID;
	int pos;
	EFW_ERROR_CODE err;
	while(dlg->EFW_cap[iID].bThrGetPosRun)
	{		
		err = EFWGetPosition(iID, &pos);
		if(err != EFW_SUCCESS || pos != -1)//如果已经关闭的话就结束线程
			break;
		Sleep(200);
	}
	dlg->EFW_cap[iID].bThrGetPosRun = false;
	if(dlg->iSelectedID == iID)
		SendMessage(dlg->m_hWnd, WM_MY_MSG, WM_CHANGEUISTATE, FALSE);
	_endthread();

}
void CEFW_MFCDlg::refreshPosStatus()
{
	int pos;
	EFW_ERROR_CODE err = EFWGetPosition(iSelectedID, &pos);
	if(err == EFW_SUCCESS && iSelectedID > -1 && iSelectedID < sizeof(EFW_cap)/sizeof(EFW_Cap))
	{
		if(pos == -1)
		{	
			m_static_status = "moving";

			if (!EFW_cap[iSelectedID].bThrGetPosRun)
			{
				EFW_cap[iSelectedID].bThrGetPosRun = true;
				EFW_cap[iSelectedID].Thr_getPos = (HANDLE)_beginthread(MoveFunction, NULL, this);
			}
		}
		else
		{	
			m_static_status = "ready";

			if(pos >= 0 && pos < combo_slots.GetCount())
				combo_slots.SetCurSel(pos);
		}
	}
	UpdateData(FALSE);
}
void CEFW_MFCDlg::refreshUI()//刷新slot下拉框 并选择当前位置，显示当前状态
{
	EFW_INFO info;
	if(iSelectedID < 0)
	{
		combo_slots.ResetContent();
		m_static_status = "not opened";
		m_check_unidirectional = false;
	}
	else
	{
		bool bUnidir;
		EFWGetDirection(iSelectedID, &bUnidir);
		m_check_unidirectional = bUnidir;

		EFW_ERROR_CODE err = EFWGetProperty(iSelectedID, &info);
		if(err == EFW_SUCCESS)
		{
			CString cs;
			combo_slots.ResetContent();
			for(int i = 0; i < info.slotNum; i++)
			{
				cs.Format("%d", i + 1);
				combo_slots.AddString(cs);
			}
			refreshPosStatus();
		}
		else if(err == EFW_ERROR_MOVING)
		{
			m_static_status = "moving...";
			if (!EFW_cap[iSelectedID].bThrGetSlotNumRun)
			{
				EFW_cap[iSelectedID].bThrGetSlotNumRun = true;
				EFW_cap[iSelectedID].Thr_getSlotNum = (HANDLE)_beginthread(GetSlotsNumFunc, NULL, this);
			}
		}
	}
	UpdateData(FALSE);
}


void CEFW_MFCDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	if(EFWGetID(combo_filter.GetCurSel(), &iSelectedID) != EFW_SUCCESS)
		return;
	
	EFW_ERROR_CODE err = EFWOpen(iSelectedID);
	if(err != EFW_SUCCESS)
	{
		::AfxMessageBox("failed to open filter");
		return;
	}
	OnBnClickedButtonScan();
}
void CEFW_MFCDlg::closeEFW(int ID)
{
	if(ID > -1 && ID < sizeof(EFW_cap)/sizeof(EFW_Cap))
	{
		if(EFW_cap[ID].bThrGetSlotNumRun)
		{
			EFW_cap[ID].bThrGetSlotNumRun = false;
			WaitForSingleObject(EFW_cap[ID].Thr_getSlotNum, 5000);
		}
		if(EFW_cap[ID].bThrGetPosRun)
		{
			EFW_cap[ID].bThrGetPosRun = false;
			WaitForSingleObject(EFW_cap[ID].Thr_getPos, 5000);
		}	
	}   
	EFWClose(ID);
}

void CEFW_MFCDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	closeEFW(iSelectedID);
	OnBnClickedButtonScan();
}

void CEFW_MFCDlg::OnCbnSelchangeComboSlots()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = combo_slots.GetCurSel();
	EFWSetPosition(iSelectedID, index);
	refreshPosStatus();
}


void CEFW_MFCDlg::OnCbnSelchangeComboFilters()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = combo_filter.GetCurSel();
	EFWGetID(index, &iSelectedID);
	refreshUI();
}
LRESULT CEFW_MFCDlg::OnUpdateData(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
	
	case WM_CHANGEUISTATE:
		if(lParam)
			refreshUI();
		else
			refreshPosStatus();
		break;
	case WM_UPDATEUISTATE:
		UpdateData(lParam);
		break;
	}			

	return 0;
}

void CEFW_MFCDlg::OnBnClickedCheckUnidirectional()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	EFWSetDirection(iSelectedID, m_check_unidirectional);
}
