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
  void _ChangeScene(void);

  static const int kFadeWaitTime = 2; // �t�F�[�h�̍ő�҂�����(���ꂾ���҂��ăt�F�[�h���I�����Ȃ��Ȃ狭���I�Ɏ��̃V�[���ɂ���)

  // property
  Scene* pCurScene_;
  SceneFactory* pNextSceneFactory_;
  bool scene_change_flag_;
  int fade_false_count_;
};


#endif // __H_SCENEMANAGER_H__