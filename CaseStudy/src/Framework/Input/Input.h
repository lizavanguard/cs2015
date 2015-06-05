//==============================================================================
//
// Input-Base [Input.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#pragma warning( disable : 4290 )
#ifndef __H_INPUT_H__
#define __H_INPUT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// version difinition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DIRECTINPUT_VERSION ( 0x0800 )	// DInput8‚ðŽg‚¤


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include "dinput.h"
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )
#include <exception>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Input {
public:
	// ctor/dtor
	Input( HINSTANCE hInstance ) throw( std::exception );
	virtual ~Input();

	// method
	virtual void Update( void ) = 0;

	// get
	LPDIRECTINPUTDEVICE8 GetDIDevice( void ) const { return pDIDevice_; }

	// set
	void SetDIDevice( LPDIRECTINPUTDEVICE8 pDIDevice ) { pDIDevice_ = pDIDevice; }

protected:
	// property
	static LPDIRECTINPUT8 s_pDInput_;
	static unsigned int s_referenceCnt_;
	LPDIRECTINPUTDEVICE8 pDIDevice_;

private:
	// assign/copy
	Input( const Input& );
	Input& operator=( const Input& );
};


#endif // __H_INPUT_H__