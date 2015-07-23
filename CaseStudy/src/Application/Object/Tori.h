//==============================================================================
//
// �� [Tori.h]
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
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FLY_TO_TOP_SPEED (9.0f)  // ��֔�ԑ��x

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

  // �������Ă�����true���Ԃ�
  bool GetHitCheck(void){ return hit_flag_; }
  bool GetEndFlag(void){ return end_flag_; }

private:
  static const int kFlyToTopSpeed = 9;                 // ��֔�ԑ��x
  static const int kTimeToFlyToBecomeGealthy = 30;     // ���C�ɂȂ��Ă����Ԃ܂ł̎���
  float move_speed_;
  int motion_timer_;
  Uriel *p_uriel_;
  Stage *p_stage_;
  bool hit_flag_;
  bool happy_flag_;
  int animation_time_;
  int anim_cnt_;
  bool end_flag_;
};


#endif // __H_TORI_H__
//