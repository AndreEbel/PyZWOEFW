
// EFW_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EFW_MFC.h"
#include "EFW_MFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CEFW_MFCDlg �Ի���




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


// CEFW_MFCDlg ��Ϣ�������

BOOL CEFW_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	iSelectedID = -1;
	for(int i = 0; i < sizeof(EFW_cap)/sizeof(EFW_Cap); i++)
	{
		
		EFW_cap[i].Thr_getSlotNum = NULL;
		EFW_cap[i].Thr_getPos= NULL;
		EFW_cap[i].bThrGetSlotNumRun = false;
		EFW_cap[i].bThrGetPosRun = false;	
	
	}
	OnBnClickedButtonScan();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEFW_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEFW_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEFW_MFCDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for(int i = 0; i < sizeof(EFW_cap)/sizeof(EFW_Cap); i++)
		closeEFW(i);
	CDialog::OnClose();
}
void CEFW_MFCDlg::OnBnClickedButtonScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		if(err != EFW_ERROR_MOVING)//����Ѿ��رյĻ��ͽ����߳�
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
		if(err != EFW_SUCCESS || pos != -1)//����Ѿ��رյĻ��ͽ����߳�
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
void CEFW_MFCDlg::refreshUI()//ˢ��slot������ ��ѡ��ǰλ�ã���ʾ��ǰ״̬
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	closeEFW(iSelectedID);
	OnBnClickedButtonScan();
}

void CEFW_MFCDlg::OnCbnSelchangeComboSlots()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combo_slots.GetCurSel();
	EFWSetPosition(iSelectedID, index);
	refreshPosStatus();
}


void CEFW_MFCDlg::OnCbnSelchangeComboFilters()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	EFWSetDirection(iSelectedID, m_check_unidirectional);
}
