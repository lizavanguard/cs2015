//******************************************************************************
//
// タイマー処理  [timer.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Object2D.h"
#include "Timer.h"
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


//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
Timer::Timer(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, NUMBER_TYPE type){
  value_ = TIMER_COUNT;
  count_ = 0;

  p_numberObject_ = new NumberObject * [2];

  // 桁の設定変数
  unsigned int figure = (unsigned int)pow((float)FIGURE_DEFINE, MAX_FIGURE);
  for (int num = 0; num < MAX_FIGURE; num++)
  {
    // 特定の桁の値を入れる
    int value = (value_ % figure) / (figure / FIGURE_DEFINE);
    // 値をセット
    p_numberObject_[num] = new NumberObject(D3DXVECTOR3(pos.x + 40.0f*num, pos.y, pos.z), rot, size, type);
    p_numberObject_[num]->SetValue(value);
    // 桁ずらし
    figure /= FIGURE_DEFINE;
  }
}

//==============================================================================
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
Timer::~Timer(void){
  for (int num = 0; num < MAX_FIGURE; num++){
    delete p_numberObject_[num];
    p_numberObject_[num] = nullptr;
  }
  delete[] p_numberObject_;
  p_numberObject_ = nullptr;
}

//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
void Timer::Update(){
  ++count_;
  if ((count_ % 30) == 0)
  {
    --value_;
    // タイムリセット
    if (value_ < 0)
        value_ = TIMER_COUNT;
    count_ = 0;
  }
  // 桁の設定変数
  unsigned int figure = (unsigned int)pow((float)FIGURE_DEFINE, MAX_FIGURE);
  for (int num = 0; num < MAX_FIGURE; num++)
  {
    // 特定の桁の値を入れる
    int value = (value_ % figure) / (figure / FIGURE_DEFINE);
    // 値をセット
    p_numberObject_[num]->SetValue(value);
    // 桁ずらし
    figure /= FIGURE_DEFINE;
  }
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
void Timer::Draw(void){
  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_numberObject_[num]->Draw();
  }
}


// EOF