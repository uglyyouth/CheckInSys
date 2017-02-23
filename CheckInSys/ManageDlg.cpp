// ManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "ManageDlg.h"
#include "VideoCam.h"
#include "password.h"
#include "leaveDlg.h"
#include "editcourse.h"
#include "heckbox.h"
extern CCheckInSysApp theApp;


// ManageDlg �Ի���


IMPLEMENT_DYNAMIC(ManageDlg, CDialog)

ManageDlg::ManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ManageDlg::IDD, pParent)
	, m_course(_T(""))
	, m_daysel(COleDateTime::GetCurrentTime())
{

}

ManageDlg::~ManageDlg()
{
}

void ManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST1, m_course);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_daysel);
}


BEGIN_MESSAGE_MAP(ManageDlg, CDialog)
	ON_COMMAND(ID_VIDEOCAM, &ManageDlg::OnVideocam)
	ON_COMMAND(ID_CHANGEPASS, &ManageDlg::OnChangepass)
	ON_LBN_SELCHANGE(IDC_LIST1, &ManageDlg::OnLbnSelchangeList1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &ManageDlg::OnMcnSelchangeMonthcalendar1)
	ON_COMMAND(ID_leave, &ManageDlg::Onleave)
	ON_COMMAND(ID_course, &ManageDlg::Oncourse)
	ON_COMMAND(ID_check, &ManageDlg::Oncheck)
END_MESSAGE_MAP()


// ManageDlg ��Ϣ�������

void ManageDlg::OnVideocam()
{
	// TODO: �ڴ���������������
	VideoCam vdlg;
	vdlg.DoModal();
}



void ManageDlg::OnChangepass()
{
	// TODO: �ڴ���������������
	password pdlg;
	pdlg.DoModal();
}


BOOL ManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CTime mt = CTime::GetCurrentTime();
	int mw=mt.GetDayOfWeek()-1; 

	
	if ((mw==0)|(mw==6))
	{
		mw=1;
	}


    //try                    
    //{      
    //   mmpConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");
	   //mmpConn->Open("","","",adConnectUnspecified);
    //}   
    //catch(_com_error e)   
    //{   
    //    MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
    //    MessageBox( e.Description() );   
    //    MessageBox( e.ErrorMessage() );    
    //    return FALSE;   
    //}  

		CString sql=_T("");
		CString kecheng=_T("");
		CString CID=_T("");
	
		sql.Format(_T("select * from course where weektime=%d"),mw); 
		pRst.CreateInstance("ADODB.Recordset");
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		//CID.Format((_bstr_t)mmpRst->GetCollect("CID"));
		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("CID")+_T("-")+(_bstr_t)pRst->GetCollect("coursename"));
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();
	((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(0);

	UpdateData();
	CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,0,'-'); 

	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();

	//mmpConn->Close();
	//mmpRst.Release();
	//mmpConn.Release();
	//CoUninitialize();
	//
	
	//	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



void ManageDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,0,'-'); 

	CString sql=_T("");
	CString kecheng=_T("");
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();




	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	//pRst.CreateInstance("ADODB.Recordset");
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();

}



void ManageDlg::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	UpdateData();
	int weekday=m_daysel.GetDayOfWeek()-1;

		if ((weekday==0)|(weekday==6))
	{
		weekday=1;
	}

	CString sql=_T("");
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();


	sql.Format(_T("select * from course where weektime=%d"),weekday); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
	//CID.Format((_bstr_t)mmpRst->GetCollect("CID"));
	while(!pRst->rsEOF)
	{
		sql.Format((_bstr_t)pRst->GetCollect("CID")+_T("-")+(_bstr_t)pRst->GetCollect("coursename"));
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(sql);
		pRst->MoveNext();
	}

		pRst->Close();
		((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(0);



		
	UpdateData();
	CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,0,'-'); 
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();

	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			sql.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(sql);
			pRst->MoveNext();
		}

	pRst->Close();




}

void ManageDlg::Onleave()
{
	// TODO: �ڴ���������������
	leaveDlg ldlg;
	ldlg.DoModal();

}

void ManageDlg::Oncourse()
{
	// TODO: �ڴ���������������
	editcourse edlg;
	edlg.DoModal();
}

void ManageDlg::Oncheck()
{
	// TODO: �ڴ���������������
	checkbox edlg;
	edlg.DoModal();
}
