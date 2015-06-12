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
#define FLY_TO_TOP_SPEED (-9.0f)  // 上へ飛ぶ速度

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Tori : public AnimationObject {
public:
  // ctor
  Tori(ANIMATION_EVENT animation_event, Uriel *uriel);

  // dtor
  virtual ~Tori();

  // update
  void Update(void);

  // draw
  virtual void PreProccessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // 当たっていたらtrueが返る
  bool GetHitCheck(void){ return hit_flag_; }

private:
  float move_speed_;
  int motion_timer_;
  Uriel *p_uriel_;
  bool hit_flag_;
  bool happy_flag_;
  int animation_time_;
};


#endif // __H_TORI_H__
