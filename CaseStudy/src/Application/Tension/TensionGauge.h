//==============================================================================
//
// TensionGauge
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2D;
class TensionTopLayer;
class ValueActiveUpdater;
class ValuePassiveUpdater;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class TensionGauge {
public:
  // ctor
  TensionGauge();

  // dtor
  ~TensionGauge();

  // Update
  void Update(void);

  /// Draw
  void Draw(void);

  // tension up
  // テンションが最大になったときに真を返す
  bool IncreaseTension(void);

  // Cool down Tension
  // テンションを最低まで下げる
  void CoolDown(void);

private:
  void _UpdateTension(void);

  float tension_;
  Object2D* p_frame_;
  TensionTopLayer* p_top_layer_;
  ValueActiveUpdater* p_value_active_updater_;
  ValuePassiveUpdater* p_value_passive_updater_;
};
