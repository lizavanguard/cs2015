//==============================================================================
//
// Input-Mouse [InputMouse.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#pragma warning( disable : 4290 )
#pragma warning( disable : 4481 )
#ifndef __H_INPUTMOUSE_H__
#define __H_INPUTMOUSE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Input.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputMouse : public Input {
public:
	// const
	static const int kMouseButtonMax = 8;

public:
	// ctor/dtor
	InputMouse( HINSTANCE hInstance, HWND hWnd ) throw( std::exception );
	virtual ~InputMouse();

	// method
	virtual void Update( void ) override;

	// get
	long GetX( void ) const { return x_; }
	long GetY( void ) const { return y_; }
	long GetZ( void ) const { return z_; }
	long GetRelativeX( void ) const { return relativeX_; }
	long GetRelativeY( void ) const { return relativeY_; }
	long GetRelativeZ( void ) const { return relativeZ_; }
	bool IsPress( int button ) const { return pressButtons_[ button ]; }
	bool IsRelease( int button ) const { return releaseButtons_[ button ]; }
	bool IsRepeat( int button ) const { return repeatButtons_[ button ]; }
	bool IsTrigger( int button ) const { return triggerButtons_[ button ]; }

private:
	// property
	HWND hWnd_;
	long x_;
	long y_;
	long z_;
	long relativeX_;
	long relativeY_;
	long relativeZ_;
	bool pressButtons_[ kMouseButtonMax ];
	bool triggerButtons_[ kMouseButtonMax ];
	bool releaseButtons_[ kMouseButtonMax ];
	bool repeatButtons_[ kMouseButtonMax ];
	int repeatCnt_[ kMouseButtonMax ];
};


#endif // __H_INPUTMOUSE_H__