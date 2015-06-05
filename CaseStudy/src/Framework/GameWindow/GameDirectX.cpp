//==============================================================================
//
// DirectX用 [GameDirectX.h]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameDirectX.h"
#include "../DirectXHelper/DeviceHolder.h"
#include "../GameManager/GameManager.h"
#include "../Utility/Utility.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameDirectX::GameDirectX() : pD3D_( nullptr ), pDevice_( nullptr ), pGameManager_( nullptr ) {
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameDirectX::~GameDirectX() {
}


//------------------------------------------------
// Initialize
//------------------------------------------------
void GameDirectX::Initialize( HINSTANCE hInstance, HWND hWnd ) {
	// Direct3Dオブジェクトの生成
	pD3D_ = Direct3DCreate9( D3D_SDK_VERSION );

	// if 作成できなかったら
	if( !pD3D_ ) {
		// エラー通知
		return;
	}

	// 現在のディスプレイモードを取得
	D3DDISPLAYMODE d3ddm;
	HRESULT hr = pD3D_->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
	// if ディスプレイモードを取得できなかったら
	if( FAILED( hr ) ) {
		// エラー通知
		return;
	}

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );							// ワークをゼロクリア
	d3dpp.BackBufferCount        = 1;								// バックバッファの数
	d3dpp.BackBufferWidth        = 1280;					// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight       = 760;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;				// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.Windowed               = true;						// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う

	// if ウィンドウモードなら
	// TODO: ウィンドウモード切替
	if( true ) {
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;							// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;											// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;		// インターバル
	}
	// else フルスクリーンモードなら
	else {
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;						// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	hr = pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,		// ディスプレイアダプタ
		D3DDEVTYPE_HAL,		// ディスプレイタイプ
		hWnd,		// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
		&d3dpp,		// デバイスのプレゼンテーションパラメータ
		&pDevice_		// デバイスインターフェースへのポインタ
	);

	// if 上記の設定が失敗したら
	if( FAILED( hr ) ) {
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行う
		hr = pD3D_->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&pDevice_
		);

		// if 上記の設定が失敗したら
		if( FAILED( hr ) ) {
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			hr = pD3D_->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&pDevice_
			);

			// if 上記の設定が失敗したら
			if( FAILED( hr ) ){
				// エラー通知
				return;
			}
		}
	}

	// 背面カリング
	pDevice_->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// Zバッファ使用
	pDevice_->SetRenderState( D3DRS_ZENABLE, TRUE );

	// アルファブレンド使用
	pDevice_->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// ソースと対象のアルファブレンド比率設定
	pDevice_->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// ソースのアルファをそのまま使用し、対象はそれの補数？をとる
	pDevice_->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// サンプラーステートパラメータの設定
	// テクスチャアドレッシング方式(U値)を設定
	pDevice_->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	// テクスチャアドレッシング方式(V値)を設定
	pDevice_->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	// テクスチャ縮小フィルタモードを設定
	pDevice_->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	// テクスチャ拡大フィルタモードを設定
	pDevice_->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// テクスチャステージステートの設定
	// アルファブレンディング処理
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	// 最初のアルファ引数
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	// 2番目のアルファ引数
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_CURRENT );

  // ホルダーに渡しちゃう
  DeviceHolder::Instance().SetDevice(pDevice_);

  // ゲームマネージャ
  GameManager::Instance(hInstance, hWnd, pDevice_);

	return;
}


//------------------------------------------------
// Finalize
//------------------------------------------------
void GameDirectX::Finalize( void ) {
	SafeRelease( pDevice_ );
	SafeRelease( pD3D_ );
}


//------------------------------------------------
// Update
//------------------------------------------------
void GameDirectX::Update( const float elapsedTime ) {
  GameManager::Instance().Update(elapsedTime);
}


//------------------------------------------------
// Draw
//------------------------------------------------
void GameDirectX::Draw( void ) {
	// 背景色も指定
	pDevice_->Clear(
		0,
		nullptr,
		( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ),	// モード
		D3DCOLOR_RGBA( 0, 128, 128, 0 ),	// 背景色
		1.0f,		// Z深度
		0
	);

	if( SUCCEEDED( pDevice_->BeginScene() ) ) {

		GameManager::Instance().Draw();

		pDevice_->EndScene();
	}

	pDevice_->Present( nullptr, nullptr, nullptr, nullptr );
}