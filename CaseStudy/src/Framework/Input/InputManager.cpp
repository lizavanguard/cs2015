//==============================================================================
//
// InputManager [InputManager.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "InputManager.h"
#include "InputDirect.h"
#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputXInput.h"
#include "Framework/Utility/SafeDelete.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
InputManager::InputManager( HINSTANCE hInstance, HWND hWnd )
	: pPrimaryDevice_( nullptr ), pPrimaryKeyboard_( nullptr ), pPrimaryMouse_( nullptr )
{
	pPrimaryDevice_ = new InputXInput( hInstance );
	if( !pPrimaryDevice_->IsEnable() ) {
		SafeDelete( pPrimaryDevice_ );
		pPrimaryDevice_ = new InputDirect( hInstance, hWnd );
	}

	pPrimaryKeyboard_ = new InputKeyboard( hInstance, hWnd );
	pPrimaryMouse_ = new InputMouse( hInstance, hWnd );
}


//------------------------------------------------
// dtor
//------------------------------------------------
InputManager::~InputManager() {
	SafeDelete( pPrimaryMouse_ );
	SafeDelete( pPrimaryKeyboard_ );
	SafeDelete( pPrimaryDevice_ );
}

#define _TEST
//------------------------------------------------
// update
//------------------------------------------------
void InputManager::Update( void ) {
	pPrimaryDevice_->Update();

#ifdef _TEST
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_UP ) ) {
		OutputDebugString( "UP" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_DOWN ) ) {
		OutputDebugString( "DOWN" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LEFT ) ) {
		OutputDebugString( "LEFT" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RIGHT ) ) {
		OutputDebugString( "RIGHT" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_A ) ) {
		OutputDebugString( "A" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_B ) ) {
		OutputDebugString( "B" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_X ) ) {
		OutputDebugString( "X" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_Y ) ) {
		OutputDebugString( "Y" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LB ) ) {
		OutputDebugString( "L" );
		pPrimaryDevice_->SetFFB( 0.5f, 0, 2 );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RB ) ) {
		OutputDebugString( "R" );
		pPrimaryDevice_->SetFFB( 0, 0.5f, 2 );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LT ) ) {
		OutputDebugString( "LT" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RT ) ) {
		OutputDebugString( "RT" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LTHUMB ) ) {
		OutputDebugString( "LTHUMB" );
		pPrimaryDevice_->SetFFB( 1.0f, 0, 2 );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RTHUMB ) ) {
		OutputDebugString( "RTHUMB" );
		pPrimaryDevice_->SetFFB( 0.5f, 1.0f, 2 );
		//__asm int 3
	}

	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_START ) ) {
		OutputDebugString( "START" );
		//__asm int 3
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_BACK ) ) {
		//__asm int 3
		OutputDebugString( "M" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LTHUMB_UP ) ) {
		OutputDebugString( "L-UP" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LTHUMB_DOWN ) ) {
		OutputDebugString( "L-DOWN" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LTHUMB_LEFT ) ) {
		OutputDebugString( "L-LEFT" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_LTHUMB_RIGHT ) ) {
		OutputDebugString( "L-RIGHT" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RTHUMB_UP ) ) {
		OutputDebugString( "R-UP" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RTHUMB_DOWN ) ) {
		OutputDebugString( "R-DOWN" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RTHUMB_LEFT ) ) {
		OutputDebugString( "R-LEFT" );
	}
	if( pPrimaryDevice_->IsTrigger( InputDirect::PAD_RTHUMB_RIGHT ) ) {
		OutputDebugString( "R-RIGHT" );
	}

#endif


	pPrimaryKeyboard_->Update();
	pPrimaryMouse_->Update();
}