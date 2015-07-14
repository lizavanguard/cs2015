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
#include "Application/Object/AnimationObject/AnimationObject.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Effect : public AnimationObject {
public:
  // ctor
  Effect();

  // dtor
  ~Effect();

  // Update
  void Update(void);

  // Set parameter
  void SetParameter(const D3DXVECTOR3& position, const D3DXVECTOR3& velocity, ANIMATION_EVENT animation_event, float scale);

  // get
  bool IsAlive(void) const { return is_alive_; }

private:
  unsigned int count_;
  unsigned int lifetime_;

  D3DXVECTOR3 velocity_;
};
