//==============================================================================
//
// InputManager [InputManager.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_INPUTMANAGER_H__
#define __H_INPUTMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include <list>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputDevice;
class InputDirect;
class InputKeyboard;
class InputMouse;
class InputXInput;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputManager {
public:
	// ctor/dtor
	InputManager( HINSTANCE hInstance, HWND hWnd );
	~InputManager();

	// method
	void Update( void );

	// get
	const InputDevice& GetPrimaryDevice( void ) const { return *pPrimaryDevice_; }
	const InputKeyboard& GetPrimaryKeyboard( void ) const { return *pPrimaryKeyboard_; }
	const InputMouse& GetPrimaryMouse( void ) const { return *pPrimaryMouse_; }

private:
	// property
	InputDevice* pPrimaryDevice_;
	InputKeyboard* pPrimaryKeyboard_;
	InputMouse* pPrimaryMouse_;
};


#endif // __H_INPUTMANAGER_H__