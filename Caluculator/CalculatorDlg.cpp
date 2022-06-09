﻿
// CaluculatorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include "Calculate.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCalculate* cCalculate = new CCalculate;

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCaluculatorDlg ダイアログ



CCaluculatorDlg::CCaluculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALUCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaluculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, View1);
	DDX_Control(pDX, IDC_EDIT2, History);
}

BEGIN_MESSAGE_MAP(CCaluculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCaluculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCaluculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON12, &CCaluculatorDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON3, &CCaluculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON14, &CCaluculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CCaluculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CCaluculatorDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CCaluculatorDlg::OnBnClickedButton18)
END_MESSAGE_MAP()


// CCaluculatorDlg メッセージ ハンドラー

BOOL CCaluculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	/*CCalculate* cCalculate = new CCalculate;
	cCalculate->SetCCalculatePointer(cCalculate);*/

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CCaluculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CCaluculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CCaluculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCaluculatorDlg::OnBnClickedButton1()
{

	char buf[30];
	snprintf(buf, 30, "%.0f", cCalculate->ExecCalc(1));

	this->View1.SetWindowText(buf);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton2()
{
	char buf[30];
	snprintf(buf, 30, "%.0f", cCalculate->ExecCalc(2));

	this->View1.SetWindowText(buf);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton12()
{
	char buf[30];
	snprintf(buf, 30, "%.0f", cCalculate->ExecCalc(12));

	this->View1.SetWindowText(buf);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton3()
{
	cCalculate->SetView1('3');
	//char ManipulationView1[MAX_MANIPULATE_LENGHT] = { 0x00 };

	//for (int i = 0; i < cCalculate->GetView1Size(); ++i)
	//{
	//	ManipulationView1[i] = ((*cCalculate->GetView1())[i]);
	//}

	///*for (int i = 0; i < cCalculate->GetView1Size(); ++i)
	//{
	//	sprintf(&ManipulationView1[i],"%c", &(*cCalculate->GetView1())[i]);
	//}*/

	
	this->View1.SetWindowText(cCalculate->GetView1());
	//delete[] ManipulationView1;
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton14()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton15()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton17()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCaluculatorDlg::OnBnClickedButton18()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
