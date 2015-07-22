//==============================================================================
//
// SceneStageSelect
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneStageSelect.h"

#include "Framework/FrameworkOption.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputXInput.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Sound/sound.h"

#include "Application/Game/SceneGameFactory.h"
#include "Application/Game/SceneGame.h"
#include "Application/Tutorial/SceneTutorialFactory.h"
#include "Application/GameCursor/GameCursor.h"
#include "Application/Object/BackGround/BackGroundManager.h"
#include "Application/Object/Object2D/Object2D.h"
#include "Application/Thumbnail/Thumbnail.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const int kNumTop = 3;
const int kNumBottom = 2;
const int kNumThumb = 5;

const D3DXVECTOR3 kCenterPosition = {kWindowWidth * 0.5f, 450.0f, 0.0f};
const D3DXVECTOR2 kSize = {200.0f, 200.0f};
const D3DXVECTOR2 kMargin = {75.0f, 50.0f};
const D3DXVECTOR2 kStride = kSize + kMargin;

// Ç‡Ç¡Ç∆àÍî âªÇµÇƒÇ‡Ç¢Ç¢Ç™ÅAÉÅÉìÉhÉC
const D3DXVECTOR3 kTopStartPosition = {
  kCenterPosition.x - kStride.x,
  kCenterPosition.y - (kStride.y * 0.5f),
  kCenterPosition.z
};
const D3DXVECTOR3 kBottomStartPosition = {
  kCenterPosition.x - (kStride.x * 0.5f),
  kCenterPosition.y + (kStride.y * 0.5f),
  kCenterPosition.z
};
const char* kTextureFilename = "data/Texture/tex_anim_04.png";

const D3DXVECTOR3 kNameCenterPosition = {kWindowWidth * 0.5f, 150.0f, 0.0f};
const D3DXVECTOR2 kNameSize = {400.0f, 100.0f};
const char* kNameTextureFilename = "data/Texture/tex_anim_04.png";

const D3DXVECTOR2 kCursorSize = {100.0f, 100.0f};
const D3DXVECTOR3 kCursorOffset = {90.0f, 90.0f, 0.0f};

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneStageSelect::SceneStageSelect()
    : p_background_manager_(nullptr)
    , p_cursor_(nullptr)
    , p_name_(nullptr) {
  for (int top_count = 0; top_count < kNumTop; ++top_count) {
    D3DXVECTOR3 position = kTopStartPosition;
    position.x += kStride.x * top_count;
    p_thumbnails_[top_count] = new Thumbnail(position, kSize, kTextureFilename);
  }
  for (int bottom_count = 0; bottom_count < kNumBottom; ++bottom_count) {
    D3DXVECTOR3 position = kBottomStartPosition;
    position.x += kStride.x * bottom_count;
    p_thumbnails_[kNumTop + bottom_count] = new Thumbnail(position, kSize, kTextureFilename);
  }

  p_name_ = new Object2D(kNameCenterPosition, kNameSize, kNameTextureFilename);

  p_background_manager_ = new BackGroundManager();

  GameCursor::PositionContainer position_list;
  for (int thumb_count = 0; thumb_count < kNumThumb; ++thumb_count) {
    position_list.push_back(p_thumbnails_[thumb_count]->GetPosition() + kCursorOffset);
  }
  p_cursor_ = new GameCursor(kCursorSize, DIK_RIGHT, DIK_LEFT, DIK_RETURN, DIK_BACKSPACE, position_list);

  // TODO:
  p_thumbnails_[0]->Activate();

  PlaySound(SOUND_LABEL_BGM_STAGESELECT);
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneStageSelect::~SceneStageSelect() {
  StopSound(SOUND_LABEL_BGM_STAGESELECT);

  SafeDelete(p_cursor_);

  SafeDelete(p_background_manager_);

  SafeDelete(p_name_);

  for (auto p_thumb : p_thumbnails_) {
    SafeDelete(p_thumb);
  }
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneStageSelect::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  p_background_manager_->Update();

  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  if (pJoypad.IsTrigger(InputDevice::Pads::PAD_A) || pKeyboard.IsTrigger(DIK_RETURN)) {
    int select_num = p_cursor_->GetCursorIndexOld();
    if (select_num == 0){
      p_scene_manager->PushNextSceneFactory(new SceneTutorialFactory());
    } else {
      SceneGame::SetSelectStageNum(select_num);
      p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
    }
  }

  p_cursor_->Update(elapsed_time);

  if (p_cursor_->IsJustMoved()) {
    const int cursor_index = p_cursor_->GetCursorIndex();
    p_thumbnails_[p_cursor_->GetCursorIndexOld()]->Deactivate();
    p_thumbnails_[p_cursor_->GetCursorIndex()]->Activate();
  }
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneStageSelect::Draw(void) {
  p_background_manager_->Draw();

  for (auto p_thumb : p_thumbnails_) {
    p_thumb->Draw();
  }

  p_cursor_->Draw();

  p_name_->Draw();
}
