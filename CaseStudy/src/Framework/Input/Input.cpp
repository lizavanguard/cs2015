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
	// 参照カウントの増加
	++s_referenceCnt_;

	// if インプットデバイスが生成済みなら終了
	if( s_pDInput_ != nullptr ) {
		return;
	}

	// DirectInputオブジェクトの作成
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

	// 参照カウントの減少
	--s_referenceCnt_;

	// if 参照しているものがなくなったら解放する
	if( s_referenceCnt_ == 0 ) {
		SafeRelease( s_pDInput_ );
	}
}