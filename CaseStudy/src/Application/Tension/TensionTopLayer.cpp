//==============================================================================
//
// TensionTopLayer
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "TensionTopLayer.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTextureFilename = "data/Texture/UI_tension_max.png";

const float kTop = 56.0f / 289.0f;
const float kBottom = 221.0f / 289.0f;
const float kRange = kBottom - kTop;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
TensionTopLayer::TensionTopLayer(const D3DXVECTOR3& pos, const D3DXVECTOR2& size) 
    : Object2D(pos, size, kTextureFilename)
    , original_height_(size.y)
    , original_bottom_(pos.y + size.y * 0.5f) {
  end_uv_.y = kBottom;
  UpdateSize(0.0f);
}

//------------------------------------------------
// Update size
// 0-1の間で値を渡すとサイズを更新する
//------------------------------------------------
void TensionTopLayer::UpdateSize(const float rate) {
  assert(0.0f <= rate && rate <= 1.0f);
  size_.y = original_height_ * rate;
  pos_.y = original_bottom_ - size_.y * 0.5f;

  const float v_amount = (rate * kRange);
  start_uv_.y = kBottom - v_amount;
}

//------------------------------------------------
// Drawの前後処理
//------------------------------------------------
void TensionTopLayer::_PreProcessOfDraw(void) {
}

void TensionTopLayer::_PostProcessOfDraw(void) {
}