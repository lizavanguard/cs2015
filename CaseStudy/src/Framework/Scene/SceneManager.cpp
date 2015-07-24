//==============================================================================
//
// SceneManager [SceneManager.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SceneManager.h"
#include "Scene.h"
#include "SceneFactory.h"

#include "Framework/Fade/Fade.h"

#include "Framework/Utility/Utility.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneManager::SceneManager(Scene* pFirstScene) : pCurScene_(pFirstScene)
    , pNextSceneFactory_(nullptr)
    ,scene_change_flag_(false)
    , fade_false_count_(0)
{
}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneManager::~SceneManager() {
  SafeDelete(pNextSceneFactory_);
  SafeDelete(pCurScene_);
}


//------------------------------------------------
// Update
//------------------------------------------------
void SceneManager::Update(const float elapsedTime) {
  // �X�V���O�ɒu�����Ƃɂ����1���[�v�I����Ă���(����̃t���[���̕`�悪�I����Ă���)
  // �V�[���̐؂�ւ����s�����ƂɂȂ�
  _ChangeScene();

  if (!scene_change_flag_){
    pCurScene_->Update(this, elapsedTime);
  }
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneManager::Draw(void) {
  pCurScene_->Draw();
}


//------------------------------------------------
// Push Next Scene
//------------------------------------------------
void SceneManager::PushNextSceneFactory(SceneFactory* pNextSceneFactory) {
  pNextSceneFactory_ = pNextSceneFactory;
  SetFade(FADE_OUT);
  scene_change_flag_ = true;
  fade_false_count_ = 0;
}

//------------------------------------------------
// Change scene
//------------------------------------------------
void SceneManager::_ChangeScene(void) {
  static bool isFadeOut = true;

  if (!isFadeOut) {
    // �t�F�[�h���J�n
    bool finished = UpdateFade();
    // if �t�F�[�h���Ȃ�I��
    if (!finished) {
      return;
    }

    isFadeOut = true;
    return;
  }

  // if ���̃V�[���t�@�N�g�������݂��Ă�����
  if (pNextSceneFactory_ != nullptr) {
    // �t�F�[�h���J�n
    bool finished = UpdateFade();

    // �t�F�[�h�������̂ŋ����I�ɏI��
    if (fade_false_count_ >= kFadeWaitTime * 60){
      finished = true;
    }

    // if �t�F�[�h���Ȃ�I��
    if (!finished) {
      ++fade_false_count_;
      return;
    }

    // else �t�F�[�h���I�����Ă�����
    // ���݂̃V�[�����폜
    SafeDelete(pCurScene_);

    // ���̃V�[���𐶐����A�t���ς���
    pCurScene_ = pNextSceneFactory_->Create();

    // �t�F�[�h�C���J�n
    SetFade(FADE_IN);

    // �V�[���t�@�N�g���̍폜
    SafeDelete(pNextSceneFactory_);

    isFadeOut = false;
    scene_change_flag_ = false;
    return;
  }
}