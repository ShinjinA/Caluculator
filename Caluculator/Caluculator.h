
// Caluculator.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CCaluculatorApp:
// このクラスの実装については、Caluculator.cpp を参照してください
//

class CCaluculatorApp : public CWinApp
{
public:
	CCaluculatorApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCaluculatorApp theApp;
