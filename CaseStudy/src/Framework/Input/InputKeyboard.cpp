//==============================================================================
//
// Input-Keyboard [InputKeyboard.h]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "InputKeyboard.h"
#include "Framework/Utility/SafeRelease.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
	const int kRepeatStartTime = 60;		// リピートの連続入力開始時間
	const int kRepeatIntervalTime = 1;		// リピート入力の連続入力間隔
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
InputKeyboard::InputKeyboard( HINSTANCE hInstance, HWND hWnd ) : Input( hInstance ) {
	// initialize
	for( int i = 0; i < kKeyboardMax; ++i ) {
		isPressKeys_[ i ] = false;
		isTriggerKeys_[ i ] = false;
		isReleaseKeys_[ i ] = false;
		isRepeatKeys_[ i ] = false;
		repeatCnts_[ i ] = 0;
	}

	// デバイスオブジェクトを作成
	HRESULT hr = s_pDInput_->CreateDevice( GUID_SysKeyboard, &pDIDevice_, nullptr );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// データフォーマットを設定
	hr = pDIDevice_->SetDataFormat( &c_dfDIKeyboard );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = pDIDevice_->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	pDIDevice_->Acquire();
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputKeyboard::~InputKeyboard() {
	pDIDevice_->Unacquire();
}


//------------------------------------------------
// update
//------------------------------------------------
void InputKeyboard::Update( void ) {
	BYTE keyCntStates_[ kKeyboardMax ];	// 一時的な情報配列

	// キーボードの状態の取得
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( keyCntStates_ ), &keyCntStates_[ 0 ] );

	// if キーボードの状態の取得に成功なら
	if( SUCCEEDED( hr ) ) {
		// 全てのキーの更新
		for( int keyCnt = 0; keyCnt < kKeyboardMax; ++keyCnt ) {
			// 前回の情報退避
			bool pressKeyOld = isPressKeys_[ keyCnt ];

			// キー情報の更新
			isPressKeys_[ keyCnt ] = ( keyCntStates_[ keyCnt ] & 0x80 ) ? true : false;

			// トリガーの更新
			isTriggerKeys_[ keyCnt ] = ( isPressKeys_[ keyCnt ] ^ pressKeyOld ) & isPressKeys_[ keyCnt ];

			// リリースの更新
			isReleaseKeys_[ keyCnt ] = ( isPressKeys_[ keyCnt ] ^ pressKeyOld ) & pressKeyOld;

			// リピートの更新
			// リピートのクリア
			isRepeatKeys_[ keyCnt ] = false;
			// if キーが押されていたら
			if( isPressKeys_[ keyCnt ] ) {
				// ifリピートカウンタが0なら
				if( repeatCnts_[ keyCnt ] == 0 ) {
					// リピートをオンにする
					isRepeatKeys_[ keyCnt ] = true;
				}
				// else if 連続入力開始時間以上かつ一定時間毎なら
				else if( ( repeatCnts_[ keyCnt ] >= kRepeatStartTime ) &&
					( repeatCnts_[ keyCnt ] % kRepeatIntervalTime == 0 ) ) {

					// リピートをオンにする
					isRepeatKeys_[ keyCnt ] = true;
				}
				// リピートカウンタのカウントアップ
				++repeatCnts_[ keyCnt ];
			}
			// else if リリースなら
			else if( isReleaseKeys_[ keyCnt ] ) {
				// リピートカウンタを0にする
				repeatCnts_[ keyCnt ] = 0;
			}
		}
	}

	else {
		pDIDevice_->Acquire();
	}
}