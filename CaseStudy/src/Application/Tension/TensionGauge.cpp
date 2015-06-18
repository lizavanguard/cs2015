//==============================================================================
//
// TensionGauge
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "TensionGauge.h"

#include <algorithm>

#include "Application/Object/Object2D/Bar.h"
#include "Application/Object/Object2D/Board.h"
#include "Application/Object/Object2D/Frame.h"
#include "Application/Utility/ValueActiveUpdater.h"
#include "Application/Utility/ValuePassiveUpdater.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const D3DXVECTOR3 kPos = {200.0f, 25.0f, 0.0f};
const D3DXVECTOR2 kSize = {300.0f, 20.0f};

const float kTensionRiseValue = 0.4f;
const float kTensionMaxValue = 1.0f;
const float kTensionPassiveChangeAmount = 0.001f;
const float kTensionActiveSpeedUpAmount = 0.01f;
const float kTensionActiveSpeedDownAmount = 0.05f;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
TensionGauge::TensionGauge()
    : tension_(0.0f)
    , p_bar_(nullptr)
    , p_board_(nullptr)
    , p_frame_(nullptr)
    , p_value_active_updater_(nullptr)
    , p_value_passive_updater_(nullptr) {
  p_bar_ = new Bar(kPos, kSize, kTensionMaxValue);
  p_board_ = new Board(kPos, kSize);
  p_frame_ = new Frame(kPos, kSize);
  p_value_active_updater_ = new ValueActiveUpdater(0.0f, kTensionActiveSpeedUpAmount, 0.0f, kTensionMaxValue);
  p_value_passive_updater_ = new ValuePassiveUpdater(0.0f, -kTensionPassiveChangeAmount, 0.0f, kTensionMaxValue);
}

//------------------------------------------------
// dtor
//------------------------------------------------
TensionGauge::~TensionGauge() {
  SafeDelete(p_value_passive_updater_);
  SafeDelete(p_value_active_updater_);
  SafeDelete(p_frame_);
  SafeDelete(p_board_);
  SafeDelete(p_bar_);
}

//------------------------------------------------
// update
//------------------------------------------------
void TensionGauge::Update(void) {
  _UpdateTension();

  p_bar_->UpdateValue(tension_);
}

//------------------------------------------------
// Drawの前後処理
//------------------------------------------------
void TensionGauge::Draw(void) {
  p_board_->Draw();
  p_bar_->Draw();
  p_frame_->Draw();
}

//------------------------------------------------
// tension up
// テンションが最大になったときに真を返す
//------------------------------------------------
bool TensionGauge::IncreaseTension(void) {
  const float target_value = tension_ + kTensionRiseValue;
  p_value_active_updater_->AssignTargetValue(target_value);
  p_value_active_updater_->SetChangeSpeed(kTensionActiveSpeedUpAmount);
  return target_value >= kTensionMaxValue;
}

//------------------------------------------------
// Cool down
// テンションを最低まで下げる
//------------------------------------------------
void TensionGauge::CoolDown(void) {
  p_value_active_updater_->AssignTargetValue(0.0f);
  p_value_active_updater_->SetChangeSpeed(kTensionActiveSpeedDownAmount);
}

//------------------------------------------------
// update tension
//------------------------------------------------
void TensionGauge::_UpdateTension(void) {
  // 能動的に値が変化している場合
  if (p_value_active_updater_->IsActive()) {
    p_value_active_updater_->Update();
    tension_ = p_value_active_updater_->GetValue();
    p_value_passive_updater_->SetValue(tension_);
  }
  // 受動的に値が変化している場合
  else {
    p_value_passive_updater_->Update();
    tension_ = p_value_passive_updater_->GetValue();
    p_value_active_updater_->SetValue(tension_);
  }
}
