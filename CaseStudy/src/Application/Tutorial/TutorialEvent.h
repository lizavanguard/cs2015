//==============================================================================
//
// TutorialEvent[TutorialEvent.h]
// Author: Yuji Momoi
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/Object2D/Object2D.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Uriel;
class Player;
class Stage;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class TutorialEvent : public Object2D {
public:
  // ctor
  TutorialEvent(Uriel* p_uriel, Player* p_player, Stage* p_stage);

  // dtor
  ~TutorialEvent();

  // Update
  virtual void Update(void);

  // Draw
  virtual void _PreProcessOfDraw(void);
  virtual void _PostProcessOfDraw(void);

  // get
  bool IsEnd(void) const { return is_end_; }
  bool ViewEvent(void) const { return view_event_flag_; }

private:
  typedef enum{
    EVENT_NAME_NONE = -1,
    EVENT_NAME_START,
    EVENT_NAME_START2,
    EVENT_NAME_CALL,
    EVENT_NAME_JUNP,
    EVENT_NAME_CHARGE_JUNP,
    EVENT_NAME_RUNAWAY,
    EVENT_NAME_BUILDING_BLOCK,
    EVENE_NAME_LEAD_URIEL,
    EVENT_NAME_MAX,
  }EVENT_NAME;
  static const int kTutorialEventMax = EVENT_NAME_MAX;
  static const int kTutorialEventHitSize = 10;           // チュートリアルイベントの表示判定サイズ

  bool view_event_flag_;
  int texture_ids_[kTutorialEventMax];
  bool event_view_flag_[kTutorialEventMax];
  bool use_flag_[kTutorialEventMax];
  bool already_used_flag_[kTutorialEventMax];
  bool is_end_;
  Uriel* p_uriel_;
  int event_number_;
  bool TutorialEventCheck(void);
  void EventUpdate(void);
  Player* p_player_;
  Stage* p_stage_;
};
