//==============================================================================
//
// ValueActiveUpdater
// Author: Shimizu Shoji
//
// �ڕW�l�Ɍ������Ĉ��̕ω��ʂŕω���������
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
  // ���̊֐����Ăԓx�ɒl���X�V�����
  // �ڕW�l�ɓ��B���Ă���Ԃ�true��Ԃ�������
  bool Update(void);

  // �ڕW�l�����蓖�Ă�
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
