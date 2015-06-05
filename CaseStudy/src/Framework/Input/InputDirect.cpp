//==============================================================================
//
// DirectInput用 [InputDirect.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "InputDirect.h"
#include "Framework/Utility/SafeRelease.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
	const int kAxisMax = 1000;
	const int kAxisMin = -1000;
	const int kRepeatStartTime = 60;		// リピートの連続入力開始時間
	const int kRepeatIntervalTime = 1;		// リピート入力の連続入力間隔
	const int kAnalogStickThreshold = 100;	// アナログスティック用の閾値　てきとー
	const int kTriggerThreshold = 100;

	const char kPadToRGBButtonTbl[ InputDirect::kPadMax ] = {
		-1,	// PAD_UP
		-1,	// PAD_DOWN
		-1,	// PAD_LEFT
		-1,	// PAD_RIGHT
		0,	// PAD_A
		1,	// PAD_B
		2,	// PAD_X
		3,	// PAD_Y
		4,	// PAD_LB
		5,	// PAD_RB
		-1,	// PAD_LT
		-1,	// PAD_RT
		10,	// PAD_RTHUMB
		11,	// PAD_LTHUMB
		8,	// PAD_BACK
		9,	// PAD_START
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
InputDirect* InputDirect::pCallBackTarget_ = nullptr;


//------------------------------------------------
// ctor
//------------------------------------------------
InputDirect::InputDirect( HINSTANCE hInstance, HWND hWnd )
	: InputDevice( hInstance )
	, timeFFB_( 0 )
	, pDIEffect_( nullptr )
	, numForceFeedbackAxis_( 0 )
	, isGeneratingFFB_( false )
{
	// 自分自身をコールバックの対象にする
	InputDirect::SetCallBackTarget( this );

	// デバイスを列挙して作成
	// コールバック関数内部でデバイスを作成する処理を書く
	HRESULT hr = s_pDInput_->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		nullptr,
		DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY
	);
	SetEnableFFB( true );

	// if 作成が失敗したら
	if( FAILED( hr ) || pDIDevice_ == nullptr ) {
		// FFB無しで作成
		hr =  s_pDInput_->EnumDevices(
			DI8DEVCLASS_GAMECTRL,
			EnumJoysticksCallback,
			nullptr,
			DIEDFL_ATTACHEDONLY
		);
		SetEnableFFB( false );

		// それでもだめなら 終了
		if( FAILED( hr ) || pDIDevice_ == nullptr ) {
			return;
		}
	}

	// データ形式を設定
	hr = pDIDevice_->SetDataFormat( &c_dfDIJoystick2 );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr,"c_dfDIJoystick2形式の設定に失敗", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = pDIDevice_->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr, "フォアグラウンド＆非排他モードの設定に失敗", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// コールバック関数を使って各軸のモードを設定
	hr = pDIDevice_->EnumObjects( EnumAxesCallback, &numForceFeedbackAxis_, DIDFT_AXIS );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr, "軸モードの設定に失敗", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// エフェクトの設定
	DIEFFECT diEffect;
	ZeroMemory( &diEffect , sizeof( diEffect ) );
	DICONSTANTFORCE cf;
	cf.lMagnitude = DI_FFNOMINALMAX;	// Full force
	diEffect.dwSize = sizeof( DIEFFECT );
	diEffect.dwFlags = DIEFF_POLAR | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = (DWORD)( 0.5f * DI_SECONDS );
	diEffect.dwSamplePeriod = 0;	// = default
	diEffect.dwGain = DI_FFNOMINALMAX;	// No scaling
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;	// Not a button response
	diEffect.dwTriggerRepeatInterval = 0;	// Not applicable
	diEffect.cAxes = 2;
	DWORD rgdwAxes[ 2 ] = { DIJOFS_X , DIJOFS_Y };
	diEffect.rgdwAxes = &rgdwAxes[ 0 ];
	LONG rglDirection[ 2 ] = { 1 , 1 };
	diEffect.rglDirection = &rglDirection[ 0 ];
	diEffect.lpEnvelope = nullptr;
	diEffect.cbTypeSpecificParams = sizeof( DICONSTANTFORCE );
	DICONSTANTFORCE diConstantForce;
	diEffect.lpvTypeSpecificParams = &diConstantForce;

	// エフェクトの作成
	pDIDevice_->CreateEffect( GUID_ConstantForce, &diEffect, &pDIEffect_, nullptr );

	// 入力制御開始
	pDIDevice_->Acquire();
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputDirect::~InputDirect() {
	if( pDIEffect_ ) {
		pDIEffect_->Start( 0, 0 );
	}
	SafeRelease( pDIEffect_ );
}


//------------------------------------------------
// Update
//------------------------------------------------
void InputDirect::Update( void ) {

	// デバイスが存在しないなら 終了
	if( pDIDevice_ == nullptr ) {
		return;
	}

	// ジョイパッドデータのポーリング
	pDIDevice_->Poll();

	// 入力の受付開始
	pDIDevice_->Acquire();

	// 値の取得
	DIJOYSTATE2 diJoyState;
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( DIJOYSTATE2 ), &diJoyState );
	if( FAILED( hr ) ) {
		// if デバイスロストなら再取得
		if( hr == DIERR_INPUTLOST ) {
			pDIDevice_->Acquire();
		}
		return;
	}

	// 前回の情報を保存
	bool pressOldKeys[ kPadMax ] = {};
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		pressOldKeys[ padCnt ] = isPressPads_[ padCnt ];
	}

	// 軸のプレス情報を更新
	_UpdateAxis( diJoyState );

	// ボタンのプレス情報を更新
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		if( kPadToRGBButtonTbl[ padCnt ] != -1 ) {
			isPressPads_[ padCnt ] = diJoyState.rgbButtons[ kPadToRGBButtonTbl[ padCnt ] ] != 0;
		}
	}

	isPressPads_[ PAD_LT ] = diJoyState.rglSlider[ 0 ] > 0;
	isPressPads_[ PAD_RT ] = diJoyState.rglSlider[ 1 ] > 0;


	// 他の情報の更新
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		// トリガーの更新
		isTriggerPads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressOldKeys[ padCnt ] ) & isPressPads_[ padCnt ];

		// リリースの更新
		isReleasePads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressOldKeys[ padCnt ] ) & pressOldKeys[ padCnt ];

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
			else if( ( repeatCnts_[ padCnt ] >= kRepeatStartTime ) &&
				( repeatCnts_[ padCnt ] % kRepeatIntervalTime == 0 ) ) {

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

	// トリガー情報の更新
	lTrigger_ = (float)diJoyState.rglSlider[ 0 ];
	rTrigger_ = (float)diJoyState.rglSlider[ 1 ];
	lVTrigger_ = (float)diJoyState.rglVSlider[ 0 ];
	rVTrigger_ = (float)diJoyState.rglVSlider[ 1 ];

	// FFB中なら
	if( isGeneratingFFB_ ) {
		// if 時間経過なら 振動を止める
		if( timeFFB_ < 0 ) {
			if( pDIEffect_ ) {
				pDIEffect_->Start( 0, 0 );
			}
			isGeneratingFFB_ = false;
		}

		// HACK: UPDATEの引数に渡すとかな
		timeFFB_ -= 0.016f;
	}
}


//------------------------------------------------
// コールバック用関数
// 使用できるジョイスティックを列挙する
//------------------------------------------------
BOOL CALLBACK InputDirect::EnumJoysticksCallback( LPCDIDEVICEINSTANCE pDIDeviceInstance, LPVOID ) {
	// 列挙されたジョイスティックへのインターフェイスを取得する。
	LPDIRECTINPUTDEVICE8 pDIDevice;	// ローカル環境のデバイス
	if( FAILED( s_pDInput_->CreateDevice(pDIDeviceInstance->guidInstance, &pDIDevice, nullptr ) ) ) {
		return DIENUM_CONTINUE;
	}

	// ジョイスティックの能力を調べる
	DIDEVCAPS diDevCaps;
	diDevCaps.dwSize = sizeof( DIDEVCAPS );
	if ( FAILED( pDIDevice->GetCapabilities( &diDevCaps ) ) ) {
		// ジョイスティック能力の取得に失敗
		SafeRelease( pDIDevice );
		return DIENUM_CONTINUE;
	}

	// 格納
	InputDirect::GetCallBackTarget()->SetDIDevice( pDIDevice );
	InputDirect::GetCallBackTarget()->SetDevCaps( &diDevCaps );

	return DIENUM_STOP;
}


//------------------------------------------------
// コールバック用関数
// 使用できる軸を設定する
//------------------------------------------------
BOOL CALLBACK InputDirect::EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE pDIDeviceObjectInstance, LPVOID pvRef ) {
	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diPropRange;
	ZeroMemory( &diPropRange, sizeof( diPropRange ) );
	diPropRange.diph.dwSize = sizeof( diPropRange ); 
	diPropRange.diph.dwHeaderSize = sizeof( diPropRange.diph );
	diPropRange.diph.dwObj = pDIDeviceObjectInstance->dwType;
	diPropRange.diph.dwHow = DIPH_BYID;
	diPropRange.lMin = kAxisMin;
	diPropRange.lMax = kAxisMax;
	HRESULT hr = InputDirect::GetCallBackTarget()->GetDIDevice()->SetProperty( DIPROP_RANGE, &diPropRange.diph );
	if( FAILED( hr ) ) {
		return DIENUM_STOP;
	}
	
	// エフェクト用
	DWORD* pNumForceFeedbackAxis = (DWORD*)pvRef;
	if( ( pDIDeviceObjectInstance->dwFlags & DIDOI_FFACTUATOR ) != 0 ) {
		++(*pNumForceFeedbackAxis);
	}

	return DIENUM_CONTINUE;
}


//------------------------------------------------
// set
//------------------------------------------------
void InputDirect::SetFFB( const float left, const float right, const float time ) {
	timeFFB_ = time;
	isGeneratingFFB_ = true;

	if( pDIEffect_ && ( left != 0 || right != 0 ) ) {
		pDIEffect_->Start( 1 , 0 );
	}
	else if( pDIEffect_ ) {
		pDIEffect_->Stop();
	}
}


//------------------------------------------------
// Update for Axis
//------------------------------------------------
void InputDirect::_UpdateAxis( const DIJOYSTATE2& rDIJoyState ) {
	for( int i = 0; i < 4; ++i ) {
		isPressPads_[ i ] = false;
	}

	// rgdwPOV[0]に押された方向が角度×100という整数で格納されている
	// 真上が0で時計回りに36000まで範囲がある
	// デジタル入力方式のゲームパッドの場合、45度単位で取得してもまず問題ない
	switch( rDIJoyState.rgdwPOV[ 0 ] ) {
		case 0:
			isPressPads_[ PAD_UP ] = true;
			break;
		case 4500:
			isPressPads_[ PAD_UP ] = true;
			isPressPads_[ PAD_RIGHT ] = true;
			break;
		case 9000:
			isPressPads_[ PAD_RIGHT ] = true;
			break;
		case 13500:
			isPressPads_[ PAD_RIGHT ] = true;
			isPressPads_[ PAD_DOWN ] = true;
			break;
		case 18000:
			isPressPads_[ PAD_DOWN ] = true;
			break;
		case 22500:
			isPressPads_[ PAD_DOWN ] = true;
			isPressPads_[ PAD_LEFT ] = true;
			break;
		case 27000:
			isPressPads_[ PAD_LEFT ] = true;
			break;
		case 31500:
			isPressPads_[ PAD_LEFT ] = true;
			isPressPads_[ PAD_UP ] = true;
			break;
	}

	// アナログスティック用
	float lXOld = lX_;
	float lYOld = lY_;
	lX_ = (float)rDIJoyState.lX;
	lY_ = (float)rDIJoyState.lY;
	lVx_ = lX_ - lXOld;
	lVy_ = lY_ - lYOld;

	isPressPads_[ PAD_LTHUMB_UP ] = rDIJoyState.lY < -kAnalogStickThreshold;
	isPressPads_[ PAD_LTHUMB_DOWN ] = rDIJoyState.lY > kAnalogStickThreshold;
	isPressPads_[ PAD_LTHUMB_LEFT ] = rDIJoyState.lX < -kAnalogStickThreshold;
	isPressPads_[ PAD_LTHUMB_RIGHT ] = rDIJoyState.lX > kAnalogStickThreshold;
	isPressPads_[ PAD_LTHUMB_ANY ] =
		isPressPads_[ PAD_LTHUMB_UP ] || isPressPads_[ PAD_LTHUMB_DOWN ] ||
		isPressPads_[ PAD_LTHUMB_LEFT ] || isPressPads_[ PAD_LTHUMB_RIGHT ];
}