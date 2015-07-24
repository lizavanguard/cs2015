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
  // 更新より前に置くことによって1ループ終わってから(今回のフレームの描画が終わってから)
  // シーンの切り替えを行うことになる
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
    // フェードを開始
    bool finished = UpdateFade();
    // if フェード中なら終了
    if (!finished) {
      return;
    }

    isFadeOut = true;
    return;
  }

  // if 次のシーンファクトリが存在していたら
  if (pNextSceneFactory_ != nullptr) {
    // フェードを開始
    bool finished = UpdateFade();

    // フェードが長いので強制的に終了
    if (fade_false_count_ >= kFadeWaitTime * 60){
      finished = true;
    }

    // if フェード中なら終了
    if (!finished) {
      ++fade_false_count_;
      return;
    }

    // else フェードが終了していたら
    // 現在のシーンを削除
    SafeDelete(pCurScene_);

    // 次のシーンを生成し、付け変える
    pCurScene_ = pNextSceneFactory_->Create();

    // フェードイン開始
    SetFade(FADE_IN);

    // シーンファクトリの削除
    SafeDelete(pNextSceneFactory_);

    isFadeOut = false;
    scene_change_flag_ = false;
    return;
  }
}