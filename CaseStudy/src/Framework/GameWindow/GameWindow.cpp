//==============================================================================
//
// Game用ウィンドウクラス [GameWindow.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameWindow.h"
#include <MMSystem.h>
#pragma comment( lib, "winmm.lib" )
#include "Framework\FrameworkOption.h"
#include "GameBase.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
	const char* kWindowClassName = "WindowClassName";
	const float kSecondPerFrame = 1 / kFPS;
	const float kMSecondPerFrame = 1000 / kFPS;
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
GameBase* GameWindow::pCallbackTarget_ = nullptr;


//------------------------------------------------
// ctor
//------------------------------------------------
GameWindow::GameWindow(
	HINSTANCE hInstance,
	const int nCmdShow,
	const char* pWindowCaption,
	const unsigned int windowWidth,
	const unsigned int windowHeight,
	GameBase* pGameImpl
)
	: hInstance_( hInstance )
	, hWnd_( nullptr )
	, pGameImpl_( pGameImpl )
{
	// ウィンドウクラス構造体の生成
	WNDCLASSEX wcex = {
		sizeof( WNDCLASSEX ),
		CS_CLASSDC,
		LocalWindowProcedure,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor( NULL, IDC_ARROW ),
		( HBRUSH )( COLOR_WINDOW + 1 ),
		NULL,
		kWindowClassName,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx( &wcex );

	// ウィンドウの生成
	hWnd_ = CreateWindowEx(
		0,
		kWindowClassName,
		pWindowCaption,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	// 時間計測の精度を上げる
	timeBeginPeriod( 1 );

	// ウィンドウ表示
	ShowWindow( hWnd_, nCmdShow );

	// ウィンドウ更新
	UpdateWindow( hWnd_ );

	// 初期化
	pGameImpl_->Initialize( hInstance_, hWnd_ );

	// むりくり
	pCallbackTarget_ = pGameImpl_;
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameWindow::~GameWindow() {
	// 終了処理
	pGameImpl_->Finalize();
	delete pGameImpl_;

	// 時間計測の精度を戻す
	timeEndPeriod( 1 );
}


//------------------------------------------------
// Run
//------------------------------------------------
void GameWindow::Run( void ) {
	DWORD currentTime = timeGetTime();
	DWORD execLastTime = currentTime;

	// メッセージループ
	MSG msg;
	while( true ) {
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ) {
			if( msg.message == WM_QUIT ) {
				break;
			}
			else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else {
			currentTime = timeGetTime();

      // if 経過時間が一定以上なら
      const DWORD elapsedTime = currentTime - execLastTime;
      if ( elapsedTime >= kMSecondPerFrame) {
				// 処理した時刻を保存
				execLastTime = currentTime;

				// Update
        const float elapsedTimeFloat = elapsedTime * 0.001f;
        pGameImpl_->Update(elapsedTimeFloat);

				// Draw
				pGameImpl_->Draw();
			}
		}
	}
}


//------------------------------------------------
// Window-Procedure
//------------------------------------------------
LRESULT CALLBACK GameWindow::LocalWindowProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	if( pCallbackTarget_ ) {
		return pCallbackTarget_->WndProc( hWnd, msg, wParam, lParam );
	}

	// その他の処理はデフォルトの処理を適用
	return DefWindowProc( hWnd, msg, wParam, lParam );
}