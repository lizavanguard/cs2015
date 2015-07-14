//==============================================================================
//
// EffectManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <deque>

#include "Framework/Utility/SingletonHolder.hpp"

#include "Effect.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class EffectManager {
public:
  // enum
  enum EffectType {
    EFFECTTYPE_KIRAKIRA,
    kEffectTypeMax
  };

  // ctor
  EffectManager();

  // dtor
  ~EffectManager();

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  // Create
  void Create(EffectType effect_type, const D3DXVECTOR2& position, const D3DXVECTOR2& velocity, float scale);

private:
  void _Foreach(void(*function)(Effect*));
  Effect* _SearchDeadEffect(void);

  typedef std::deque<Effect*> EffectList;
  EffectList effect_list_;
  int texture_data_[kEffectTypeMax];
};

typedef liza::generic::SingletonHolder<EffectManager> EffecManagerSingleton;
