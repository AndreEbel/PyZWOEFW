
// EFW_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "EFW_filter.h"
#include "afxwin.h"

// CEFW_MFCDlg �Ի���
class CEFW_MFCDlg : public CDialog
{
// ����
public:
	CEFW_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EFW_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	struct EFW_Cap{
		HANDLE Thr_getSlotNum;
		bool bThrGetSlotNumRun;
		HANDLE Thr_getPos;
		bool bThrGetPosRun;

	} ;
//	int EFW_ID[EFW_ID_MAX];


	void refreshUI();
	void refreshPosStatus();
	LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);
	void closeEFW(int ID);
public:
	int iSelectedID;
	EFW_Cap EFW_cap[EFW_ID_MAX];

	afx_msg void OnBnClickedButtonScan();

	CComboBox combo_filter;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	CComboBox combo_slots;
	afx_msg void OnCbnSelchangeComboSlots();
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboFilters();
	CString m_static_status;

	BOOL m_check_unidirectional;
	afx_msg void OnBnClickedCheckUnidirectional();
};
