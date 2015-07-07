//==============================================================================
//
// SceneStageSelect
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Scene/Scene.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneStageSelect : public Scene {
public:
  // ctor
  SceneStageSelect();

  // dtor
  virtual ~SceneStageSelect();

  // Update
  void Update(SceneManager* pSceneManager, float elapsedTime) override;

  // Draw
  void Draw(void);

private:
};
