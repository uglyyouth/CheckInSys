// CheckInSysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "CheckInSysDlg.h"
#include "LoginDlg.h"
#include "CvvImage.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/gpu/gpu.hpp"
//#include "opencv2/gpu/gpumat.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
//using namespace std;
using namespace gpu;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern CCheckInSysApp theApp;

VideoCapture cap(0);
CRect rect;  
CDC *pDC;  
HDC hDC;  
CWnd *pwnd;
CascadeClassifier faceDetector;
Mat original;
//CascadeClassifier_GPU cascade_gpu;

	

CString re=_T("");

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


// CCheckInSysDlg �Ի���




CCheckInSysDlg::CCheckInSysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckInSysDlg::IDD, pParent)

	, m_COID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckInSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_btn3);
	//DDX_Control(pDX, IDC_BUTTON1, but1);
}

BEGIN_MESSAGE_MAP(CCheckInSysDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCheckInSysDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCheckInSysDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CCheckInSysDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCheckInSysDlg ��Ϣ�������

BOOL CCheckInSysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
    pwnd = GetDlgItem(IDC_ShowFra);  
    //pwnd->MoveWindow(35,30,352,288);   
    pDC =pwnd->GetDC();  
    //pDC =GetDC();   
    hDC= pDC->GetSafeHdc();  
    pwnd->GetClientRect(&rect); 
	faceDetector.load("haarcascade_frontalface_default.xml");
	CoInitialize(NULL);
	HBITMAP  hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP13));
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap); 
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP14));
	((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap); 
	//but1.LoadBitmaps(IDB_BITMAP13,IDB_BITMAP14);
	//CascadeClassifier_GPU cascade_gpu("haarcascade_frontalface_alt.xml");

    //try                    
    //{      
    //   mpConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");
	   //mpConn->Open("","","",adConnectUnspecified);
    //}   
    //catch(_com_error e)   
    //{   
    //    MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
    //    MessageBox( e.Description() );   
    //    MessageBox( e.ErrorMessage() );    
    //    return FALSE;   
    //}  


	CTime mt = CTime::GetCurrentTime();
	int mw=mt.GetDayOfWeek()-1; 
	int mh=mt.GetHour(); 
	int mha;
	CString str=mt.Format("%Y-%m-%d  %H:%M");
	//strTime.Format(_T("%s",time.Format("%y:%m:%d %H-%M-%S")));  
	GetDlgItem(IDC_STATIC_3)->SetWindowText(str);

	if ((mw==0)|(mw==6))
	{
		mw=1;
	}

	switch(mh)
	{
	case (8):
	mha=1;
	break;
	case (9):
	mha=1;
	break;
	case (10):
	mha=2;
	break;
	case (11):
	mha=2;
	break;
	case (14):
	mha=3;
	break;
	case (15):
	mha=3;
	break;
	case (16):
	mha=4;
	break;
	case (17):
	mha=4;
	break;
	default:
	mha=1;
	}

	try
	{
		CString sql=_T("");
		sql.Format(_T("select * from course where weektime=%d and daytime=%d"),mw,mha); 
		pRst.CreateInstance("ADODB.Recordset");

		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		re=(char *)(_bstr_t)pRst->GetCollect("coursename");
		GetDlgItem(IDC_STATIC_1)->SetWindowText(re);
		re=(char *)(_bstr_t)pRst->GetCollect("CID");
		m_COID=(char *)(_bstr_t)pRst->GetCollect("ID");
		GetDlgItem(IDC_STATIC_2)->SetWindowText(re);


	}
	catch(_com_error e)///��׽�쳣
	{
		MessageBox(_T("��ȡ���ݿ�ʧ��!"));///��ʾ������Ϣ
	    MessageBox( e.Description() );   
        MessageBox( e.ErrorMessage() );  
	}

	pRst->Close();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCheckInSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCheckInSysDlg::OnPaint()
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
HCURSOR CCheckInSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCheckInSysDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!cap.isOpened()) {
			cap.open(0);
       
    }

	    if(!cap.isOpened()) {
        MessageBox(_T("��⣬����ͷ�޷��򿪣���������ͷ"));
       
    }
		m_btn3.ShowWindow(SW_SHOW);

		cap >> original;

		IplImage Iframe = IplImage(original);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
    {  
        m_CvvImage.DrawToHDC(hDC, &rect);  
        //cvWaitKey(10);   
    }  
		SetTimer(1,10,NULL);  


//���ԣ�������Ƶ
		//for(;;) 
		//{
  //      cap >> frame;
  //      // Clone the current frame:
  //      Mat original = frame.clone();
  //      // Convert the current frame to grayscale:
  //      Mat gray;
  //      cvtColor(original, gray, CV_BGR2GRAY);


  //      // Show the result:
  //      imshow("face_recognizer", original);
  //      // And display it:
  //      char key = (char) waitKey(20);
  //      // Exit this loop on escape:
  //      if(key == 27)
  //          break;
		//}




}

void CCheckInSysDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cap.release();
	LoginDlg ldlg;
	ldlg.DoModal();

}

void CCheckInSysDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime mt = CTime::GetCurrentTime();

	CString str=mt.Format("%Y-%m-%d  %H:%M");
	//strTime.Format(_T("%s",time.Format("%y:%m:%d %H-%M-%S")));  
	GetDlgItem(IDC_STATIC_3)->SetWindowText(str);

	//	Mat original;
	cap >> original;


	IplImage Iframe = IplImage(original);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(&Iframe,1);     
    if (true)  
    {  
        m_CvvImage.DrawToHDC(hDC, &rect);  
        //cvWaitKey(10);   
    }  

	CDialog::OnTimer(nIDEvent);
}

void CCheckInSysDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		m_btn3.ShowWindow(SW_HIDE);


//shrink the image
		const int DETECTION_WIDTH = 320;
		Mat smallImg;
		float scale =original.cols / (float) DETECTION_WIDTH;
		if (original.cols > DETECTION_WIDTH) {
	
		int scaledHeight = cvRound(original.rows / scale);
		resize(original, smallImg, Size(DETECTION_WIDTH, scaledHeight));
		}
		else {
			   smallImg = original;
		   }


		Mat gray;
		   if (smallImg.channels() == 3) {
			   cvtColor(smallImg, gray, CV_BGR2GRAY);
		   }
		   else if (smallImg.channels() == 4) {
			   cvtColor(smallImg, gray, CV_BGRA2GRAY);
		}
		else {
			   // Access the grayscale input image directly.
		gray = smallImg; }

		
		int flags = CASCADE_SCALE_IMAGE; 
		Size minFeatureSize(20, 20); 
		float searchScaleFactor = 1.1f;  
		int minNeighbors = 4;           
		std::vector<Rect> faces;
		faceDetector.detectMultiScale(gray, faces, searchScaleFactor,minNeighbors, flags, minFeatureSize);
		CString renname=_T("");
		CString banname=_T("");
		CString rid2=_T("");
		string rid;
		//CoInitialize(NULL);


		//try                    
		//{      
		//   mpConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");
		//   mpConn->Open("","","",adConnectUnspecified);
		//}   
		//catch(_com_error e)   
		//{   
		//	MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
		//	MessageBox( e.Description() );   
		//	MessageBox( e.ErrorMessage() );    
		//	return;   
		//}  

		
//ѡ��Fisherface�ķ�����
		//Ptr<FaceRecognizer> model = createFisherFaceRecognizer();

		//�˴�����LBPH
		Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
		model->load("face_LBPH.xml");
		int im_width = (imread("pic/s1/1.bmp")).cols;
		int im_height =(imread("pic/s1/1.bmp")).rows;


		//if (smallImg.cols > 320) {
		//	   for (int i = 0; i < (int)faces.size(); i++ ) {
		//		   faces[i].x = cvRound(faces[i].x * scale);
		//		   faces[i].y = cvRound(faces[i].y * scale);
		//		   faces[i].width = cvRound(faces[i].width * scale);
		//		   faces[i].height = cvRound(faces[i].height * scale);
		//} }
		//  
		//   for (int i = 0; i < (int)faces.size(); i++ ) {
		//	   if (faces[i].x < 0)
		//		   faces[i].x = 0;
		//	   if (faces[i].y < 0)
		//		   faces[i].y = 0;
		//	   if (faces[i].x + faces[i].width > smallImg.cols)
		//		   faces[i].x = smallImg.cols - faces[i].width;
		//	   if (faces[i].y + faces[i].height > smallImg.rows)
		//		   faces[i].y = smallImg.rows - faces[i].height;
		//}

			if(faces.size()<1){
			cap.release();
			MessageBox(_T("û�м�⵽�����������´�����ͷ"));
			}
			else{
	
			for(int i = 0; i < faces.size(); i++) {

				Rect face_i = faces[i];
				Mat face = gray(face_i);
				Mat face_resized;
				cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
				int prediction = model->predict(face_resized);

					try
					{
						CString sqlb=_T("");
						sqlb.Format(_T("select * from people where faceflag=%d"),prediction); 
						//pRst.CreateInstance("ADODB.Recordset");
						pRst->Open(_variant_t(sqlb),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		
						renname=(char *)(_bstr_t)pRst->GetCollect("name");		
						banname=(char *)(_bstr_t)pRst->GetCollect("CID");	
						rid=(char *)(_bstr_t)pRst->GetCollect("ID");
						rid2=(char *)(_bstr_t)pRst->GetCollect("ID");
						if(banname!=re)
						{
						MessageBox(_T("ͬѧ����������ô�����ڻ��������Ͽ�Ŷ!"));
							cap.release();
							pRst->Close();
							return;
						}
						pRst->Close();

						CTime mtu = CTime::GetCurrentTime();
						CString strTime;
						strTime = mtu.Format("%Y/%m/%d");

						CString sqln;
						long newid;
						sqln.Format(_T("select * from state"));
						pRst->Open(_variant_t(sqln),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
						pRst->MoveLast();
						//mid.Format((_bstr_t)pRst->GetCollect("ID"));
						_variant_t vIndex = (long)0;
						_variant_t vtemp =pRst->GetCollect("ID");
						newid =(long)(pRst->GetCollect(vIndex))+1;


						bool show=true;


						 try
						 {
						  pRst->AddNew();       //�������
						  pRst->PutCollect("ID",(_bstr_t)newid);
						  pRst->PutCollect("PID",(_bstr_t)rid2);
						  pRst->PutCollect("COID",(_bstr_t)m_COID);
						  pRst->PutCollect("sday",(_bstr_t)strTime);
						  pRst->PutCollect("show",(_bstr_t)show);
						  pRst->Update();       //�������ݱ��¼
						  pRst->Close();

						 }
						 catch(...)            //��׽���ܳ��ֵĴ���
						 {
						  MessageBox(_T("����ʧ��"));        //����������ʾ
						  pRst->Close();
						  return;
						 }

						GetDlgItem(IDC_STATIC_4)->SetWindowText(renname);

					}
					catch(_com_error e)///��׽�쳣
					{
						MessageBox(_T("��ȡ���ݿ�ʧ��!"));///��ʾ������Ϣ
						MessageBox( e.Description() );   
						MessageBox( e.ErrorMessage() );  
					}



				rectangle(smallImg, face_i, CV_RGB(0, 255,0), 1);
				//string box_text = format(" %s", &rid);
  
            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);

            putText(smallImg, rid, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0,TRUE);

	           
			}

				//pRst->Close();

		IplImage Iframe = IplImage(smallImg);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC, &rect);   
		}  
		cap.release();
			}

////����ΪGPU�����������
//		GpuMat image_gpu(gray);
//
//		GpuMat objbuf;
//		int detections_number = cascade_gpu.detectMultiScale( image_gpu,objbuf, 1.2);
//		Mat obj_host;
//
//		objbuf.colRange(0, detections_number).download(obj_host);
//
//		Rect* faces = obj_host.ptr<Rect>();
//
//
//
//		if(detections_number<1){
//		cap.release();
//		MessageBox(_T("û�м�⵽�����������´�����ͷ"));
//		}
//		else{
//
//			for(int i = 0; i < detections_number; i++) {
//
//				//Rect face_i = faces[i];
//				//Mat face = gray(face_i);
//				//Mat face_resized;
//
//	//            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
//	            
//			   // int prediction = model->predict(face_resized);
//	           
//		//	CPU
//				//rectangle(original, face_i, CV_RGB(0, 255,0), 1);
//				cv::rectangle(original, faces[i], Scalar(255));
//
//	           
//			   // string box_text = format("Prediction = %d", prediction);
//
//				//int pos_x = std::max(face_i.tl().x - 10, 0);
//				//int pos_y = std::max(face_i.tl().y - 10, 0);
//
//			   // putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
//			}
//			IplImage Iframe = IplImage(original);
//			CvvImage m_CvvImage;
//			m_CvvImage.CopyOf(&Iframe,1);     
//			if (true)  
//			{  
//				m_CvvImage.DrawToHDC(hDC, &rect);  
//				//cvWaitKey(10);   
//			}  
//			cap.release();
//		}
//
//
//



////��ͨ�������
//		vector< Rect_<int> > faces;
//        faceDetector.detectMultiScale(gray, faces,1.5);
//
//
//		if(faces.size()<1){
//		cap.release();
//		MessageBox(_T("û�м�⵽�����������´�����ͷ"));
//		}
//		else{
//
//			for(int i = 0; i < faces.size(); i++) {
//
//				Rect face_i = faces[i];
//				Mat face = gray(face_i);
//				Mat face_resized;
//
//	//            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
//	            
//			   // int prediction = model->predict(face_resized);
//	           
//				rectangle(original, face_i, CV_RGB(0, 255,0), 1);
//	           
//			   // string box_text = format("Prediction = %d", prediction);
//
//				//int pos_x = std::max(face_i.tl().x - 10, 0);
//				//int pos_y = std::max(face_i.tl().y - 10, 0);
//
//			   // putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
//			}
//			IplImage Iframe = IplImage(original);
//			CvvImage m_CvvImage;
//			m_CvvImage.CopyOf(&Iframe,1);     
//			if (true)  
//			{  
//				m_CvvImage.DrawToHDC(hDC, &rect);  
//				//cvWaitKey(10);   
//			}  
//			cap.release();
//		}
		

}
