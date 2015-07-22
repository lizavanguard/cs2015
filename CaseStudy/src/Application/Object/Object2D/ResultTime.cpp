//******************************************************************************
//
// クリアタイム処理  [ResultTime.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework\FrameworkOption.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

#include "Object2D.h"
#include "ResultTime.h"
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
namespace{
    const int kCountMax = kFPS * 5;

    const int kCountLimit = 99;

    const int kResultTime = 60;
}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//==============================================================================
ResultTime::ResultTime(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, NUMBER_TYPE type){
  value_ = 0;
  count_ = 0;
//  timer_value = timer->GetTimeValue();
  p_number_object_ = new NumberObject *[MAX_FIGURE];

  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(0);
  }
}

//==============================================================================
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//==============================================================================
ResultTime::~ResultTime(void){
  for (int num = 0; num < MAX_FIGURE; num++){
      delete p_number_object_[num];
      p_number_object_[num] = nullptr;
  }
  delete[] p_number_object_;
  p_number_object_ = nullptr;
}

//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//==============================================================================
void ResultTime::Update(){
  // カウントが
  if (count_ > kCountMax){
      value_ = kResultTime;
  }
  else{
      value_ += 21;
      ++count_;
  }
  if (value_ > kCountLimit)
      value_ -= kCountLimit;
  // 桁の設定変数
  unsigned int figure = (unsigned int)pow((float)FIGURE_DEFINE, MAX_FIGURE);
  for (int num = 0; num < MAX_FIGURE; num++)
  {
    // 特定の桁の値を入れる
    int value = (value_ % figure) / (figure / FIGURE_DEFINE);
    // 値をセット
    p_number_object_[num]->SetValue(value);
    // 桁ずらし
    figure /= FIGURE_DEFINE;
  }
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//==============================================================================
void ResultTime::Draw(void){
  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_number_object_[num]->Draw();
  }
}


// EOF