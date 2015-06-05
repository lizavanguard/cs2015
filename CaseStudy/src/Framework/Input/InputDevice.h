//==============================================================================
//
// 入力用Deviceクラス [InputDevice.h]
// Created : Shimizu Shoji
// MEMO:
//  似たようなパラメータがあったのでまとめて持ってきてしまいましたが
//  これがはたして良い設計だったのか 熟考して結論を出すこと
//
//==============================================================================
#pragma once
#ifndef __H_INPUTDEVICE_H__
#define __H_INPUTDEVICE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Input.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class InputDevice : public Input {
public:
	// Pad Enum
	enum Pads {
		PAD_UP,
		PAD_DOWN,
		PAD_LEFT,
		PAD_RIGHT,
		PAD_A,
		PAD_B,
		PAD_X,
		PAD_Y,
		PAD_LB,
		PAD_RB,
		PAD_LT,
		PAD_RT,
		PAD_LTHUMB,
		PAD_RTHUMB,
		PAD_BACK,
		PAD_START,
		PAD_LTHUMB_UP,
		PAD_LTHUMB_DOWN,
		PAD_LTHUMB_LEFT,
		PAD_LTHUMB_RIGHT,
		PAD_LTHUMB_ANY,
		PAD_RTHUMB_UP,
		PAD_RTHUMB_DOWN,
		PAD_RTHUMB_LEFT,
		PAD_RTHUMB_RIGHT,
		PAD_RTHUMB_ANY,
		kPadMax
	};

	enum Thumbs {
		THUMB_UP,
		THUMB_DOWN,
		THUMB_LEFT,
		THUMB_RIGHT,
		THUMB_ANY,
		kThumbMax
	};

public:
	// ctor/dtor
	InputDevice( HINSTANCE hInstance )
		: Input( hInstance )
		, lTrigger_( 0 )
		, lVTrigger_( 0 )
		, lX_( 0 )
		, lY_( 0 )
		, lVx_( 0 )
		, lVy_( 0 )
		, rTrigger_( 0 )
		, rVTrigger_( 0 )
		, rX_( 0 )
		, rY_( 0 )
		, rVx_( 0 )
		, rVy_( 0 )
		, isEnable_( false )
		, isEnableFFB_( false )
	{
		for( int padCnt = 0; padCnt < kPadMax; ++padCnt ) {
			isPressPads_[ padCnt ] = false;
			isReleasePads_[ padCnt ] = false;
			isRepeatPads_[ padCnt ] = false;
			isTriggerPads_[ padCnt ] = false;
			repeatCnts_[ padCnt ] = 0;
		}
	}

	virtual ~InputDevice() {}

	// get
	bool IsPress( Pads pad ) const { return isPressPads_[ pad ]; }
	bool IsRelease( Pads pad ) const { return isReleasePads_[ pad ]; }
	bool IsRepeat( Pads pad ) const { return isRepeatPads_[ pad ]; }
	bool IsTrigger( Pads pad ) const { return isTriggerPads_[ pad ]; }

	// スティックの詳細情報
	void GetLThumb( float* pX, float* pY ) const { *pX = rX_; *pY = rY_; }
	void GetLThumbVelocity( float* pVx, float* pVy ) const { *pVx = lVx_; *pVy = lVy_; }
	void GetRThumb( float* pX, float* pY ) const { *pX = rX_; *pY = rY_; }
	void GetRThumbVelocity( float* pVx, float* pVy ) const { *pVx = rVx_; *pVy = rVy_; }

	// トリガーの詳細情報
	float GetLTrigger( void ) const { return lTrigger_; }
	float GetVLTrigger( void ) const { return lVTrigger_; }
	float GetRTrigger( void ) const { return rTrigger_; }
	float GetVRTrigger( void ) const { return rVTrigger_; }

	bool IsEnable( void ) const { return isEnable_; }
	bool IsEnableFFB( void ) const { return isEnableFFB_; }

	// set
	void SetEnable( bool isEnable ) { isEnable_ = isEnable; }
	void SetEnableFFB( bool isEnable ) { isEnableFFB_ = isEnable; }
	virtual void SetFFB( float left, float right, float time ) = 0;

protected:
	// property
	float lTrigger_;
	float lVTrigger_;
	float lX_;
	float lY_;
	float lVx_;
	float lVy_;
	float rTrigger_;
	float rVTrigger_;
	float rX_;
	float rY_;
	float rVx_;
	float rVy_;
	bool isPressPads_[ kPadMax ];
	bool isReleasePads_[ kPadMax ];
	bool isRepeatPads_[ kPadMax ];
	bool isTriggerPads_[ kPadMax ];
	int repeatCnts_[ kPadMax ];

private:
	// property
	bool isEnable_;
	bool isEnableFFB_;	// 振動のON/OFF
};


#endif // __H_INPUTDEVICE_H__