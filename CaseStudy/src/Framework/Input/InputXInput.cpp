//==============================================================================
//
// XInput用 [InputXInput.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "windows.h"
#include "InputXInput.h"
#pragma comment( lib, "Xinput.lib" )
#include "Framework/Utility/SafeDelete.h"
#include "Framework/Utility/MathUtility.hpp"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
	const int kRepeatStartTime = 60;	// リピートの連続入力開始時間
	const int kRepeatIntervalTime = 1;	// リピート入力の連続入力間隔

	// パッドボタンからXInputボタンへの対応テーブル
	const DWORD kPadToXInputTbl[ InputDevice::kPadMax ] = {
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		-1,
		-1,
		XINPUT_GAMEPAD_LEFT_THUMB,
		XINPUT_GAMEPAD_RIGHT_THUMB,
		XINPUT_GAMEPAD_BACK,
		XINPUT_GAMEPAD_START,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
	};
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
unsigned int InputXInput::padCnt_ = 0;


//------------------------------------------------
// ctor
//------------------------------------------------
InputXInput::InputXInput( HINSTANCE hInstance )
	: InputDevice( hInstance )
	, padID_( -1 )
	, timeFFB_( 0 )
	, isConnect_( false )
	, isGeneratingFFB_( false )
{

	// XInput有効にする
	XInputEnable( TRUE );

	// PADに管理用IDを振る
	padID_ = InputXInput::padCnt_;

	// パッドの数を更新
	++padCnt_;

	// XInputの能力を取得
	XINPUT_CAPABILITIES capability;
	DWORD result = XInputGetCapabilities( padID_, XINPUT_FLAG_GAMEPAD, &capability );
	
	// 使用の可否を更新
	SetEnable( result == ERROR_SUCCESS );

	// 振動をON
	SetEnableFFB( true );
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputXInput::~InputXInput() {
	XINPUT_VIBRATION vibration = { 0, 0 };
	XInputSetState( padID_, &vibration );

	// XInput無効にする
	XInputEnable( FALSE );
}


//------------------------------------------------
// Update
//------------------------------------------------
void InputXInput::Update( void ) {
	// Pad状態取得
	XINPUT_STATE xPadState;
	DWORD result = XInputGetState( padID_, &xPadState );
	// if エラーなら 未接続状態にする
	if( result != ERROR_SUCCESS ) {
		isConnect_ = false;
		return;
	}

	// 接続状態にする
	isConnect_ = true;

	// 前回の情報退避
	bool pressKeyOlds[ kPadMax ];
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		pressKeyOlds[ padCnt ] = isPressPads_[ padCnt ];
	}

	// プレス情報の更新
	const WORD padButtonBit = xPadState.Gamepad.wButtons;
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		if( kPadToXInputTbl[ padCnt_ ] != -1 ) {
			isPressPads_[ padCnt ] = padButtonBit & kPadToXInputTbl[ padCnt ] ? true : false;
		}
	}
	isPressPads_[ PAD_LT ] = xPadState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	isPressPads_[ PAD_RT ] = xPadState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	isPressPads_[ PAD_LTHUMB_UP ] = xPadState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	isPressPads_[ PAD_LTHUMB_DOWN ] = xPadState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	isPressPads_[ PAD_LTHUMB_LEFT ] = xPadState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	isPressPads_[ PAD_LTHUMB_RIGHT ] = xPadState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	isPressPads_[ PAD_LTHUMB_ANY ] =
		isPressPads_[ PAD_LTHUMB_UP ] || isPressPads_[ PAD_LTHUMB_DOWN ] ||
		isPressPads_[ PAD_LTHUMB_LEFT ] || isPressPads_[ PAD_LTHUMB_RIGHT ];
	isPressPads_[ PAD_RTHUMB_UP ] = xPadState.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	isPressPads_[ PAD_RTHUMB_DOWN ] = xPadState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	isPressPads_[ PAD_RTHUMB_LEFT ] = xPadState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	isPressPads_[ PAD_RTHUMB_RIGHT ] = xPadState.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	isPressPads_[ PAD_RTHUMB_ANY ] =
		isPressPads_[ PAD_RTHUMB_UP ] || isPressPads_[ PAD_RTHUMB_DOWN ] ||
		isPressPads_[ PAD_RTHUMB_LEFT ] || isPressPads_[ PAD_RTHUMB_RIGHT ];

	// パッド情報の更新
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		// 前回の情報退避
		bool pressKeyOld = pressKeyOlds[ padCnt ];

		// トリガーの更新
		isTriggerPads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressKeyOld ) & isPressPads_[ padCnt ];

		// リリースの更新
		isReleasePads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressKeyOld ) & pressKeyOld;

		// リピートの更新
		// リピートのクリア
		isRepeatPads_[ padCnt ] = false;
		// if キーが押されていたら
		if( isPressPads_[ padCnt ] ) {
			// ifリピートカウンタが0なら
			if( repeatCnts_[ padCnt ] == 0 ) {
				// リピートをオンにする
				isRepeatPads_[ padCnt ] = true;
			}
			// else if 連続入力開始時間以上かつ一定時間毎なら
			else if(
				( repeatCnts_[ padCnt ] >= kRepeatStartTime ) &&
				( repeatCnts_[ padCnt ] % kRepeatIntervalTime == 0 )
			) {
				// リピートをオンにする
				isRepeatPads_[ padCnt ] = true;
			}
			// リピートカウンタのカウントアップ
			++repeatCnts_[ padCnt ];
		}
		// else if リリースなら
		else if( isReleasePads_[ padCnt ] ) {
			// リピートカウンタを0にする
			repeatCnts_[ padCnt ] = 0;
		}
	}

	// トリガーの情報
	float lTriggerOld = lTrigger_;
	float rTriggerOld = rTrigger_;
	lTrigger_ = xPadState.Gamepad.bLeftTrigger;
	rTrigger_ = xPadState.Gamepad.bRightTrigger;
	lVTrigger_ = lTrigger_ - lTriggerOld;
	rVTrigger_ = rTrigger_ - rTriggerOld;

	// アナログスティックの情報
	float lXOld = lX_;
	float lYOld = lY_;
	float rXOld = rX_;
	float rYOld = rY_;
	lX_ = xPadState.Gamepad.sThumbLX;
	lY_ = xPadState.Gamepad.sThumbLY;
	rX_ = xPadState.Gamepad.sThumbRX;
	rY_ = xPadState.Gamepad.sThumbRY;
	lVx_ = lX_ - lXOld;
	lVy_ = lY_ - lYOld;
	rVx_ = rX_ - rXOld;
	rVy_ = rY_ - rYOld;

	// FFB中なら
	if( isGeneratingFFB_ ) {
		// if 時間経過なら 振動を止める
		if( timeFFB_ < 0 ) {
			XINPUT_VIBRATION vibration = { 0, 0 };
			XInputSetState( padID_, &vibration );
			isGeneratingFFB_ = false;
		}

		// HACK: UPDATEの引数に渡すとかな
		timeFFB_ -= 0.016f;
	}
}


//------------------------------------------------
// set
//------------------------------------------------
void InputXInput::SetFFB( const float left, const float right, const float time ) {
	// if 接続していなら終了
	if( !isConnect_ ) {
		return;
	}

	// if 振動が無効なら終了
	if( !IsEnableFFB() ) {
		return;
	}

	// 値を0~65535に丸める
	float leftRate = liza::math::Clamp( left, 0.0f, 1.0f );
	float rightRate = liza::math::Clamp( right, 0.0f, 1.0f );
	timeFFB_ = time;

	// 振動の設定
	XINPUT_VIBRATION vibration = {
		(WORD)( leftRate * 65535 ),
		(WORD)( rightRate * 65535 )
	};
	XInputSetState( padID_, &vibration );
	isGeneratingFFB_ = true;
}