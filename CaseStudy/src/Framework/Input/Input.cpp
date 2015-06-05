//==============================================================================
//
// Input-Base [Input.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Input.h"
#include "Framework/Utility/SafeRelease.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
LPDIRECTINPUT8 Input::s_pDInput_ = nullptr;
unsigned int Input::s_referenceCnt_ = 0;


//------------------------------------------------
// ctor
//------------------------------------------------
Input::Input( HINSTANCE hInstance ) : pDIDevice_( nullptr ) {
	// �Q�ƃJ�E���g�̑���
	++s_referenceCnt_;

	// if �C���v�b�g�f�o�C�X�������ς݂Ȃ�I��
	if( s_pDInput_ != nullptr ) {
		return;
	}

	// DirectInput�I�u�W�F�N�g�̍쐬
	HRESULT hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>( &s_pDInput_ ),
		nullptr
	);
	if( FAILED( hr ) ) {
		throw std::exception();
	}
}


//------------------------------------------------
// dtor
//------------------------------------------------
Input::~Input() {
	if( pDIDevice_ ) {
		pDIDevice_->Unacquire();
		SafeRelease( pDIDevice_ );
	}

	// �Q�ƃJ�E���g�̌���
	--s_referenceCnt_;

	// if �Q�Ƃ��Ă�����̂��Ȃ��Ȃ�����������
	if( s_referenceCnt_ == 0 ) {
		SafeRelease( s_pDInput_ );
	}
}