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
//#include "Application/Object/AnimationObject/AnimationObject.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Effect : public Object2D {
//class Effect : public AnimationObject {
public:
  // ctor
  Effect();

  // dtor
  ~Effect();

  // Update
  void Update(void);

  // Set parameter
  void SetParameter(const D3DXVECTOR3& position, const D3DXVECTOR3& velocity, float size, unsigned int lifetime, int texture_id);

  // get
  bool IsAlive(void) const { return is_alive_; }

  // set
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }

private:
  unsigned int count_;
  unsigned int lifetime_;

  D3DXVECTOR3 velocity_;
};
