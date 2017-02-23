// VideoCam.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "CheckInSysDlg.h"
#include "VideoCam.h"
#include "CvvImage.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"


#include <iostream>
#include <fstream>
#include <sstream>
extern CCheckInSysApp theApp;
using namespace cv;
using namespace std;
using namespace gpu;



VideoCapture capb;
CRect rectv;  
CDC *pDCv;  
HDC hDCv;  
CWnd *pwndv;
CascadeClassifier faceDetectorv;
Mat originalv;
Mat mpic1;
Mat mpic2;
Mat mpic3;
Mat mpic4;
Mat mpic5;
Mat mpic6;




// VideoCam 对话框

IMPLEMENT_DYNAMIC(VideoCam, CDialog)

VideoCam::VideoCam(CWnd* pParent /*=NULL*/)
	: CDialog(VideoCam::IDD, pParent)
	, pics1(false)
	, pics2(false)
	, pics3(false)
	, pics4(false)
	, pics5(false)
	, pics6(false)
	, m_name(_T(""))
	, m_classname(_T(""))
{


}

VideoCam::~VideoCam()
{
}

void VideoCam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_CBString(pDX, IDC_COMBO1, m_classname);
}


BEGIN_MESSAGE_MAP(VideoCam, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &VideoCam::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON2, &VideoCam::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &VideoCam::OnBnClickedButton3)
END_MESSAGE_MAP()


// VideoCam 消息处理程序

void VideoCam::OnBnClickedButton1()
{


	//// TODO: 在此添加控件通知处理程序代码

	if(!capb.isOpened()) {
	capb.open(0);
	}

    if(!capb.isOpened()) {
    MessageBox(_T("糟糕，摄像头无法打开"));
   
	}

	capb >> originalv;

	IplImage Iframe = IplImage(originalv);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(&Iframe,1);     
	if (true)  
	{  
    m_CvvImage.DrawToHDC(hDCv, &rectv);    
	}  



	
////调试，弹出视频
//	Mat frame;
//	VideoCapture capq(0);
//	for(;;) 
//	{
//    capq >> frame;
//     Clone the current frame:
//    Mat original = frame.clone();
//     Convert the current frame to grayscale:
//    Mat gray;
//    cvtColor(original, gray, CV_BGR2GRAY);
//
//
//     Show the result:
//    imshow("face_recognizer", original);
//     And display it:
//    char key = (char) waitKey(20);
//     Exit this loop on escape:
//    if(key == 27)
//        break;
//	}



	SetTimer(1,10,NULL);  


}

void VideoCam::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	capb >> originalv;

	IplImage Iframe = IplImage(originalv);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(&Iframe,1);     
	if (true)  
	{  
		m_CvvImage.DrawToHDC(hDCv, &rectv);  
	}  

	CDialog::OnTimer(nIDEvent);
}

void VideoCam::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	//capv.open(0);
	pwndv = GetDlgItem(IDC_ShowFraV);  
    pDCv =pwndv->GetDC();    
    hDCv= pDCv->GetSafeHdc();  
    pwndv->GetClientRect(&rectv); 
	faceDetectorv.load("haarcascade_frontalface_default.xml");
	pics1=TRUE;
	pics2=TRUE;
	pics3=TRUE;
	pics4=TRUE;
	pics5=TRUE;
	pics6=TRUE;
}

void VideoCam::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(pics1)
	{
		mpic1=originalv.clone();
		cvtColor(mpic1, mpic1, CV_BGR2GRAY);

		pics1=FALSE;
		CRect rect;  
		CWnd *pwnd=GetDlgItem(IDC_pic1); 
		CDC *pDC=pwnd->GetDC();
		HDC hDC= pDC->GetSafeHdc();
		pwnd->GetClientRect(&rect);

		IplImage Iframe = IplImage(mpic1);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC, &rect);  
		}  
		}else if(pics2)
		{  
		mpic2=originalv.clone();
		cvtColor(mpic2, mpic2, CV_BGR2GRAY);
		pics2=FALSE;
		CRect rect2;  
		CWnd *pwnd2=GetDlgItem(IDC_pic2); 
		CDC *pDC2=pwnd2->GetDC();
		HDC hDC2= pDC2->GetSafeHdc();
		pwnd2->GetClientRect(&rect2);

		IplImage Iframe = IplImage(mpic2);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC2, &rect2);  
		}  

		}else if(pics3)
		{
		mpic3=originalv.clone();
		cvtColor(mpic3, mpic3, CV_BGR2GRAY);
		pics3=FALSE;
		CRect rect3;  
		CWnd *pwnd3=GetDlgItem(IDC_pic3); 
		CDC *pDC3=pwnd3->GetDC();
		HDC hDC3= pDC3->GetSafeHdc();
		pwnd3->GetClientRect(&rect3);

		IplImage Iframe = IplImage(mpic3);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);      
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC3, &rect3);  
		} 


		}else if(pics4)
		{  
		mpic4=originalv.clone();
		cvtColor(mpic4, mpic4, CV_BGR2GRAY);
		pics4=FALSE;
		CRect rect4;  
		CWnd *pwnd4=GetDlgItem(IDC_pic4); 
		CDC *pDC4=pwnd4->GetDC();
		HDC hDC4= pDC4->GetSafeHdc();
		pwnd4->GetClientRect(&rect4);

		IplImage Iframe = IplImage(mpic4);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC4, &rect4);  
		}
		}else if(pics5)
		{  
		mpic5=originalv.clone();
		cvtColor(mpic5, mpic5, CV_BGR2GRAY);
		pics5=FALSE;
		CRect rect5;  
		CWnd *pwnd5=GetDlgItem(IDC_pic5); 
		CDC *pDC5=pwnd5->GetDC();
		HDC hDC5= pDC5->GetSafeHdc();
		pwnd5->GetClientRect(&rect5);

		IplImage Iframe = IplImage(mpic5);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC5, &rect5);  
		}
		}else if(pics6)
		{  
		mpic6=originalv.clone();
		cvtColor(mpic6, mpic6, CV_BGR2GRAY);
		pics6=FALSE;
		CRect rect6;  
		CWnd *pwnd6=GetDlgItem(IDC_pic6); 
		CDC *pDC6=pwnd6->GetDC();
		HDC hDC6= pDC6->GetSafeHdc();
		pwnd6->GetClientRect(&rect6);

		IplImage Iframe = IplImage(mpic6);
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(&Iframe,1);     
		if (true)  
		{  
			m_CvvImage.DrawToHDC(hDC6, &rect6);  
		}  		
		capb.release();
		}
		else
		{
			MessageBox(_T("只需要六张照片哦~"));

		}

}

void VideoCam::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_name.IsEmpty())
    {
        MessageBox(_T("请填写姓名"));
        return;
    }

	CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_classname,0,'-'); 

	vector<Mat> images;
	vector<int> labels;

	//images.push_back(mpic1); 
	//labels.push_back(1);
	//images.push_back(mpic2);
	//labels.push_back(1);
	//images.push_back(mpic3);
	//labels.push_back(1);
	//images.push_back(mpic4); 
	//labels.push_back(1);
	//images.push_back(mpic5);
	//labels.push_back(1);
	//images.push_back(mpic6);
	//labels.push_back(1);



	int im_width = (imread("pic/s1/1.bmp")).cols;
    int im_height =(imread("pic/s1/1.bmp")).rows;

	CascadeClassifier haar_cascade;
    haar_cascade.load("haarcascade_frontalface_default.xml");

	vector< Rect_<int> > faces;
    haar_cascade.detectMultiScale(mpic1, faces);
	Mat face_resized;
	for(int i = 0; i < faces.size(); i++) {

    Rect face_i = faces[i];
	Mat face = mpic1(face_i);
    cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}

	vector< Rect_<int> > faces2;
    haar_cascade.detectMultiScale(mpic2, faces2);
	Mat face_resized2;
	for(int i = 0; i < faces2.size(); i++) {

    Rect face2_i = faces2[i];
	Mat face2 = mpic2(face2_i);
    cv::resize(face2, face_resized2, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}

	vector< Rect_<int> > faces3;
    haar_cascade.detectMultiScale(mpic3, faces3);
	Mat face_resized3;
	for(int i = 0; i < faces3.size(); i++) {

    Rect face3_i = faces3[i];
	Mat face3 = mpic3(face3_i);
    cv::resize(face3, face_resized3, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}

	vector< Rect_<int> > faces4;
    haar_cascade.detectMultiScale(mpic4, faces4);
	Mat face_resized4;
	for(int i = 0; i < faces4.size(); i++) {

    Rect face4_i = faces4[i];
	Mat face4 = mpic4(face4_i);
    cv::resize(face4, face_resized4, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}


	vector< Rect_<int> > faces5;
    haar_cascade.detectMultiScale(mpic5, faces5);
	Mat face_resized5;
	for(int i = 0; i < faces5.size(); i++) {

    Rect face5_i = faces5[i];
	Mat face5 = mpic5(face5_i);
    cv::resize(face5, face_resized5, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}


	vector< Rect_<int> > faces6;
    haar_cascade.detectMultiScale(mpic6, faces6);
	Mat face_resized6;
	for(int i = 0; i < faces6.size(); i++) {

    Rect face6_i = faces6[i];
	Mat face6 = mpic6(face6_i);
    cv::resize(face6, face_resized6, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

	}




	
	char separator = ';';
	const string filename="at.txt";
    std::ifstream file(filename.c_str(), ifstream::in);


    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;

    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);

        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }



		CString sql=_T("");
		CString stuID=_T("");
		CString CID=_T("");
		int num=1;
		int allpeo=0;

		sql.Format(_T("select * from people where CID='%s'"),csTemp);
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		while(!pRst->rsEOF)
		{
			num++;
			pRst->MoveNext();
		}
		if(num>=9){
		stuID.Format(csTemp+_T("%d"),num);
		}else{
		stuID.Format(csTemp+_T("0")+_T("%d"),num);
		}
		pRst->Close();


		sql.Format(_T("select * from people"));
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		while(!pRst->rsEOF)
		{
			allpeo++;
			pRst->MoveNext();
		}
		pRst->Close();


		//sql.Format(_T("insert into people(ID,name,CID,faceflag) values('%s','%s','%s',%d)"),stuID,m_name,csTemp,allpeo);
		//pRst->Execute(sql,&RecordsAffected,adCmdText);



		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		pRst->AddNew();
 		pRst->PutCollect("ID", _variant_t(stuID));
		pRst->PutCollect("name", _variant_t(m_name));
		pRst->PutCollect("CID", _variant_t(csTemp));
  		pRst->PutCollect("faceflag", allpeo);
 		pRst->Update();

		pRst->Close();
		sql.Format(_T("成功录入学生'%s'的信息"),m_name);
		MessageBox(sql);

		//num++;
		//CString strpath;
		//CString strpath1=_T("pic\\s");
		//strpath.Format(strpath1+_T("%d"),num);
		//CreateDirectory(strpath, NULL);
		//string strinfo="pic\\s24\\1.bmp";

		//imwrite(strinfo, face_resized);
		//strinfo="pic\\s24\\2.bmp";
		//imwrite(strinfo,  face_resized2);
		//strinfo="pic\\s24\\3.bmp";
		//imwrite(strinfo,  face_resized3);
		//strinfo="pic\\s24\\4.bmp";
		//imwrite(strinfo, face_resized4);
		//strinfo="pic\\s24\\5.bmp";
		//imwrite(strinfo, face_resized5);
		//strinfo="pic\\s24\\6.bmp";
		//imwrite(strinfo, face_resized6);

		imwrite("1.bmp", face_resized);
		imwrite("2.bmp", face_resized2);
		imwrite("3.bmp", face_resized3);
		imwrite("4.bmp", face_resized4);
		imwrite("5.bmp", face_resized5);
		imwrite("6.bmp", face_resized6);

	////Ptr<FaceRecognizer> model = createFisherFaceRecognizer();  
	////Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

	images.push_back(face_resized); 
	labels.push_back(allpeo);
	images.push_back(face_resized2);
	labels.push_back(allpeo);
	images.push_back(face_resized3);
	labels.push_back(allpeo);
	images.push_back(face_resized4);
	labels.push_back(allpeo);
	images.push_back(face_resized5);
	labels.push_back(allpeo);
	images.push_back(face_resized6);
	labels.push_back(allpeo);

    model->train(images, labels);
	//model->load("face_LBPH.xml");
	////////model->train(images, labels);  
	model->save("face_LBPH.xml");
	//model->update(images,labels);


}

BOOL VideoCam::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


/*    try                    
    {      
       vmpConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");
	   vmpConn->Open("","","",adConnectUnspecified);
    }   
    catch(_com_error e)   
    {   
        MessageBox(_T("数据库连接失败，确认数据库是否在当前路径下!"));   
        MessageBox( e.Description() );   
        MessageBox( e.ErrorMessage() );    
        return FALSE;   
    } */ 
		CString sql=_T("");
		CString classname=_T("");
		CString CID=_T("");
	
		sql.Format(_T("select * from class")); 
		pRst.CreateInstance("ADODB.Recordset");
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		//CID.Format((_bstr_t)vmpRst->GetCollect("ID"));
		while(!pRst->rsEOF)
		{
			classname.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("classname"));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(classname);
			pRst->MoveNext();
		}

		pRst->Close();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
