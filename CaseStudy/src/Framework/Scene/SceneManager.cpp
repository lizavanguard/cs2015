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
  // 更新より前に置くことによって1ループ終わってから(今回のフレームの描画が終わってから)
  // シーンの切り替えを行うことになる
  // if 次のシーンファクトリが存在していたら
  if (pNextSceneFactory_ != nullptr) {
    // 現在のシーンを削除
    SafeDelete(pCurScene_);

    // 次のシーンを生成し、付け変える
    pCurScene_ = pNextSceneFactory_->Create();

    // シーンファクトリの削除
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