//==============================================================================
//
// ValueUpdater
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ValueUpdater {
public:
  // ctor
  ValueUpdater(float value, float change_amount);

  // Update
  // ���̊֐����Ăԓx�ɒl���X�V�����
  // �ݒ�l�ɓ��B���Ă���Ԃ�true��Ԃ�������
  bool Update(void);

  // �ڕW�l�ƕω��ʂ��w��
  void SetTargetValue(float target_value) { target_value_ = target_value; }
  void SetChangeAmount(float change_amount) { change_amount_ = change_amount; }

private:
  float change_amount_;
  float value_;
  float target_value_;
};
