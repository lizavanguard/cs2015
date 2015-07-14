//==============================================================================
//
// EffectManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "EffectManager.h"

#include <algorithm>

#include "Framework/Texture/TextureManagerHolder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// struct
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

struct _EffectData {
  ANIMATION_EVENT animation_event;
};

}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const int kEffectDefaultMax = 2000;

const _EffectData kEffectData[EffectManager::kEffectTypeMax] = {
  ANIMATION_PLAYER_RATTEL_SHAKE,
};

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
EffectManager::EffectManager() {
  for (int i = 0; i < kEffectDefaultMax; ++i) {
    effect_list_.push_back(new Effect());
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
EffectManager::~EffectManager() {
  _Foreach([](Effect* p_effect) {
    SafeDelete(p_effect);
  });
}

//------------------------------------------------
// Update
//------------------------------------------------
void EffectManager::Update(void) {
  _Foreach([](Effect* p_effect) {
    p_effect->Update();
  });
}

//------------------------------------------------
// Draw
//------------------------------------------------
void EffectManager::Draw(void) {
  _Foreach([](Effect* p_effect) {
    p_effect->Draw();
  });
}

//------------------------------------------------
// Create a effect
//------------------------------------------------
void EffectManager::Create(const EffectType effect_type, const D3DXVECTOR2& position, const D3DXVECTOR2& velocity, const float scale) {
  assert(0 <= effect_type && effect_type < kEffectTypeMax);

  Effect* p_effect = _SearchDeadEffect();
  p_effect->SetParameter(D3DXVECTOR3(position.x, position.y, 0.0f),
                         D3DXVECTOR3(velocity.x, velocity.y, 0.0f),
                         kEffectData[effect_type].animation_event,
                         scale);
}

//------------------------------------------------
// Internal Foreach
//------------------------------------------------
void EffectManager::_Foreach(void(*function)(Effect*)) {
  std::for_each(effect_list_.begin(), effect_list_.end(), function);
}

//------------------------------------------------
// Search a dead effect.
// return not used effect id.
//------------------------------------------------
Effect* EffectManager::_SearchDeadEffect(void) {
  for (auto p_effect : effect_list_) {
    if (!p_effect->IsAlive()) {
      return p_effect;
    }
  }

  effect_list_.push_back(new Effect());
  return effect_list_.back();
}
