//==============================================================================
//
// ƒQ[ƒ€ŠÇ— [GameManager.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameManager.h"

#include "Framework/DebugProc/DebugProc.h"
#include "Framework/DrawDebugPrimitive/DrawPrimitive.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Sound/sound.h"
#include "Framework/Texture/TextureManager.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/Utility/Utility.h"

#include "Application/Game/SceneGame.h"  // HACK: –³—‚â‚è
#include "Application/Title/SceneTitle.h"



//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Get Instance
//------------------------------------------------
GameManager& GameManager::Instance( HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice ) {
	static GameManager instance( hInstance, hWnd, pDevice );
	return instance;
}


//------------------------------------------------
// ctor
//------------------------------------------------
GameManager::GameManager( HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice )
	: pDevice_( pDevice )
	, pDebugProc_( nullptr )
	, pInputManager_( nullptr )
  , pSceneManager_(nullptr)
  , pTextureManager_(nullptr)
{
  pDebugProc_ = new DebugProc();
  pDebugProc_->Init( pDevice_ );

  pInputManager_ = new InputManager( hInstance, hWnd );
  InputManagerHolder::Instance().SetInputManager(pInputManager_);

  pTextureManager_ = new TextureManager(pDevice);
  TextureManagerHolder::Instance().SetTextureManager(pTextureManager_);

  InitSound(hWnd);

  InitDrawPrimitive(pDevice);
 
  Scene* pFirstScene = new SceneTitle();
  pSceneManager_ = new SceneManager(pFirstScene);
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  SafeDelete(pSceneManager_);

  UninitDrawPrimitive();

  UninitSound();

  SafeDelete(pTextureManager_);

  SafeDelete(pInputManager_);

  pDebugProc_->Uninit();
  SafeDelete(pDebugProc_);
}


//------------------------------------------------
// update
//------------------------------------------------
void GameManager::Update( const float elapsedTime ) {
  // input
	pInputManager_->Update();

  // scene
  pSceneManager_->Update(elapsedTime);
}


//------------------------------------------------
// draw
//------------------------------------------------
void GameManager::Draw( void ) {
  // scene
  pSceneManager_->Draw();

  // draw debug
  DrawAll();

  // debug
	pDebugProc_->Draw();
}