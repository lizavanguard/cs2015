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
  void Draw(void);

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
