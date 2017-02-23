// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "LoginDlg.h"
#include "ManageDlg.h"

// LoginDlg �Ի���

IMPLEMENT_DYNAMIC(LoginDlg, CDialog)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
	, m_user(_T(""))
	, m_password(_T(""))
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LoginDlg ��Ϣ�������

void LoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//CoInitialize(NULL);
	//_ConnectionPtr pConn(__uuidof(Connection));
	//_RecordsetPtr pRst(__uuidof(Recordset));
	//_CommandPtr pCmd(__uuidof(Command));
	//pRst->CursorType = adOpenStatic;//������GetRecordCount����������������Ҫʹ�ã�������Ϊ��̬�α�
	//pRst->CursorLocation = adUseClient;

    //try                    
    //{      
    //   pConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");  
	   //pConn->Open("","","",adConnectUnspecified);
    //}   
    //catch(_com_error e)   
    //{   
    //    MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
    //    MessageBox( e.Description() );   
    //    MessageBox( e.ErrorMessage() );    
    //    return;   
    //}   

	UpdateData();
	if(m_user.IsEmpty() || m_password.IsEmpty())
    {
        MessageBox(_T("�û��������벻��Ϊ��"));
        return;
    }

	//pCmd->put_ActiveConnection(_variant_t((IDispatch*)pConn));
	//pCmd->CommandText=_bstr_t(sql);
	//

	try
	{
		CString sql=_T("");
		sql.Format(_T("select * from users where username='%s' and password='%s'"),m_user,m_password); 

		//pRst=pCmd->Execute(NULL,NULL,adCmdText);
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		//pRst->get_RecordCount()
		//long lCount = 0; 
		//HRESULT hr = pRst ->get_RecordCount( &lCount ); 
		//int a=pRst->GetRecordCount();

		if(pRst->rsEOF)
		{
			MessageBox(_T("�û��������벻��ȷ��")); 
		}
		else
		{
			theApp.managename=pRst->GetCollect("username");
			//pRst->Close();
			MessageBox(_T("��½�ɹ���")); 
			this->ShowWindow(SW_HIDE);
			ManageDlg mdlg;
			mdlg.DoModal();
			EndDialog(TRUE);  
		
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		MessageBox(_T("��ȡ���ݿ�ʧ��!"));///��ʾ������Ϣ
	    MessageBox( e.Description() );   
        MessageBox( e.ErrorMessage() );  
	}
	pRst->Close();



	//OnOK();

}

BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pRst.CreateInstance("ADODB.Recordset");
	HBITMAP  hBitmap1;   
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP16));
	((CButton *)GetDlgItem(IDOK))->SetBitmap(hBitmap1); 
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP17));
	((CButton *)GetDlgItem(IDCANCEL))->SetBitmap(hBitmap1); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL LoginDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	

	return CDialog::DestroyWindow();
}
