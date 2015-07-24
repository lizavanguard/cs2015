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
  value_ = kTimerCount;
  count_ = 0;
  time_up_ = false;

  p_number_object_ = new NumberObject *[kMaxFigure];
  // 時間変数
  int minuteTime = value_ / kOneMinute;
  int secondTime = value_ - minuteTime * kOneMinute;

  unsigned int figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  for (int num = 0; num < 2; num++)
  {
      // 特定の桁の値を入れる
      int value = (minuteTime % figure) / (figure / kFigureDefine);
      // 値をセット
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 40.0f*num, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(value);
      // 桁ずらし
      figure /= kFigureDefine;
  }

  p_object2D_ = new Object2D(D3DXVECTOR3(pos.x + 40.0f * 2 - 10.0f, pos.y, pos.z), size, "data/Texture/figure_coron.png");

  figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  for (int num = 2; num < 4; num++)
  {
      // 特定の桁の値を入れる
      int value = (secondTime % figure) / (figure / kFigureDefine);
      // 値をセット
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 40.0f*num + 20.0f, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(value);
      // 桁ずらし
      figure /= kFigureDefine;
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
  for (int num = 0; num < kMaxFigure; num++){
    delete p_number_object_[num];
    p_number_object_[num] = nullptr;
  }
  delete[] p_number_object_;
  p_number_object_ = nullptr;

  delete p_object2D_;
  p_object2D_ = nullptr;
}

//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
void Timer::Update(){
  if (time_up_){
    return;
  }

  ++count_;
  if ((count_ % 30) == 0)
  {
    --value_;
    // タイムリセット
    if (value_ < 0){
      value_ = 0;
      time_up_ = true;
    }
    count_ = 0;
  }
  int minuteTime = value_ / kOneMinute;
  int secondTime = value_ - minuteTime * kOneMinute;
  // 桁の設定変数
  unsigned int figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  for (int num = 0; num < 2; num++)
  {
      // 特定の桁の値を入れる
      int value = (minuteTime % figure) / (figure / kFigureDefine);
      // 値をセット
      p_number_object_[num]->SetValue(value);
      // 桁ずらし
      figure /= kFigureDefine;
  }
  figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  for (int num = 2; num < 4; num++)
  {
      // 特定の桁の値を入れる
      int value = (secondTime % figure) / (figure / kFigureDefine);
      // 値をセット
      p_number_object_[num]->SetValue(value);
      // 桁ずらし
      figure /= kFigureDefine;
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
    for (int num = 0; num < kMaxFigure; num++)
  {
      p_number_object_[num]->Draw();
  }
    p_object2D_->Draw();
}


// EOF