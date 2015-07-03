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

#include "Application/Tension/TensionTopLayer.h"
#include "Application/Utility/ValueActiveUpdater.h"
#include "Application/Utility/ValuePassiveUpdater.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kFrameTextureFilename = "data/Texture/UI_tension_min.png";

const float kRateToFixSize = 0.4f;
const D3DXVECTOR3 kPos = {150.0f, 100.0f, 0.0f};
const D3DXVECTOR2 kSize = {1277.0f, 289.0f};

const D3DXVECTOR2 kFixedSize = kSize * kRateToFixSize;
const D3DXVECTOR2 kGaugeSize = {kSize.x, 221.0f - 56.0f};
const D3DXVECTOR2 kFixedGaugeSize = kGaugeSize * kRateToFixSize;

const D3DXVECTOR3 kGaugePos = {kPos.x, (kPos.y - kFixedSize.y * 0.5f) + (56.0f * kRateToFixSize + kFixedGaugeSize.y * 0.5f), 0.0f};

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
    , p_frame_(nullptr)
    , p_top_layer_(nullptr)
    , p_value_active_updater_(nullptr)
    , p_value_passive_updater_(nullptr) {
  p_frame_ = new Object2D(kPos, kFixedSize, kFrameTextureFilename);
  p_top_layer_ = new TensionTopLayer(kGaugePos, kFixedGaugeSize);
  p_value_active_updater_ = new ValueActiveUpdater(0.0f, kTensionActiveSpeedUpAmount, 0.0f, kTensionMaxValue);
  p_value_passive_updater_ = new ValuePassiveUpdater(0.0f, -kTensionPassiveChangeAmount, 0.0f, kTensionMaxValue);
}

//------------------------------------------------
// dtor
//------------------------------------------------
TensionGauge::~TensionGauge() {
  SafeDelete(p_value_passive_updater_);
  SafeDelete(p_value_active_updater_);
  SafeDelete(p_top_layer_);
  SafeDelete(p_frame_);
}

//------------------------------------------------
// update
//------------------------------------------------
void TensionGauge::Update(void) {
  _UpdateTension();
  p_top_layer_->UpdateSize(tension_);
}

//------------------------------------------------
// Drawの前後処理
//------------------------------------------------
void TensionGauge::Draw(void) {
  p_frame_->Draw();
  p_top_layer_->Draw();
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
