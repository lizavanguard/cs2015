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
class Bar;
class Board;
class Frame;
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
  // �e���V�������ő�ɂȂ����Ƃ��ɐ^��Ԃ�
  bool IncreaseTension(void);

  // Cool down Tension
  // �e���V�������Œ�܂ŉ�����
  void CoolDown(void);

private:
  void _UpdateTension(void);

  float tension_;
  Bar* p_bar_;
  Board* p_board_;
  Frame* p_frame_;
  ValueActiveUpdater* p_value_active_updater_;
  ValuePassiveUpdater* p_value_passive_updater_;
};