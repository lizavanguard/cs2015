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
class Collision;
class Uriel;
class Player;
class Ready;
class Stage;
class Tori;
class TensionGauge;
class Timer;
class Camera;
class SangManager;

class GamePause;
class NaviManager;
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
  static void SetSelectStageNum(int select_stage_num){ select_stage_num_ = select_stage_num; }

  // get
  bool IsPause(void) const;

private:
  // property
  bool is_end_;
  BackGroundManager* p_background_manager_;
  Collision* p_collision_;
  Player* p_player_;
  Ready* p_ready_;
  Stage* p_stage_;
  TensionGauge* p_tension_gauge_;
  Tori* p_tori_;
  Uriel* p_uriel_;
  Timer* p_timer_;
  Camera* p_camera;
  SangManager* p_sang_manager_;
  Camera* p_camera_;
  GamePause* p_game_pause_;
  NaviManager* p_navimanager_;
  static int select_stage_num_;
};


#endif // __H_SCENEGAME_H__
