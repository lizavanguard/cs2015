//==============================================================================
//
// Effect
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Effect.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const D3DXVECTOR2 kDefaultSize = {128.0f, 128.0f};

}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Effect::Effect()
    : Object2D(D3DXVECTOR3(0.0f, 0.0f, 0.0f), kDefaultSize, nullptr)
    , count_(0)
    , lifetime_(0)
    , velocity_(0.0f, 0.0f, 0.0f) {
  is_alive_ = false;
}

//------------------------------------------------
// dtor
//------------------------------------------------
Effect::~Effect() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Effect::Update(void) {
  if (!is_alive_) {
    return;
  }

  pos_ += velocity_;


  if (count_ == lifetime_) {
    is_alive_ = false;
  }
  ++count_;
}

//------------------------------------------------
// Set parameter
//------------------------------------------------
void Effect::SetParameter(
    const D3DXVECTOR3& position,
    const D3DXVECTOR3& velocity,
    const float size,
    const unsigned int lifetime,
    const int texture_id) {
  assert(lifetime != 0);
  assert(size >= 0.0f);
  assert(texture_id >= 0);

  pos_ = position;
  velocity_ = velocity;
  size_ = D3DXVECTOR2(size, size);
  lifetime_ = lifetime;
  count_ = 0;
  texture_id_ = texture_id;
  is_alive_ = true;
}

