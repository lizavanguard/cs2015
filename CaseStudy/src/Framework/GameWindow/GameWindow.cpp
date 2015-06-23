//==============================================================================
//
// Game�p�E�B���h�E�N���X [GameWindow.cpp]
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
	// �E�B���h�E�N���X�\���̂̐���
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx( &wcex );

	// �E�B���h�E�̐���
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

	// ���Ԍv���̐��x���グ��
	timeBeginPeriod( 1 );

	// �E�B���h�E�\��
	ShowWindow( hWnd_, nCmdShow );

	// �E�B���h�E�X�V
	UpdateWindow( hWnd_ );

	// ������
	pGameImpl_->Initialize( hInstance_, hWnd_ );

	// �ނ肭��
	pCallbackTarget_ = pGameImpl_;
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameWindow::~GameWindow() {
	// �I������
	pGameImpl_->Finalize();
	delete pGameImpl_;

	// ���Ԍv���̐��x��߂�
	timeEndPeriod( 1 );
}


//------------------------------------------------
// Run
//------------------------------------------------
void GameWindow::Run( void ) {
	DWORD currentTime = timeGetTime();
	DWORD execLastTime = currentTime;

	// ���b�Z�[�W���[�v
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

      // if �o�ߎ��Ԃ����ȏ�Ȃ�
      const DWORD elapsedTime = currentTime - execLastTime;
      if ( elapsedTime >= kMSecondPerFrame) {
				// ��������������ۑ�
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

	// ���̑��̏����̓f�t�H���g�̏�����K�p
	return DefWindowProc( hWnd, msg, wParam, lParam );
}