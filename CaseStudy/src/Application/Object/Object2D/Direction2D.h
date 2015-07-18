//==============================================================================
//
// Direction2D
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2D.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Direction2D : public Object2D {
public:
  // ctor
  Direction2D();

  // dtor
  ~Direction2D();

  // Aから見た時のBへの方向を計算してセット
  void CalcRotationUsingPosition(const D3DXVECTOR3& pos_a, const D3DXVECTOR3& pos_b);

  // set
  void SetRotation(float rotation) { rot_ = rotation; }

  void Alive(void) { is_alive_ = true; }
  void Dead(void) { is_alive_ = false; }
};
