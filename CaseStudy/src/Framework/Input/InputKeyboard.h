//==============================================================================
//
// Input-Keyboard [InputKeyboard.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#pragma warning( disable : 4481 )
#ifndef __H_INPUTKEYBOARD_H__
#define __H_INPUTKEYBOARD_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Input.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputKeyboard : public Input {
private:
	// const
	static const int kKeyboardMax = 256;

public:
	// ctor/dtor
	InputKeyboard( HINSTANCE hInstance, HWND hWnd ) throw( std::exception );
	virtual ~InputKeyboard();

	// method
	virtual void Update( void ) override;

	// get
	bool IsPress( int key ) const { return isPressKeys_[ key ]; }
	bool IsRelease( int key ) const { return isReleaseKeys_[ key ]; }
	bool IsRepeat( int key ) const { return isRepeatKeys_[ key ]; }
	bool IsTrigger( int key ) const { return isTriggerKeys_[ key ]; }

private:
	// property
	bool isPressKeys_[ kKeyboardMax ];
	bool isTriggerKeys_[ kKeyboardMax ];
	bool isReleaseKeys_[ kKeyboardMax ];
	bool isRepeatKeys_[ kKeyboardMax ];
	int repeatCnts_[ kKeyboardMax ];
};


#endif // __H_INPUTKEYBOARD_H__