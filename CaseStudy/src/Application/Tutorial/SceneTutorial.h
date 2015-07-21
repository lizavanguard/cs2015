//==============================================================================
//
// SceneTutorial [SceneTutorial.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#pragma warning( disable : 4481 )
#ifndef __H_SCENETUTORIAL_H__
#define __H_SCENETUTORIAL_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Scene/Scene.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Collision;
class Uriel;
class Player;
class Stage;
class Tori;
class TensionGauge;
class Camera;
class TutorialEvent;
class TutorialBackGround;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneTutorial : public Scene {
public:
  // ctor/dtor
  SceneTutorial();
  virtual ~SceneTutorial();

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
  Collision* p_collision_;
  Player* p_player_;
  Stage* p_stage_;
  TensionGauge* p_tension_gauge_;
  Tori* p_tori_;
  Uriel* p_uriel_;
  Camera* p_camera;
  TutorialEvent* p_tutorial_event_;
  TutorialBackGround* p_tutorial_backGround_;
};


#endif // __H_SCENEGAME_H__
