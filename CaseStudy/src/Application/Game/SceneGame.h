//==============================================================================
//
// SceneGame [SceneGame.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#pragma warning( disable : 4481 )
#ifndef __H_SCENEGAME_H__
#define __H_SCENEGAME_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Scene/Scene.h"

// HACK:
#include "Application/Object/Object.h"
#include "Application/Object/Uriel.h"
#include "Application/Object/Tori.h"
#include "Application/Stage/Stage.h"
#include "Application/Object/player.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneGame : public Scene {
public:
  // ctor/dtor
  SceneGame();
  virtual ~SceneGame();

  // method
  void Update(SceneManager* pSceneManager, float elapsedTime) override;
  void Draw(void) override;

  // set
  void End(void) { is_end_ = true; }

  // get
  bool IsPause(void) const;

private:
  // property
  bool is_end_;
  Object* p_object_;
  Object* p_back_;
  Uriel* p_uriel_;
  Tori* p_tori_;
  Stage* p_stage_;
  Player* p_player;
  bool start_event_;
  int start_event_timer_;
};


#endif // __H_SCENEGAME_H__
