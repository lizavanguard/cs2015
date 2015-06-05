//==============================================================================
//
// Scene Base [Scene.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_SCENE_H__
#define __H_SCENE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneManager;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Scene {
public:
  // dtor
  virtual ~Scene() {}

  // method
  virtual void Update(SceneManager* pSceneManager, float elapsedTime) = 0;
  virtual void Draw(void) = 0;
};


#endif // __H_SCENE_H__