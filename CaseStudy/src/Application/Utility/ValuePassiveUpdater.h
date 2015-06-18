//==============================================================================
//
// ValuePassiveUpdater
// Author: Shimizu Shoji
//
// ���t���[���l�����Z��������
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ValuePassiveUpdater {
public:
  // ctor
  ValuePassiveUpdater(float value, float change_speed, float max, float min);

  // Update
  // ���̊֐����Ăԓx�ɒl���X�V�����
  void Update(void);

  // get
  float GetValue(void) const { return value_; }

  // set
  void SetValue(float value) { _CheckValue(value); value_ = value; }
  void SetChangeSpeed(float change_speed) { change_speed_ = change_speed; }

private:
  void _CheckValue(float value) { assert(min_ <= value && value <= max_); }
  float change_speed_;
  float max_;
  float min_;
  float value_;
};
