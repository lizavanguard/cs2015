//==============================================================================
//
// ValuePassiveUpdater
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "ValuePassiveUpdater.h"

#include <algorithm>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ValuePassiveUpdater::ValuePassiveUpdater(const float value, const float change_speed, const float min, const float max)
    : change_speed_(change_speed)
    , max_(max)
    , min_(min)
    , value_(value) {
  assert(min <= max);
  _CheckValue(value);
}

//------------------------------------------------
// Update
// �ݒ�l�ɓ��B���Ă���Ԃ�true��Ԃ�������
//------------------------------------------------
void ValuePassiveUpdater::Update(void) {
  value_ = std::max<float>(std::min<float>(value_ + change_speed_, max_), min_);
}
