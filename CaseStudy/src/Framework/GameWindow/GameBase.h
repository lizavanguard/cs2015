//==============================================================================
//
// ゲームウィンドウ実装ベース [GameBase.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_GAMEBASE_H__
#define __H_GAMEBASE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameBase {
public:
	// dtor
	GameBase() {}
	virtual ~GameBase() {}

	// Initialize
	virtual void Initialize( HINSTANCE hInstance, HWND hWnd ) = 0;

	// Finalize
	virtual void Finalize( void ) = 0;

	// Update
	virtual void Update( float elapsedTime ) = 0;

	// Draw
	virtual void Draw( void ) = 0;

	// Window-Procedure
	virtual LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
		switch( msg ) {
			case WM_DESTROY:
				PostQuitMessage( 0 );
				break;

			case WM_CLOSE:
				DestroyWindow( hWnd );
				return 0;

			case WM_KEYDOWN:
				switch( wParam ) {
					case VK_ESCAPE:
						DestroyWindow( hWnd );
						return 0;
					default:
						break;
				}
				break;

			default:
				break;
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

private:
	// copy/assign
	GameBase( const GameBase& );
	GameBase& operator = ( const GameBase& );
};


#endif // __H_GAMEBASE_H__
