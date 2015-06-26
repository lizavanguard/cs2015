//==============================================================================
//
// DirectX用のウィンドウ管理クラス [DirectXWindow.h]
// Created : Shimizu Shoji
//
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Utility/HandyLeakCheck.h"
#include "Framework/GameWindow/GameWindow.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/FrameworkOption.h"


//==============================================================================
// EntryPoint
//==============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow ) {
	liza::utility::BeginLeakCheck();

	GameWindow gameWindow(
		hInstance,
		nCmdShow,
		"WindowTest",
        kWindowWidth,
        kWindowHeight,
		new GameDirectX()
	);

	gameWindow.Run();

	return 0;
}