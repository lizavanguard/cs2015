//==============================================================================
//
// íπ [Tori.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_TORI_H__
#define __H_TORI_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "AnimationObject/AnimationObject.h"
#include "Uriel.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage;
class Tori : public AnimationObject {
public:
  // ctor
  Tori(ANIMATION_EVENT animation_event, Uriel *uriel, Stage *stage);

  // dtor
  virtual ~Tori();

  // update
  void Update(void);

  // draw
  virtual void _PreProcessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // ìñÇΩÇ¡ÇƒÇ¢ÇΩÇÁtrueÇ™ï‘ÇÈ
  bool GetHitCheck(void){ return hit_flag_; }

private:
  static const int kFlyToTopSpeed = 9;                 // è„Ç÷îÚÇ‘ë¨ìx
  static const int kTimeToFlyToBecomeGealthy = 30;     // å≥ãCÇ…Ç»Ç¡ÇƒÇ©ÇÁîÚÇ‘Ç‹Ç≈ÇÃéûä‘
  float move_speed_;
  int motion_timer_;
  Uriel *p_uriel_;
  Stage *p_stage_;
  bool hit_flag_;
  bool happy_flag_;
  int animation_time_;
};


#endif // __H_TORI_H__
