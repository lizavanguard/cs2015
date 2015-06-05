//==============================================================================
//
// DirectInput�p [InputDirect.cpp]
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
	const int kRepeatStartTime = 60;		// ���s�[�g�̘A�����͊J�n����
	const int kRepeatIntervalTime = 1;		// ���s�[�g���̘͂A�����͊Ԋu
	const int kAnalogStickThreshold = 100;	// �A�i���O�X�e�B�b�N�p��臒l�@�Ă��Ɓ[
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
	// �������g���R�[���o�b�N�̑Ώۂɂ���
	InputDirect::SetCallBackTarget( this );

	// �f�o�C�X��񋓂��č쐬
	// �R�[���o�b�N�֐������Ńf�o�C�X���쐬���鏈��������
	HRESULT hr = s_pDInput_->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		nullptr,
		DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY
	);
	SetEnableFFB( true );

	// if �쐬�����s������
	if( FAILED( hr ) || pDIDevice_ == nullptr ) {
		// FFB�����ō쐬
		hr =  s_pDInput_->EnumDevices(
			DI8DEVCLASS_GAMECTRL,
			EnumJoysticksCallback,
			nullptr,
			DIEDFL_ATTACHEDONLY
		);
		SetEnableFFB( false );

		// ����ł����߂Ȃ� �I��
		if( FAILED( hr ) || pDIDevice_ == nullptr ) {
			return;
		}
	}

	// �f�[�^�`����ݒ�
	hr = pDIDevice_->SetDataFormat( &c_dfDIJoystick2 );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr,"c_dfDIJoystick2�`���̐ݒ�Ɏ��s", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = pDIDevice_->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr, "�t�H�A�O���E���h����r�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
	hr = pDIDevice_->EnumObjects( EnumAxesCallback, &numForceFeedbackAxis_, DIDFT_AXIS );
	if( FAILED( hr ) ) {
#ifdef _DEBUG
		MessageBox( nullptr, "�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK );
#endif
		return;
	}

	// �G�t�F�N�g�̐ݒ�
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

	// �G�t�F�N�g�̍쐬
	pDIDevice_->CreateEffect( GUID_ConstantForce, &diEffect, &pDIEffect_, nullptr );

	// ���͐���J�n
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

	// �f�o�C�X�����݂��Ȃ��Ȃ� �I��
	if( pDIDevice_ == nullptr ) {
		return;
	}

	// �W���C�p�b�h�f�[�^�̃|�[�����O
	pDIDevice_->Poll();

	// ���͂̎�t�J�n
	pDIDevice_->Acquire();

	// �l�̎擾
	DIJOYSTATE2 diJoyState;
	HRESULT hr = pDIDevice_->GetDeviceState( sizeof( DIJOYSTATE2 ), &diJoyState );
	if( FAILED( hr ) ) {
		// if �f�o�C�X���X�g�Ȃ�Ď擾
		if( hr == DIERR_INPUTLOST ) {
			pDIDevice_->Acquire();
		}
		return;
	}

	// �O��̏���ۑ�
	bool pressOldKeys[ kPadMax ] = {};
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		pressOldKeys[ padCnt ] = isPressPads_[ padCnt ];
	}

	// ���̃v���X�����X�V
	_UpdateAxis( diJoyState );

	// �{�^���̃v���X�����X�V
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		if( kPadToRGBButtonTbl[ padCnt ] != -1 ) {
			isPressPads_[ padCnt ] = diJoyState.rgbButtons[ kPadToRGBButtonTbl[ padCnt ] ] != 0;
		}
	}

	isPressPads_[ PAD_LT ] = diJoyState.rglSlider[ 0 ] > 0;
	isPressPads_[ PAD_RT ] = diJoyState.rglSlider[ 1 ] > 0;


	// ���̏��̍X�V
	for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
		// �g���K�[�̍X�V
		isTriggerPads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressOldKeys[ padCnt ] ) & isPressPads_[ padCnt ];

		// �����[�X�̍X�V
		isReleasePads_[ padCnt ] = ( isPressPads_[ padCnt ] ^ pressOldKeys[ padCnt ] ) & pressOldKeys[ padCnt ];

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
			else if( ( repeatCnts_[ padCnt ] >= kRepeatStartTime ) &&
				( repeatCnts_[ padCnt ] % kRepeatIntervalTime == 0 ) ) {

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

	// �g���K�[���̍X�V
	lTrigger_ = (float)diJoyState.rglSlider[ 0 ];
	rTrigger_ = (float)diJoyState.rglSlider[ 1 ];
	lVTrigger_ = (float)diJoyState.rglVSlider[ 0 ];
	rVTrigger_ = (float)diJoyState.rglVSlider[ 1 ];

	// FFB���Ȃ�
	if( isGeneratingFFB_ ) {
		// if ���Ԍo�߂Ȃ� �U�����~�߂�
		if( timeFFB_ < 0 ) {
			if( pDIEffect_ ) {
				pDIEffect_->Start( 0, 0 );
			}
			isGeneratingFFB_ = false;
		}

		// HACK: UPDATE�̈����ɓn���Ƃ���
		timeFFB_ -= 0.016f;
	}
}


//------------------------------------------------
// �R�[���o�b�N�p�֐�
// �g�p�ł���W���C�X�e�B�b�N��񋓂���
//------------------------------------------------
BOOL CALLBACK InputDirect::EnumJoysticksCallback( LPCDIDEVICEINSTANCE pDIDeviceInstance, LPVOID ) {
	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	LPDIRECTINPUTDEVICE8 pDIDevice;	// ���[�J�����̃f�o�C�X
	if( FAILED( s_pDInput_->CreateDevice(pDIDeviceInstance->guidInstance, &pDIDevice, nullptr ) ) ) {
		return DIENUM_CONTINUE;
	}

	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	DIDEVCAPS diDevCaps;
	diDevCaps.dwSize = sizeof( DIDEVCAPS );
	if ( FAILED( pDIDevice->GetCapabilities( &diDevCaps ) ) ) {
		// �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		SafeRelease( pDIDevice );
		return DIENUM_CONTINUE;
	}

	// �i�[
	InputDirect::GetCallBackTarget()->SetDIDevice( pDIDevice );
	InputDirect::GetCallBackTarget()->SetDevCaps( &diDevCaps );

	return DIENUM_STOP;
}


//------------------------------------------------
// �R�[���o�b�N�p�֐�
// �g�p�ł��鎲��ݒ肷��
//------------------------------------------------
BOOL CALLBACK InputDirect::EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE pDIDeviceObjectInstance, LPVOID pvRef ) {
	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
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
	
	// �G�t�F�N�g�p
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

	// rgdwPOV[0]�ɉ����ꂽ�������p�x�~100�Ƃ��������Ŋi�[����Ă���
	// �^�オ0�Ŏ��v����36000�܂Ŕ͈͂�����
	// �f�W�^�����͕����̃Q�[���p�b�h�̏ꍇ�A45�x�P�ʂŎ擾���Ă��܂����Ȃ�
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

	// �A�i���O�X�e�B�b�N�p
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