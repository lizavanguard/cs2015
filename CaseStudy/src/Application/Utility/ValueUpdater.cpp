//==============================================================================
//
// ValueUpdater
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "ValueUpdater.h"

#include <algorithm>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ValueUpdater::ValueUpdater(const float value, const float change_amount)
    : change_amount_(change_amount)
    , value_(value)
    , target_value_(value) {
}

//------------------------------------------------
// Update
// Ý’è’l‚É“ž’B‚µ‚Ä‚¢‚éŠÔ‚Ítrue‚ð•Ô‚µ‘±‚¯‚é
//------------------------------------------------
bool ValueUpdater::Update(void) {
  if (value_ == target_value_) {
    return true;
  }

  if (change_amount_ > 0.0f) {
    assert(value_ > target_value_);
    value_ = std::min<float>(value_ + change_amount_, target_value_);
    return value_ == target_value_;
  }
  else {
    assert(value_ < target_value_);
    value_ = std::max<float>(value_ + change_amount_, target_value_);
    return value_ == target_value_;
  }
}
