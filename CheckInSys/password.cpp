// password.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "password.h"

extern CCheckInSysApp theApp;


// password �Ի���

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


// password ��Ϣ�������

void password::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
 //       MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
 //       MessageBox( e.Description() );   
 //       MessageBox( e.ErrorMessage() );    
 //       return;   
 //   }   

	UpdateData();
	if(m_passwordo.IsEmpty() || m_passwordn.IsEmpty()||m_passwordnn.IsEmpty())
    {
        MessageBox(_T("���벻��Ϊ��"));
        return;
    }
	if(m_passwordn!=m_passwordnn)
    {
        MessageBox(_T("�����벻ͬ����������"));
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
			MessageBox(_T("�����벻��ȷ��")); 
		}
		else
		{
			//sql.Format(_T("UPDATE users SET password='%s'"),m_passwordn); 
			while(!pRst->rsEOF)
		{
			pRst->PutCollect("password",_variant_t(m_passwordn));
			pRst->MoveNext();
		}
			MessageBox(_T("�޸ĳɹ���"));
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

}

BOOL password::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pRst.CreateInstance("ADODB.Recordset");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
