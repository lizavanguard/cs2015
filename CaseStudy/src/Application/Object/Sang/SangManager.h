//==============================================================================
//
// ��Q���Ǘ��N���X [SangManager.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_SANGMANGER_H__
#define __H_SANGMANGER_H__
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
class Uriel;
class SangManager{
public:
  // ctor
  SangManager();

  // dtor
  virtual ~SangManager();

  // update
  void Update(void);

  // draw
  void Draw(void);

  static void AddToSang(AnimationObject* sang, AnimationObject::ANIM_OBJ_TYPE anim_obj_type);

  void SetUrielPointer(Uriel* p_uriel){ p_uriel_ = p_uriel; }

private:
  static const int kPlayerSangPower = 10;
  static const int kButterflySangPower = 20;
  static const int kFlowerSangPower = 14;
  static const int kSetSangViewLength = 300;              // 3�u���b�N�悾������E���G���ɖړI�n�Ƃ��Đݒ�
  static AnimationObject* sang_object_top_;
  static AnimationObject* sang_object_cur_;
  Uriel* p_uriel_;
};


#endif // __H_SANGMANGER_H__
//