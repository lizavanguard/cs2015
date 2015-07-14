//******************************************************************************
//
// TitleChar  [TitleChar.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "TitleChar.h"
#include "Framework\GameManager\GameManager.h"
#include "Framework\DebugProc\DebugProc.h"

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
    const float kPosSpeed = 2.5f;

    const float kPosMoveMax = 100.0f;
}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//==============================================================================
TitleChar::TitleChar(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size ,
                    const float &speed , const float &movemax, const char* texName)
    : Object2D(pos, size, texName) {
  rot_ = rot;
  move_counter_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  change_pos_ = D3DXVECTOR3(0.0f, speed, 0.0f);
}

//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//==============================================================================
void TitleChar::Update(const float &movemax){
    pos_ += change_pos_;
    move_counter_ += change_pos_;
    if (abs(move_counter_.y) > movemax){
        change_pos_ *= -1;
        move_counter_.y = 0.0f;
    }
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//==============================================================================
void TitleChar::_PreProcessOfDraw(void){
}

void TitleChar::_PostProcessOfDraw(void){
}


// EOF