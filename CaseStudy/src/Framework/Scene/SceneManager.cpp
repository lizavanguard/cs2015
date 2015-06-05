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

#include "Framework/Utility/Utility.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneManager::SceneManager(Scene* pFirstScene) : pCurScene_(pFirstScene), pNextSceneFactory_(nullptr) {
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
  // if ���̃V�[���t�@�N�g�������݂��Ă�����
  if (pNextSceneFactory_ != nullptr) {
    // ���݂̃V�[�����폜
    SafeDelete(pCurScene_);

    // ���̃V�[���𐶐����A�t���ς���
    pCurScene_ = pNextSceneFactory_->Create();

    // �V�[���t�@�N�g���̍폜
    SafeDelete(pNextSceneFactory_);
  }

  pCurScene_->Update(this, elapsedTime);
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
}