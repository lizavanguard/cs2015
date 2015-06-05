//==============================================================================
//
// Input-Mouse [InputMouse.h]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "InputMouse.h"
#include "Framework/Utility/SafeRelease.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const int kRepeatStartTime = 60;		// リピートの連続入力開始時間
static const int kRepeatIntervalTime = 1;		// リピート入力の連続入力間隔


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
InputMouse::InputMouse( const HINSTANCE hInstance, const HWND hWnd )
	: hWnd_( hWnd )
	, Input( hInstance )
	, x_( 0 )
	, y_( 0 )
	, z_( 0 )
	, relativeX_( 0 )
	, relativeY_( 0 )
	, relativeZ_( 0 )
{
	for( int i = 0; i < kMouseButtonMax; ++i ) {
		pressButtons_[ i ] = false;
		triggerButtons_[ i ] = false;
		releaseButtons_[ i ] = false;
		repeatButtons_[ i ] = false;
		repeatCnt_[ i ] = 0;
	}

	// デバイスオブジェクトを作成
	HRESULT hr = s_pDInput_->CreateDevice( GUID_SysMouse, &pDIDevice_, nullptr );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// データフォーマットを設定
	hr = pDIDevice_->SetDataFormat( &c_dfDIMouse2 );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = pDIDevice_->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diProperty;
	diProperty.diph.dwSize = sizeof(diProperty); 
	diProperty.diph.dwHeaderSize = sizeof(diProperty.diph); 
	diProperty.diph.dwObj = 0;
	diProperty.diph.dwHow = DIPH_DEVICE;
	// 相対値モードの場合
	diProperty.dwData = DIPROPAXISMODE_REL;
	// 絶対値モードの場合
	//diProperty.dwData  = DIPROPAXISMODE_ABS;

	hr = pDIDevice_->SetProperty( DIPROP_AXISMODE, &diProperty.diph );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	pDIDevice_->Acquire();
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputMouse::~InputMouse() {
	pDIDevice_->Unacquire();
}


//------------------------------------------------
// update
//------------------------------------------------
void InputMouse::Update( void ) {
	DIMOUSESTATE2 mouseState;
	// マウスの状態の取得
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( mouseState ), &mouseState );
	if( FAILED( hr ) ) {
		// マウスデバイスの再取得
		pDIDevice_->Acquire();
		return;
	}

	// 絶対値の更新
	POINT pos;
	GetCursorPos( &pos );
	ScreenToClient( hWnd_, &pos );
	x_ = pos.x;
	y_ = pos.y;
	z_ = 0;

	// 相対値の更新
	relativeX_ = mouseState.lX;
	relativeY_ = mouseState.lY;
	relativeZ_ = mouseState.lZ;

	// 全てのキーの更新
	for( int button = 0; button < kMouseButtonMax; ++button ) {
		// 前回の情報退避
		bool pressButtonOld = pressButtons_[ button ];

		// キー情報の更新
		pressButtons_[ button ] = ( mouseState.rgbButtons[ button ] & 0x80 ) ? true : false;

		// トリガーの更新
		triggerButtons_[ button ] = ( pressButtons_[ button ] ^ pressButtonOld ) & pressButtons_[ button ];

		// リリースの更新
		releaseButtons_[ button ] = ( pressButtons_[ button ] ^ pressButtonOld ) & pressButtonOld;

		// リピートの更新
		// HACK: 構造が適当
		// リピートのクリア
		repeatButtons_[ button ] = false;
		// if キーが押されていたら
		if( pressButtons_[ button ] ) {
			// ifリピートカウンタが0なら
			if( repeatCnt_[ button ] == 0 ) {
				// リピートをオンにする
				repeatButtons_[ button ] = true;
			}
			// else if 連続入力開始時間以上かつ一定時間毎なら
			else if( ( repeatCnt_[ button ] >= kRepeatStartTime ) &&
				( repeatCnt_[ button ] % kRepeatIntervalTime == 0 ) ) {

				// リピートをオンにする
				repeatButtons_[ button ] = true;
			}
			// リピートカウンタのカウントアップ
			++repeatCnt_[ button ];
		}
		// else if リリースなら
		else if( releaseButtons_[ button ] ) {
			// リピートカウンタを0にす	る
			repeatCnt_[ button ] = 0;
		}
	}
}