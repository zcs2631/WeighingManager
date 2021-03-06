
// WeighingManagerDlg.h : 头文件
//

#pragma once
#include "CToolBarEx.h"

// CWeighingManagerDlg 对话框
class CWeighingManagerDlg : public CDialogEx
{
// 构造
public:
	CWeighingManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WEIGHINGMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void InitImageList();
	BOOL InitToolBar();
private:
	CImageList      m_ImageListHotToolbar;//使工具栏图标显示256色
	CImageList      m_ImageListToolbar;
	CToolBarEx      m_ToolBar;
};
