//==============================================================================
//
// DirectX—p [GameDirectX.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_GAMEDIRECTX_H__
#define __H_GAMEDIRECTX_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameBase.h"
#include "d3dx9.h"
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxguid.lib" )


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameManager;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameDirectX : public GameBase {
public:
	// ctor/dtor
	GameDirectX();
	virtual ~GameDirectX();

	// Initialize
	void Initialize( HINSTANCE hInstance, HWND hWnd ) override;

	// Finalize
	void Finalize( void ) override;

	// Update
  void Update( float elapsedTime ) override;

	// Draw
	void Draw( void ) override;

  // get
  LPDIRECT3DDEVICE9 GetDevice(void) const { return pDevice_; }

private:
	// property
	LPDIRECT3D9 pD3D_;
	LPDIRECT3DDEVICE9 pDevice_;
	GameManager* pGameManager_;
};


#endif // __H_GAMEDIRECTX_H__