// password.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "password.h"

extern CCheckInSysApp theApp;


// password 对话框

IMPLEMENT_DYNAMIC(password, CDialog)

password::password(CWnd* pParent /*=NULL*/)
	: CDialog(password::IDD, pParent)
	, m_passwordo(_T(""))
	, m_passwordnn(_T(""))
	, m_passwordn(_T(""))
{

}

password::~password()
{
}

void password::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_passwordo);
	DDX_Text(pDX, IDC_EDIT3, m_passwordnn);
	DDX_Text(pDX, IDC_EDIT2, m_passwordn);
}


BEGIN_MESSAGE_MAP(password, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &password::OnBnClickedButton1)
END_MESSAGE_MAP()


// password 消息处理程序

void password::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//CoInitialize(NULL);
	//_ConnectionPtr pConn(__uuidof(Connection));
	//_RecordsetPtr pRst(__uuidof(Recordset));
	//_CommandPtr pCmd(__uuidof(Command));
	//pRst->CursorType = adOpenStatic;
	//pRst->CursorLocation = adUseClient;

 //   try                    
 //   {      
 //      pConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");  
	//   pConn->Open("","","",adConnectUnspecified);
 //   }   
 //   catch(_com_error e)   
 //   {   
 //       MessageBox(_T("数据库连接失败，确认数据库是否在当前路径下!"));   
 //       MessageBox( e.Description() );   
 //       MessageBox( e.ErrorMessage() );    
 //       return;   
 //   }   

	UpdateData();
	if(m_passwordo.IsEmpty() || m_passwordn.IsEmpty()||m_passwordnn.IsEmpty())
    {
        MessageBox(_T("密码不能为空"));
        return;
    }
	if(m_passwordn!=m_passwordnn)
    {
        MessageBox(_T("新密码不同请重新输入"));
        return;
    }

	CString sql=_T("");

	try
	{
		
		sql.Format(_T("select * from users where username='%s' and password='%s'"),theApp.managename,m_passwordo); 

		//pRst=pCmd->Execute(NULL,NULL,adCmdText);
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
	
	

		if(pRst->rsEOF)
		{
			MessageBox(_T("旧密码不正确！")); 
		}
		else
		{
			//sql.Format(_T("UPDATE users SET password='%s'"),m_passwordn); 
			while(!pRst->rsEOF)
		{
			pRst->PutCollect("password",_variant_t(m_passwordn));
			pRst->MoveNext();
		}
			MessageBox(_T("修改成功！"));
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

}

BOOL password::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pRst.CreateInstance("ADODB.Recordset");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
