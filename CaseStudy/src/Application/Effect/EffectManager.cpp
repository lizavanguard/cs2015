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
  const char* p_texture_filename;
  unsigned int lifetime;
  float size;
};

}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const int kEffectDefaultMax = 2000;

const _EffectData kEffectData[EffectManager::kEffectTypeMax] = {
  {"data/texture/tex_anim_sample.png", 60, 128.0f},
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

  for (int i = 0; i < kEffectTypeMax; ++i) {
    texture_data_[i] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(kEffectData[i].p_texture_filename);
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
    128,//kEffectData[effect_type].size * scale,
    1000,//kEffectData[effect_type].lifetime,
    0);
       //                 texture_data_[effect_type]);
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
