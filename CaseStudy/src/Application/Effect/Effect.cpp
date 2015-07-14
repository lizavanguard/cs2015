///==============================================================================
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
    : AnimationObject(ANIMATION_NONE)
    , count_(0)
    , lifetime_(0)
    , velocity_(0.0f, 0.0f, 0.0f) {
  pos_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  size_ = kDefaultSize;

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
    const ANIMATION_EVENT animation_event,
    const float scale) {
  assert(scale > 0.0f);

  pos_ = position;
  velocity_ = velocity;
  size_ = kDefaultSize * scale;
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
  lifetime_ = p_texture_animation_->GetAnimationTime();
  count_ = 0;
  is_alive_ = true;
}
