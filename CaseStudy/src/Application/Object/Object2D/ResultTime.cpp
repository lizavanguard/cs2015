//******************************************************************************
//
// クリアタイム処理  [ResultTime.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/14
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

    const int kCountLimit = kOneMinute * 60;
}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/14
//==============================================================================
ResultTime::ResultTime(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, const int &value, NUMBER_TYPE type){
  value_ = 0;
  count_ = 0;
  timer_value_ = value;

  p_number_object_ = new NumberObject *[kMaxFigure];

  for (int num = 0; num < 2; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(0);
  }
  for (int num = 2; num < 4; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num+20.0f, pos.y, pos.z), rot, size, type);
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
    for (int num = 0; num < kMaxFigure; num++){
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
// 更新日  :  2015/07/14
//==============================================================================
void ResultTime::Update(){
  // 一定時間が立ったらタイムを表示する
  if (count_ > kCountMax){
      value_ = timer_value_;
  }
  // 適当に値を動かす
  else{
      value_ += 2121;
      ++count_;
  }
  if (value_ > kCountLimit)
      value_ -= kCountLimit;
  // 時間変数
  int minuteTime = value_ / kOneMinute;
  int secondTime = value_ - minuteTime * kOneMinute;
  // 桁の設定変数
  unsigned int figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  // 分
  for (int num = 0; num < 2; num++)
  {
      // 特定の桁の値を入れる
      int value = (minuteTime % figure) / (figure / kFigureDefine);
      // 値をセット
      p_number_object_[num]->SetValue(value);
      // 桁ずらし
      figure /= kFigureDefine;
  }
  // 秒
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
// 更新日  :  2015/06/29
//==============================================================================
void ResultTime::Draw(void){
  for (int num = 0; num < kMaxFigure; num++)
  {
      p_number_object_[num]->Draw();
  }
}


// EOF