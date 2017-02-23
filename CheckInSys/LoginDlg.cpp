// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "LoginDlg.h"
#include "ManageDlg.h"

// LoginDlg 对话框

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


// LoginDlg 消息处理程序

void LoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//CoInitialize(NULL);
	//_ConnectionPtr pConn(__uuidof(Connection));
	//_RecordsetPtr pRst(__uuidof(Recordset));
	//_CommandPtr pCmd(__uuidof(Command));
	//pRst->CursorType = adOpenStatic;//该死的GetRecordCount（）函数，尽量不要使用，这里设为静态游标
	//pRst->CursorLocation = adUseClient;

    //try                    
    //{      
    //   pConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");  
	   //pConn->Open("","","",adConnectUnspecified);
    //}   
    //catch(_com_error e)   
    //{   
    //    MessageBox(_T("数据库连接失败，确认数据库是否在当前路径下!"));   
    //    MessageBox( e.Description() );   
    //    MessageBox( e.ErrorMessage() );    
    //    return;   
    //}   

	UpdateData();
	if(m_user.IsEmpty() || m_password.IsEmpty())
    {
        MessageBox(_T("用户名或密码不能为空"));
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
			MessageBox(_T("用户名或密码不正确！")); 
		}
		else
		{
			theApp.managename=pRst->GetCollect("username");
			//pRst->Close();
			MessageBox(_T("登陆成功！")); 
			this->ShowWindow(SW_HIDE);
			ManageDlg mdlg;
			mdlg.DoModal();
			EndDialog(TRUE);  
		
		}
	}
	catch(_com_error e)///捕捉异常
	{
		MessageBox(_T("读取数据库失败!"));///显示错误信息
	    MessageBox( e.Description() );   
        MessageBox( e.ErrorMessage() );  
	}
	pRst->Close();



	//OnOK();

}

BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pRst.CreateInstance("ADODB.Recordset");
	HBITMAP  hBitmap1;   
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP16));
	((CButton *)GetDlgItem(IDOK))->SetBitmap(hBitmap1); 
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP17));
	((CButton *)GetDlgItem(IDCANCEL))->SetBitmap(hBitmap1); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL LoginDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	

	return CDialog::DestroyWindow();
}
