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
	const int kRepeatStartTime = 60;		// ���s�[�g�̘A�����͊J�n����
	const int kRepeatIntervalTime = 1;		// ���s�[�g���̘͂A�����͊Ԋu
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

	// �f�o�C�X�I�u�W�F�N�g���쐬
	HRESULT hr = s_pDInput_->CreateDevice( GUID_SysKeyboard, &pDIDevice_, nullptr );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = pDIDevice_->SetDataFormat( &c_dfDIKeyboard );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = pDIDevice_->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );
	if( FAILED( hr ) ) {
		throw std::exception();
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
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
	BYTE keyCntStates_[ kKeyboardMax ];	// �ꎞ�I�ȏ��z��

	// �L�[�{�[�h�̏�Ԃ̎擾
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( keyCntStates_ ), &keyCntStates_[ 0 ] );

	// if �L�[�{�[�h�̏�Ԃ̎擾�ɐ����Ȃ�
	if( SUCCEEDED( hr ) ) {
		// �S�ẴL�[�̍X�V
		for( int keyCnt = 0; keyCnt < kKeyboardMax; ++keyCnt ) {
			// �O��̏��ޔ�
			bool pressKeyOld = isPressKeys_[ keyCnt ];

			// �L�[���̍X�V
			isPressKeys_[ keyCnt ] = ( keyCntStates_[ keyCnt ] & 0x80 ) ? true : false;

			// �g���K�[�̍X�V
			isTriggerKeys_[ keyCnt ] = ( isPressKeys_[ keyCnt ] ^ pressKeyOld ) & isPressKeys_[ keyCnt ];

			// �����[�X�̍X�V
			isReleaseKeys_[ keyCnt ] = ( isPressKeys_[ keyCnt ] ^ pressKeyOld ) & pressKeyOld;

			// ���s�[�g�̍X�V
			// ���s�[�g�̃N���A
			isRepeatKeys_[ keyCnt ] = false;
			// if �L�[��������Ă�����
			if( isPressKeys_[ keyCnt ] ) {
				// if���s�[�g�J�E���^��0�Ȃ�
				if( repeatCnts_[ keyCnt ] == 0 ) {
					// ���s�[�g���I���ɂ���
					isRepeatKeys_[ keyCnt ] = true;
				}
				// else if �A�����͊J�n���Ԉȏォ��莞�Ԗ��Ȃ�
				else if( ( repeatCnts_[ keyCnt ] >= kRepeatStartTime ) &&
					( repeatCnts_[ keyCnt ] % kRepeatIntervalTime == 0 ) ) {

					// ���s�[�g���I���ɂ���
					isRepeatKeys_[ keyCnt ] = true;
				}
				// ���s�[�g�J�E���^�̃J�E���g�A�b�v
				++repeatCnts_[ keyCnt ];
			}
			// else if �����[�X�Ȃ�
			else if( isReleaseKeys_[ keyCnt ] ) {
				// ���s�[�g�J�E���^��0�ɂ���
				repeatCnts_[ keyCnt ] = 0;
			}
		}
	}

	else {
		pDIDevice_->Acquire();
	}
}