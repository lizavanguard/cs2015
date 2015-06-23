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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class BackGroundManager;
class Uriel;
class Player;
class Ready;
class Stage;
class Tori;
class TensionGauge;

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
  BackGroundManager* p_background_manager_;
  Player* p_player_;
  Ready* p_ready_;
  Stage* p_stage_;
  TensionGauge* p_tension_gauge_;
  Tori* p_tori_;
  Uriel* p_uriel_;
};


#endif // __H_SCENEGAME_H__
