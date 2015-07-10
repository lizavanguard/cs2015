//==============================================================================
//
// フェードモジュール[fade.cpp]
// Designed On 2013/07/13 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Fade.h"

#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/FrameworkOption.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 定数定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const int kPolygonMax = 1;	// 四角形のポリゴンの数
static const int kVertexMax = kPolygonMax * 4;

static const float kAlphaMax = 255.0f;
static const float kFadeSpd = 4.0f;

static const float kFadeWidth = kWindowWidth;
static const float kFadeHeight = kWindowHeight + 100;
static const float kFadePosX = kFadeWidth / 2;
static const float kFadePosY = kFadeHeight / 2;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {

//------------------------------------------------
// オブジェクト
//------------------------------------------------
typedef struct {
	D3DXVECTOR3 pos;	// ポリゴンの位置(中心点を座標として保持する)
	D3DXVECTOR3 spd;	// 速度
	D3DXVECTOR3 rot;	// ポリゴンの回転(向き)
	D3DXVECTOR3 size;	// ポリゴンのサイズ
	float length;		// ポリゴンの対角線の長さ
	float angle;		// ポリゴンの対角線の角度
	LPDIRECT3DVERTEXBUFFER9 vtx_buff;	// 頂点バッファ
} Object;

//------------------------------------------------
// フェード
//------------------------------------------------
typedef struct {
	Object obj;
	Fades fade_mode;
	float alpha;
} Fade;

typedef struct _Vertex2 {
  D3DXVECTOR3 vtx;		// 頂点座標
  float    rhw;		// 同次座標の係数w
  D3DCOLOR diffuse;	// 反射光
  D3DXVECTOR2  tex;		// テクスチャ座標
} Vertex2;

#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static bool UpdateFadeIn( void );
static bool UpdateFadeOut( void );


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff = NULL;
Fade g_fade;	// フェード


//==============================================================================
// 関数実装部
//==============================================================================
//------------------------------------------------
// フェードの初期化
//------------------------------------------------
HRESULT InitFade( void )
{
	// 初期パラメータ
	g_fade.obj.pos = D3DXVECTOR3( kFadePosX, kFadePosY, 0 );
	g_fade.obj.spd = D3DXVECTOR3( 0, 0, 0 );
	g_fade.obj.rot = D3DXVECTOR3( 0, 0, 0 );
	g_fade.obj.size = D3DXVECTOR3( kFadeWidth, kFadeHeight, 0 );
	g_fade.obj.length = 0;
	g_fade.obj.angle = 0;

	// デバイスハンドルの取得
	LPDIRECT3DDEVICE9 pDevice;
  pDevice = DeviceHolder::Instance().GetDevice();

	// 頂点バッファの生成(メモリの確保)
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof( Vertex2 ) * kVertexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pD3DVtxBuff,
		NULL
	);

	// if 生成に失敗したら
	if( FAILED( hr ) ) {
		return E_FAIL;
	}

	// ポリゴンの対角線の長さの計算
	g_fade.obj.length = sqrtf( ( g_fade.obj.size.x / 2 ) * ( g_fade.obj.size.x / 2 ) + ( g_fade.obj.size.y / 2 ) * ( g_fade.obj.size.y / 2 ) );

	// ポリゴンの中心点から対角線に対する角度の計算
	g_fade.obj.angle = atan2f( g_fade.obj.size.x, g_fade.obj.size.y );

	// アルファの設定
	g_fade.alpha = 0.0f;

	// 頂点情報の設定
	Vertex2* pVtx;
	// 占有開始
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );
	// 座標の設定
	pVtx[ 0 ].vtx.x = g_fade.obj.pos.x - sinf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 0 ].vtx.y = g_fade.obj.pos.y - cosf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 1 ].vtx.x = g_fade.obj.pos.x + sinf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 1 ].vtx.y = g_fade.obj.pos.y - cosf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 2 ].vtx.x = g_fade.obj.pos.x - sinf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 2 ].vtx.y = g_fade.obj.pos.y + cosf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 3 ].vtx.x = g_fade.obj.pos.x + sinf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 3 ].vtx.y = g_fade.obj.pos.y + cosf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;

	// rhwの設定
	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	// 反射光の設定
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

	// 占有終了
	g_pD3DVtxBuff->Unlock();

	// テクスチャの読み込み
	/*
	D3DXCreateTextureFromFile( pDevice,
							   kTextureFilename,
							   &g_pD3DTex );
	*/

	return S_OK;
}

//------------------------------------------------
// フェードの終了処理
//------------------------------------------------
void UninitFade( void )
{
	// 頂点バッファの解放
	SafeRelease( g_pD3DVtxBuff );
}

//------------------------------------------------
// フェードの更新処理
// フェードアウト完了時にtrueを返す
// それ以外はfalse
//------------------------------------------------
bool UpdateFade( void )
{
	// 状態により分岐
	switch( g_fade.fade_mode ){
	case FADE_NONE:
		break;
	case FADE_IN:
		return UpdateFadeIn();
		break;
	case FADE_OUT:
		return UpdateFadeOut();
		break;
	default:
		break;
	}
	return false;
}

//------------------------------------------------
// フェードの描画処理
//------------------------------------------------
void DrawFade( void )
{
	// デバイスハンドルの取得
  LPDIRECT3DDEVICE9 m_device = DeviceHolder::Instance().GetDevice();
	
	// レンダーステートパラメータの設定
	// 背面カリング
	m_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	// Zバッファ使用
	m_device->SetRenderState( D3DRS_ZENABLE, TRUE );
	// アルファブレンド使用
	m_device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// ソースと対象のアルファブレンド比率設定
	m_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// ソースのアルファをそのまま使用し、対象はそれの補数？をとる
	m_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	
	// 頂点ストリームにバインド
	m_device->SetStreamSource( 0, g_pD3DVtxBuff, 0, sizeof( Vertex2 ) );

	// FVFの設定
	m_device->SetFVF( FVF_VERTEX_2D );

	// テクスチャのセット
	m_device->SetTexture( 0, NULL );

	// ポリゴンの描画
	m_device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}

//------------------------------------------------
// フェードの設定
//------------------------------------------------
void SetFade( Fades fade )
{
	g_fade.fade_mode = fade;
}


//==============================================================================
// 内部関数実装部
//==============================================================================
//------------------------------------------------
// フェードインの更新処理
//------------------------------------------------
static bool UpdateFadeIn( void ) {
	// アルファの減算
  bool done_fade_in = false;
  g_fade.alpha -= kFadeSpd;
	// if アルファの最小値を越えていたら
	if( g_fade.alpha <= 0 ) {
		// 最小値を設定して通常状態へ
		g_fade.alpha = 0;
		g_fade.fade_mode = FADE_NONE;
    done_fade_in = true;
  }

	// 頂点情報の設定
	Vertex2* pVtx;
	// 占有開始
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );

	// 反射光の設定
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// 占有終了
	g_pD3DVtxBuff->Unlock();

  return done_fade_in;
}

//------------------------------------------------
// フェードアウトの更新処理
//------------------------------------------------
static bool UpdateFadeOut( void ) {
	bool done_fade_out = false;
	// アルファの加算
	g_fade.alpha += kFadeSpd;
	// if アルファの最大値を超えていたら
	if( g_fade.alpha > kAlphaMax ) {
		// 最大値を設定して通常状態へ
		g_fade.alpha = kAlphaMax;
		g_fade.fade_mode = FADE_NONE;
		done_fade_out = true;
	}

	// 頂点情報の設定
	Vertex2* pVtx;
	// 占有開始
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );

	// 反射光の設定
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// 占有終了
	g_pD3DVtxBuff->Unlock();

	return done_fade_out;
}
