//==============================================================================
//
// Bar
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Bar.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTextureFilename = "data/Texture/square.png";

const DWORD kBarColor = 0xffff0000;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Bar::Bar(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const float max_value)
    : max_value_(max_value)
    , original_position_(D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, pos.z))
    , original_size_(size) {
  assert(max_value > 0.0f);
  SetTexture(kTextureFilename);
  pos_ = pos;
  size_ = size;
  color_ = kBarColor;

  _UpdatePosAndSize(0.5f);
}

//------------------------------------------------
// update value
//------------------------------------------------
void Bar::UpdateValue(const float value) {
  assert(value <= max_value_);
  const float rate = value / max_value_;
  _UpdatePosAndSize(rate);
}

//------------------------------------------------
// Draw‚Ì‘OŒãˆ—
//------------------------------------------------
void Bar::_PreProcessOfDraw(void) {
}

void Bar::_PostProcessOfDraw(void) {
}

//------------------------------------------------
// Update pos and size
//------------------------------------------------
void Bar::_UpdatePosAndSize(const float rate) {
  assert(0.0f <= rate && rate <= 1.0f);
  size_.x = original_size_.x * rate;
  pos_.x = original_position_.x + size_.x * 0.5f;
}
