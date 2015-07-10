//==============================================================================
//
// â‘ [Flower.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_FLOWER_H__
#define __H_FLOWER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Application/Object/AnimationObject/AnimationObject.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// É}ÉNÉçíËã`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage;
class Flower : public AnimationObject {
public:
  // ctor
  Flower(ANIMATION_EVENT animation_event, Stage *stage);

  // dtor
  virtual ~Flower();

  // update
  void Update(void);

  // draw
  virtual void _PreProcessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // set
  void SetPos(const D3DXVECTOR3& pos);

private:
  Stage *p_stage_;
  int animation_time_;
};


#endif // __H_FLOWER_H__
//