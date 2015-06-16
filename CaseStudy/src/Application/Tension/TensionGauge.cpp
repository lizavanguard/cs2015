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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const D3DXVECTOR3 kPos = {300.0f, 200.0f, 0.0f};
const D3DXVECTOR2 kSize = {300.0f, 20.0f};

const float kTensionRiseValue = 0.4f;
const float kTensionMaxValue = 1.0f;

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
    , p_frame_(nullptr) {
  p_bar_ = new Bar(kPos, kSize, kTensionMaxValue);
  p_board_ = new Board(kPos, kSize);
  p_frame_ = new Frame(kPos, kSize);
}

//------------------------------------------------
// dtor
//------------------------------------------------
TensionGauge::~TensionGauge() {
  SafeDelete(p_frame_);
  SafeDelete(p_board_);
  SafeDelete(p_bar_);
}

//------------------------------------------------
// tension up
// テンションが最大になったときに真を返す
//------------------------------------------------
bool TensionGauge::IncreaseTension(void) {
  tension_ += kTensionRiseValue;
  std::max<float>(tension_, kTensionMaxValue);
  return tension_ == kTensionMaxValue;
}

//------------------------------------------------
// Cool down
// テンションを最低まで下げる
//------------------------------------------------
void TensionGauge::CoolDown(void) {
  tension_ = 0.0f;
}

//------------------------------------------------
// Drawの前後処理
//------------------------------------------------
void TensionGauge::Draw(void) {
  p_board_->Draw();
  p_bar_->Draw();
  p_frame_->Draw();
}
