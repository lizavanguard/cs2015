//==============================================================================
//
// Effect
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/Object2D/Object2D.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Effect : public Object2D {
public:
  // ctor
  Effect();

  // dtor
  ~Effect();

  // Update
  void Update(void) {
    if (!is_alive_) return;
    pos_.x += 5.0f;
  }

  // set
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void Alive(void) { is_alive_ = true; }
  void Dead(void) { is_alive_ = false; }

private:
};
