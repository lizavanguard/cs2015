//==============================================================================
//
// アニメーションオブジェクト [AnimationObject.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_ANIMATION_OBJECT_H__
#define __H_ANIMATION_OBJECT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "../Object.h"
#include "TextureAnimation.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class AnimationObject : public Object {
public:

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 列挙体定義
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  typedef enum {
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
  }DIRECTION;

  // ctor
  AnimationObject(ANIMATION_EVENT animation_event);

  // dtor
  virtual ~AnimationObject();

  static AnimationObject* Create(ANIMATION_EVENT animation_event, const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

  // draw
  virtual void PreProccessOfDraw(void);
  virtual void PostProcessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);
  void AddPosY(float y) { pos_.y += y; }
  void AddPosZ(float z) { pos_.z += z; }

  // add rot
  void AddRot(const D3DXVECTOR2& rot) { rot_ += rot; }

  // add size
  void AddSize(const D3DXVECTOR2& size) { size_ += size; }

  // get
  D3DXVECTOR3 GetPos(void) const { return pos_; }
  D3DXVECTOR2 GetRot(void) const { return rot_; }
  D3DXVECTOR2 GetSize(void) const { return size_; }
  bool IsAlive(void) const { return is_alive_; }

  // set
  void SetPos(const D3DXVECTOR3& pos) { pos_ = pos; }
  void SetRot(const D3DXVECTOR2& rot) { rot_ = rot; }
  void SetSize(const D3DXVECTOR2& size) { size_ = size; }
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }
  void SetAnimaton(ANIMATION_EVENT animation_event);

protected:
  TextureAnimation *p_texture_animation_;
  DIRECTION move_direction_;
};


#endif // __H_ANIMATION_OBJECT_H__
