#ifndef __TOOLBAREX_H__
#define __TOOLBAREX_H__

class CToolBarEx :public CToolBar
{
public:


protected:
	//{{AFX_MSG(CSXBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);     //������Ϣ��Ӧ����
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif