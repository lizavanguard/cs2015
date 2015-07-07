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

#include <array>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2D;
class BackGroundManager;

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
  static const int kStageMax = 5;

  std::array<Object2D*, kStageMax> p_thumbnails_;
  Object2D* p_name_;
  BackGroundManager* p_background_manager_;
};
