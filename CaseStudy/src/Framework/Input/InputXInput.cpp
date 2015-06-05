//==============================================================================
//
// XInput�p [InputXInput.cpp]
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
	const int kRepeatStartTime = 60;	// ���s�[�g�̘A�����͊J�n����
	const int kRepeatIntervalTime = 1;	// ���s�[�g���̘͂A�����͊Ԋu

	// �p�b�h�{�^������XInput�{�^���ւ̑Ή��e�[�u��
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

	// XInput�L���ɂ���
	XInputEnable( TRUE );

	// PAD�ɊǗ��pID��U��
	padID_ = InputXInput::padCnt_;

	// �p�b�h�̐����X�V
	++padCnt_;

	// XInput�̔\�͂��擾
	XINPUT_CAPABILITIES capability;
	DWORD result = XInputGetCapabilities( padID_, XINPUT_FLAG_GAMEPAD, &capability );
	
	// �g�p�̉ۂ��X�V
	SetEnable( result == ERROR_SUCCESS );

	// �U����ON
	SetEnableFFB( true );
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputXInput::~InputXInput() {
	XINPUT_VIBRATION vibration = { 0, 0 };
	XInputSetState( padID_, &vibration );

	// XInput�����ɂ���
	XInputEnable( FALSE );
}


//------------------------------------------------
// Update
//------------------------------------------------
void InputXInput::Update( void ) {
	// Pad��Ԏ擾
	XINPUT_STATE xPadState;
	DWORD result = XInputGetState( padID_, &xPadState );
	// if �G���[�Ȃ� ���ڑ���Ԃɂ���
	if( result != ERROR_SUCCESS ) {
		isConnect_ = false;
		return;
	}

	// �ڑ���Ԃɂ���
	isConnect_ = true;

	// �O��̏��ޔ�
	bool pressKeyOlds[ kPadMax ];
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		pressKeyOlds[ padCnt ] = isPressPads_[ padCnt ];
	}

	// �v���X���̍X�V
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

	// �p�b�h���̍X�V
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		// �O��̏��ޔ�
		bool pressKeyOld = pressKeyOlds[ padCnt ];

		// �g���K�[�̍X�V
		isTriggerPads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressKeyOld ) & isPressPads_[ padCnt ];

		// �����[�X�̍X�V
		isReleasePads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressKeyOld ) & pressKeyOld;

		// ���s�[�g�̍X�V
		// ���s�[�g�̃N���A
		isRepeatPads_[ padCnt ] = false;
		// if �L�[��������Ă�����
		if( isPressPads_[ padCnt ] ) {
			// if���s�[�g�J�E���^��0�Ȃ�
			if( repeatCnts_[ padCnt ] == 0 ) {
				// ���s�[�g���I���ɂ���
				isRepeatPads_[ padCnt ] = true;
			}
			// else if �A�����͊J�n���Ԉȏォ��莞�Ԗ��Ȃ�
			else if(
				( repeatCnts_[ padCnt ] >= kRepeatStartTime ) &&
				( repeatCnts_[ padCnt ] % kRepeatIntervalTime == 0 )
			) {
				// ���s�[�g���I���ɂ���
				isRepeatPads_[ padCnt ] = true;
			}
			// ���s�[�g�J�E���^�̃J�E���g�A�b�v
			++repeatCnts_[ padCnt ];
		}
		// else if �����[�X�Ȃ�
		else if( isReleasePads_[ padCnt ] ) {
			// ���s�[�g�J�E���^��0�ɂ���
			repeatCnts_[ padCnt ] = 0;
		}
	}

	// �g���K�[�̏��
	float lTriggerOld = lTrigger_;
	float rTriggerOld = rTrigger_;
	lTrigger_ = xPadState.Gamepad.bLeftTrigger;
	rTrigger_ = xPadState.Gamepad.bRightTrigger;
	lVTrigger_ = lTrigger_ - lTriggerOld;
	rVTrigger_ = rTrigger_ - rTriggerOld;

	// �A�i���O�X�e�B�b�N�̏��
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

	// FFB���Ȃ�
	if( isGeneratingFFB_ ) {
		// if ���Ԍo�߂Ȃ� �U�����~�߂�
		if( timeFFB_ < 0 ) {
			XINPUT_VIBRATION vibration = { 0, 0 };
			XInputSetState( padID_, &vibration );
			isGeneratingFFB_ = false;
		}

		// HACK: UPDATE�̈����ɓn���Ƃ���
		timeFFB_ -= 0.016f;
	}
}


//------------------------------------------------
// set
//------------------------------------------------
void InputXInput::SetFFB( const float left, const float right, const float time ) {
	// if �ڑ����Ă��Ȃ�I��
	if( !isConnect_ ) {
		return;
	}

	// if �U���������Ȃ�I��
	if( !IsEnableFFB() ) {
		return;
	}

	// �l��0~65535�Ɋۂ߂�
	float leftRate = liza::math::Clamp( left, 0.0f, 1.0f );
	float rightRate = liza::math::Clamp( right, 0.0f, 1.0f );
	timeFFB_ = time;

	// �U���̐ݒ�
	XINPUT_VIBRATION vibration = {
		(WORD)( leftRate * 65535 ),
		(WORD)( rightRate * 65535 )
	};
	XInputSetState( padID_, &vibration );
	isGeneratingFFB_ = true;
}