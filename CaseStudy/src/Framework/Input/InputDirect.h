//==============================================================================
//
// DirectInput�p [InputDirect.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_INPUTDIRECT_H__
#define __H_INPUTDIRECT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "InputDevice.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputDirect : public InputDevice {
public:
	// ctor/dtor
	InputDirect( HINSTANCE hInstance, HWND hWnd );
	virtual ~InputDirect();

	// update
	void Update( void ) override;

	// �p�b�h�ɂ͂Q�R�[���o�b�N���K�v�Ȃ̂�
	static BOOL CALLBACK EnumJoysticksCallback( LPCDIDEVICEINSTANCE pDIDeviceInstance, LPVOID pContext );
	static BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE pDIDeviceObjectInstance, LPVOID pvRef );

	// get
	static InputDirect* GetCallBackTarget( void ) { return pCallBackTarget_; }

	// set
	void SetDevCaps( DIDEVCAPS* pDevCaps ){ memcpy( &diDevCaps_, pDevCaps, sizeof( DIDEVCAPS ) ); }
	void SetFFB( float left, float right, float time ) override;
	static void SetCallBackTarget( InputDirect* pCallBackTarget ) { pCallBackTarget_ = pCallBackTarget; }

private:
	// Update for Axis
	void _UpdateAxis( const DIJOYSTATE2& rDIJoyState );

	// property
	DIDEVCAPS diDevCaps_;	// �W���C�X�e�B�b�N�̔\��

	// FFB�p
	float timeFFB_;
	LPDIRECTINPUTEFFECT pDIEffect_;
	DWORD numForceFeedbackAxis_;
	bool isGeneratingFFB_;

	static InputDirect* pCallBackTarget_;
};


#endif // __H_INPUTDIRECT_H__