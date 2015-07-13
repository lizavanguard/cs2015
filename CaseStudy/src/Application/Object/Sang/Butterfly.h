//==============================================================================
//
// �� [Butterfly.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_BUTTERFLY_H__
#define __H_BUTTERFLY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Application/Object/AnimationObject/AnimationObject.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage;
class Butterfly : public AnimationObject {
public:
  // ctor
  Butterfly(ANIMATION_EVENT animation_event, Stage *stage);

  // dtor
  virtual ~Butterfly();

  // update
  void Update(void);

  // draw
  virtual void _PreProcessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // set
  void SetPos(const D3DXVECTOR3& pos);

  // get
  DIRECTION GetDirection(void){ return move_direction_; }

  static const int kButterFlyMoveSpeed = 2;          // ���̈ړ����x

private:
  static const int kMoveAmount = 200;                // �ړ��ʂ��ݒ肳��Ȃ��������̒��̈ړ���
  Stage *p_stage_;
  int animation_time_;
  D3DXVECTOR3 base_pos_;
  D3DXVECTOR3 move_;
};


#endif // __H_BUTTERFLY_H__
//