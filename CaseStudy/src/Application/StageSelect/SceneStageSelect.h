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

#include "Application/Utility/Cursor.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class BackGroundManager;
class Object2D;

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

  BackGroundManager* p_background_manager_;
  Object2D* p_cursor_;
  Cursor<kStageMax>* p_cursor_value_;
  std::array<Object2D*, kStageMax> p_thumbnails_;
  Object2D* p_name_;
};
