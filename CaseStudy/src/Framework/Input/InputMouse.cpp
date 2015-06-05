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
static const int kRepeatStartTime = 60;		// ���s�[�g�̘A�����͊J�n����
static const int kRepeatIntervalTime = 1;		// ���s�[�g���̘͂A�����͊Ԋu


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

	// �f�o�C�X�I�u�W�F�N�g���쐬
	HRESULT hr = s_pDInput_->CreateDevice( GUID_SysMouse, &pDIDevice_, nullptr );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = pDIDevice_->SetDataFormat( &c_dfDIMouse2 );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = pDIDevice_->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diProperty;
	diProperty.diph.dwSize = sizeof(diProperty); 
	diProperty.diph.dwHeaderSize = sizeof(diProperty.diph); 
	diProperty.diph.dwObj = 0;
	diProperty.diph.dwHow = DIPH_DEVICE;
	// ���Βl���[�h�̏ꍇ
	diProperty.dwData = DIPROPAXISMODE_REL;
	// ��Βl���[�h�̏ꍇ
	//diProperty.dwData  = DIPROPAXISMODE_ABS;

	hr = pDIDevice_->SetProperty( DIPROP_AXISMODE, &diProperty.diph );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
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
	// �}�E�X�̏�Ԃ̎擾
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( mouseState ), &mouseState );
	if( FAILED( hr ) ) {
		// �}�E�X�f�o�C�X�̍Ď擾
		pDIDevice_->Acquire();
		return;
	}

	// ��Βl�̍X�V
	POINT pos;
	GetCursorPos( &pos );
	ScreenToClient( hWnd_, &pos );
	x_ = pos.x;
	y_ = pos.y;
	z_ = 0;

	// ���Βl�̍X�V
	relativeX_ = mouseState.lX;
	relativeY_ = mouseState.lY;
	relativeZ_ = mouseState.lZ;

	// �S�ẴL�[�̍X�V
	for( int button = 0; button < kMouseButtonMax; ++button ) {
		// �O��̏��ޔ�
		bool pressButtonOld = pressButtons_[ button ];

		// �L�[���̍X�V
		pressButtons_[ button ] = ( mouseState.rgbButtons[ button ] & 0x80 ) ? true : false;

		// �g���K�[�̍X�V
		triggerButtons_[ button ] = ( pressButtons_[ button ] ^ pressButtonOld ) & pressButtons_[ button ];

		// �����[�X�̍X�V
		releaseButtons_[ button ] = ( pressButtons_[ button ] ^ pressButtonOld ) & pressButtonOld;

		// ���s�[�g�̍X�V
		// HACK: �\�����K��
		// ���s�[�g�̃N���A
		repeatButtons_[ button ] = false;
		// if �L�[��������Ă�����
		if( pressButtons_[ button ] ) {
			// if���s�[�g�J�E���^��0�Ȃ�
			if( repeatCnt_[ button ] == 0 ) {
				// ���s�[�g���I���ɂ���
				repeatButtons_[ button ] = true;
			}
			// else if �A�����͊J�n���Ԉȏォ��莞�Ԗ��Ȃ�
			else if( ( repeatCnt_[ button ] >= kRepeatStartTime ) &&
				( repeatCnt_[ button ] % kRepeatIntervalTime == 0 ) ) {

				// ���s�[�g���I���ɂ���
				repeatButtons_[ button ] = true;
			}
			// ���s�[�g�J�E���^�̃J�E���g�A�b�v
			++repeatCnt_[ button ];
		}
		// else if �����[�X�Ȃ�
		else if( releaseButtons_[ button ] ) {
			// ���s�[�g�J�E���^��0�ɂ�	��
			repeatCnt_[ button ] = 0;
		}
	}
}