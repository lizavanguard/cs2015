//******************************************************************************
//
// WindowBack  [WindowBack.cpp]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "WindowBack.h"
#include "Framework/FrameworkOption.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/DebugProc/DebugProc.h"

//******************************************************************************
// マクロ定義
//******************************************************************************


//******************************************************************************
// プロトタイプ宣言
//******************************************************************************


//******************************************************************************
// メンバ変数:
//******************************************************************************


//******************************************************************************
// グローバル変数:
//******************************************************************************
namespace {

    const char* kTextureFilename = "data/Texture/pauseWindow.jpg";

    const DWORD kWindowBackColor = 0xffffffff;


}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
WindowBack::WindowBack(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size)
    : Object2D(pos, size, kTextureFilename) {
  rot_ = rot;
  color_ = kWindowBackColor;
}

void WindowBack::Update(){

}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
void WindowBack::_PreProcessOfDraw(void){
}

void WindowBack::_PostProcessOfDraw(void){
}


// EOF