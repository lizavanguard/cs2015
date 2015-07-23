//==============================================================================
//
// 鳥 [Tori.h]
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
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FLY_TO_TOP_SPEED (9.0f)  // 上へ飛ぶ速度

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

  // 当たっていたらtrueが返る
  bool GetHitCheck(void){ return hit_flag_; }
  bool GetEndFlag(void){ return end_flag_; }

private:
  static const int kFlyToTopSpeed = 9;                 // 上へ飛ぶ速度
  static const int kTimeToFlyToBecomeGealthy = 30;     // 元気になってから飛ぶまでの時間
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