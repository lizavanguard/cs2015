//==============================================================================
//
// ValueActiveUpdater
// Author: Shimizu Shoji
//
// 目標値に向かって一定の変化量で変化し続ける
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ValueActiveUpdater {
public:
  // ctor
  ValueActiveUpdater(float value, float change_speed, float min, float max);

  // Update
  // この関数を呼ぶ度に値が更新される
  // 目標値に到達している間はtrueを返し続ける
  bool Update(void);

  // 目標値を割り当てる
  void AssignTargetValue(float target_value);

  // get
  float GetValue(void) const { return value_; }
  bool IsActive(void) const { return value_ != target_value_; }

  // set
  void SetValue(float value) { _CheckValue(value); value_ = target_value_ = value; }
  void SetChangeSpeed(float change_speed) { change_speed_ = change_speed; }

private:
  void _CheckValue(float value) { assert(min_ <= value && value <= max_); }

  float change_speed_;
  float target_value_;
  float max_;
  float min_;
  float value_;
  int sign_;
};
