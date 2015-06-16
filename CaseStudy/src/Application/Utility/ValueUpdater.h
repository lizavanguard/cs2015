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
  // この関数を呼ぶ度に値が更新される
  // 設定値に到達している間はtrueを返し続ける
  bool Update(void);

  // 目標値と変化量を指定
  void SetTargetValue(float target_value) { target_value_ = target_value; }
  void SetChangeAmount(float change_amount) { change_amount_ = change_amount; }

private:
  float change_amount_;
  float value_;
  float target_value_;
};
