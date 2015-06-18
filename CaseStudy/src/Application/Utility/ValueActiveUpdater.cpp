//==============================================================================
//
// ValueActiveUpdater
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "ValueActiveUpdater.h"

#include <algorithm>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ValueActiveUpdater::ValueActiveUpdater(const float value, const float change_speed, const float min, const float max)
    : change_speed_(change_speed)
    , target_value_(value)
    , max_(max)
    , min_(min)
    , value_(value)
    , sign_(1) {
  assert(min <= max);
  _CheckValue(value);
}

//------------------------------------------------
// Update
// 設定値に到達している間はtrueを返し続ける
//------------------------------------------------
bool ValueActiveUpdater::Update(void) {
  if (value_ == target_value_) {
    return true;
  }

  if (sign_ == 1) {
    assert(value_ < target_value_);
    value_ = std::min<float>(value_ + sign_ * change_speed_, target_value_);
    return value_ == target_value_;
  }
  else {
    assert(value_ > target_value_);
    value_ = std::max<float>(value_ + sign_ * change_speed_, target_value_);
    return value_ == target_value_;
  }
}


//------------------------------------------------
// 目標値を割り当てる
//------------------------------------------------
void ValueActiveUpdater::AssignTargetValue(const float target_value) {
  target_value_ = std::max<float>(std::min<float>(target_value, max_), min_);
  sign_ = target_value_ >= value_ ? 1 : -1;
}