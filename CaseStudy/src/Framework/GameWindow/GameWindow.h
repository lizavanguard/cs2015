//==============================================================================
//
// Game用ウィンドウクラス [GameWindow.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_GAMEWINDOW_H__
#define __H_GAMEWINDOW_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameBase;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameWindow {
public:
	// ctor/dtor
	GameWindow(
		HINSTANCE hInstance,
		int nCmdShow,
		const char* pWindowCaption,
		unsigned int windowWidth,
		unsigned int windowHeight,
		GameBase* pGameImpl
	);
	~GameWindow();

	// Run
	void Run( void );

	// Window-procedure
	static LRESULT CALLBACK LocalWindowProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	// Get
	HINSTANCE GetHInstance( void ) const { return hInstance_; }
	HWND GetHWnd( void ) const { return hWnd_; }

private:
	// copy/assign
	GameWindow( const GameWindow& );
	GameWindow& operator = ( const GameWindow& );

	// property
	HINSTANCE hInstance_;
	HWND hWnd_;
	GameBase* pGameImpl_;
	static GameBase* pCallbackTarget_;	// どうしたらいいの
};


#endif // __H_GAMEWINDOW_H__