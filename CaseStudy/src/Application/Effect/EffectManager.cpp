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
    effect_list_.push_back(Effect());
  }

  for (int i = 0; i < kEffectTypeMax; ++i) {
    texture_data_[i] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(kEffectData[i].p_texture_filename);
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
EffectManager::~EffectManager() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void EffectManager::Update(void) {
  _Foreach([](Effect& effect) {
    effect.Update();
  });
}

//------------------------------------------------
// Draw
//------------------------------------------------
void EffectManager::Draw(void) {
  _Foreach([](Effect& effect) {
    effect.Draw();
  });
}

//------------------------------------------------
// Create a effect
//------------------------------------------------
void EffectManager::Create(const EffectType effect_type, const D3DXVECTOR2& position, const D3DXVECTOR2& velocity, const float scale) {
  assert(0 <= effect_type && effect_type < kEffectTypeMax);

  Effect& effect = _SearchDeadEffect();
  effect.SetParameter(D3DXVECTOR3(position.x, position.y, 0.0f),
                      D3DXVECTOR3(velocity.x, velocity.y, 0.0f),
                      kEffectData[effect_type].size * scale,
                      kEffectData[effect_type].lifetime,
                      texture_data_[effect_type]);
}

//------------------------------------------------
// Internal Foreach
//------------------------------------------------
void EffectManager::_Foreach(void(*function)(Effect&)) {
  std::for_each(effect_list_.begin(), effect_list_.end(), function);
}

//------------------------------------------------
// Search a dead effect.
// return not used effect id.
//------------------------------------------------
Effect& EffectManager::_SearchDeadEffect(void) {
  for (auto& effect : effect_list_) {
    if (!effect.IsAlive()) {
      return effect;
    }
  }

  effect_list_.push_back(Effect());
  return effect_list_.back();
}
