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
#include "Framework/Input/InputManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Texture/TextureManager.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/Utility/Utility.h"

#include "Application/Game/SceneGame.h"  // HACK: –³—‚â‚è


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

  // input manager
  pInputManager_ = new InputManager( hInstance, hWnd );
  InputManagerHolder::Instance().SetInputManager(pInputManager_);

  // texture manager
  pTextureManager_ = new TextureManager(pDevice);
  TextureManagerHolder::Instance().SetTextureManager(pTextureManager_);

  // scene manager
  Scene* pFirstScene = new SceneGame();
  pSceneManager_ = new SceneManager(pFirstScene);
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  SafeDelete(pTextureManager_);

  SafeDelete(pSceneManager_);

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

  // debug
	pDebugProc_->Draw();
}