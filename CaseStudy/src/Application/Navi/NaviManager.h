//==============================================================================
//
// 障害物管理クラス [NaviManager.h]
// Author : Tomoki Ohashi
//
//==============================================================================
#pragma once
#ifndef __H_NAVIMANAGER_H__
#define __H_NAVIMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Application/Object/AnimationObject/AnimationObject.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
enum
{
  NAVI_UP = 0,
  NAVI_BOTTOM,
  NAVI_RIGHT,
  NAVI_LEFT,
  NAVI_MAX,
};
class Camera;
class Uriel;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class NaviGation;
class NaviManager{
public:
  // ctor
  NaviManager(Camera& camera,Uriel& uriel);

  // dtor
  virtual ~NaviManager();

  // update
  void Update(void);

  // draw
  void Draw(void);

private:
  void dir_init();
  void dir_update();
  NaviGation* p_navigation_[NAVI_MAX];
  Camera& camera_;
  Uriel& uriel_;
  bool b_dir[NAVI_MAX];
};


#endif // __H_NAVIMANAGER_H__
//