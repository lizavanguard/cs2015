//==============================================================================
//
// WrapValue
// Author: Shimizu Shoji
//
// ÇΩÇæÇÃílèzä¬ÉNÉâÉX
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class WrapValue {
public:
  // ctor
  WrapValue(unsigned int max) : max_(max), value_(0) {
  }

  // dtor
  ~WrapValue() {}

  // Increment
  void Increment(void) {
    value_ = (value_ == (max_ - 1)) ? 0 : (value_ + 1);
  }

  // Decrement
  void Decrement(void) {
    value_ = (value_ == 0) ? (max_ - 1) : (value_ - 1);
  }

  // get
  int GetValue(void) const { return value_; }

private:
  unsigned int max_;
  int value_;
};
