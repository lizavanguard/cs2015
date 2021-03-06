//==============================================================================
//
// SceneManager [SceneManager.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_SCENEMANAGER_H__
#define __H_SCENEMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Scene;
class SceneFactory;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneManager {
public:
  // ctor/dtor
  SceneManager(Scene* pFirstScene);
  ~SceneManager();

  // method
  void Update(float elapsedTime);
  void Draw(void);

  void PushNextSceneFactory(SceneFactory* pNextSceneFactory);

private:
  // property
  Scene* pCurScene_;
  SceneFactory* pNextSceneFactory_;
};


#endif // __H_SCENEMANAGER_H__