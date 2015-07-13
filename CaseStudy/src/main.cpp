//==============================================================================
//
// main
// Author : Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Utility/HandyLeakCheck.h"
#include "Framework/GameWindow/GameWindow.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/FrameworkOption.h"

//==============================================================================
// EntryPoint
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
  liza::utility::BeginLeakCheck();

  GameWindow gameWindow(
    hInstance,
    nCmdShow,
    "WindowTest",
    static_cast<unsigned int>(kWindowWidth),
    static_cast<unsigned int>(kWindowHeight),
    new GameDirectX());

  gameWindow.Run();

  return 0;
}
