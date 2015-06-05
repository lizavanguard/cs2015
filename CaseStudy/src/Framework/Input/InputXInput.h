//==============================================================================
//
// XInputóp [InputXInput.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_INPUTXINPUT_H__
#define __H_INPUTXINPUT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <XInput.h>
#include "InputDevice.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputXInput: public InputDevice {
private:
	// const
	static const int kPadCapasityMax = 1;

public:
	// ctor/dtor
	InputXInput( HINSTANCE hInstance );
	virtual ~InputXInput();

	// Update
	void Update( void ) override;

	// set
	void SetFFB( float left, float right, float time ) override;

private:
	// property
	int padID_;
	float timeFFB_;
	bool isConnect_;	// ê⁄ë±Ç≥ÇÍÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
	bool isGeneratingFFB_;

	static unsigned int padCnt_;
};


#endif // __H_INPUTXINPUT_H__