//==============================================================================
//
// Cursor
// Author: Shimizu Shoji
//
// 2次元カーソルではない
// カーソルクラス...というかただの値循環クラス
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<int T_MAX>
class Cursor {
public:
  // ctor
  Cursor() : cursor_(0) {
  }

  // dtor
  ~Cursor() {}

  // Increment
  void Increment(void) {
    cursor_ = (cursor_ == (T_MAX - 1)) ? 0 : (cursor_ + 1);
  }

  // Decrement
  void Decrement(void) {
    cursor_ = (cursor_ == 0) ? (T_MAX - 1) : (cursor_ - 1);
  }

  // get
  int GetCursor(void) const { return cursor_; }

private:
  int cursor_;
};
