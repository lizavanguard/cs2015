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

#include "Effect.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class EffectManager {
public:
  // ctor
  EffectManager();

  // dtor
  ~EffectManager();

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  // Create
  void Create(void);

private:
  void _Foreach(void(*function)(Effect&));

  typedef std::deque<Effect> EffectList;

  EffectList effect_list_;
};
