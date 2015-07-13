//==============================================================================
//
// TutorialEvent[TutorialEvent.cpp]
// Author: Yuji Momoi
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Tutorial/TutorialEvent.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Application/Object/Uriel.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputXInput.h"
#include "Application/Object/player.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTexturenames[] = {
  "data/Texture/ready_sign_00.png",
  "data/Texture/ready_sign_01.png",
  "data/Texture/ready_sign_00.png",
  "data/Texture/ready_sign_01.png"
};

const D3DXVECTOR3 event_point[] = {
  D3DXVECTOR3(-600, -150, 0),
  D3DXVECTOR3(-800, -150, 0),
  D3DXVECTOR3(-600, -150, 0),
  D3DXVECTOR3(-200, -150, 0),
};

const D3DXVECTOR3 kInitialPos = {640.0f, 360.0f, 0.0f};
const D3DXVECTOR2 kSize = {640.0f, 360.0f};

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
TutorialEvent::TutorialEvent(Uriel* p_uriel, Player* p_player)
    : Object2D(kInitialPos, kSize, nullptr)
    , is_end_(false)
    , p_uriel_(nullptr)
    , view_event_flag_(false)
    , event_number_(EVENT_NAME_NONE)
    , p_player_(nullptr) {
  for (int texture_count = 0; texture_count < kTutorialEventMax; ++texture_count) {
    texture_ids_[texture_count] =
      TextureManagerHolder::Instance().GetTextureManager().LoadTexture(kTexturenames[texture_count]);
    event_view_flag_[texture_count] = false;
    already_used_flag_[texture_count] = false;
  }
  texture_id_ = texture_ids_[0];
  p_uriel_ = p_uriel;
  p_player_ = p_player;
}

//------------------------------------------------
// dtor
//------------------------------------------------
TutorialEvent::~TutorialEvent() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void TutorialEvent::Update(void) {
  view_event_flag_ = true;

  // チュートリアルイベントを表示するか調べる
  if (!TutorialEventCheck()){
    view_event_flag_ = false;
    return;
  }

  p_uriel_->SetMoveStop(true);
  EventUpdate();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void TutorialEvent::_PreProcessOfDraw(void) {
}

void TutorialEvent::_PostProcessOfDraw(void) {
}

//------------------------------------------------
// チュートリアルイベントを表示するべきか調べる
//------------------------------------------------
bool TutorialEvent::TutorialEventCheck(void){
  D3DXVECTOR3 uriel_pos = p_uriel_->GetPos();

  for (int i = 0; i < kTutorialEventMax; ++i){
    if (use_flag_[i]){
      return true;
    }
    if (already_used_flag_[i] == false){
      if (abs(uriel_pos.x - event_point[i].x) < kTutorialEventHitSize &&
          abs(uriel_pos.y - event_point[i].y) < kTutorialEventHitSize){
        if (i == EVENT_NAME_JUNP){
          if (already_used_flag_[EVENT_NAME_CALL]){
            use_flag_[i] = true;
            event_number_ = i;
          } else {
            return false;
          }
        } else {
          use_flag_[i] = true;
          event_number_ = i;
        }
        texture_id_ = texture_ids_[i];
        return true;
      }
    }
  }
  return false;
}

//------------------------------------------------
// イベントごとの判定更新
//------------------------------------------------
void TutorialEvent::EventUpdate(void){
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  switch (event_number_)
  {
  case EVENT_NAME_START:
    {
      if (pJoypad.IsTrigger(InputDevice::Pads::PAD_A) || pKeyboard.IsPress(DIK_RETURN)){
        use_flag_[EVENT_NAME_START] = false;
        already_used_flag_[EVENT_NAME_START] = true;
      }
      p_player_->SetMoveStop(true);
    }
    break;
  case EVENT_NAME_CALL:
    {
      if (pJoypad.IsPress(InputDevice::Pads::PAD_A) || pKeyboard.IsPress(DIK_RETURN)){
        use_flag_[EVENT_NAME_CALL] = false;
        already_used_flag_[EVENT_NAME_CALL] = true;
      }
      p_player_->SetMoveStop(true);
    }
    break;
  case EVENT_NAME_JUNP:
    {
      if (pJoypad.IsTrigger(InputDevice::Pads::PAD_A) || pKeyboard.IsPress(DIK_RETURN)){
        use_flag_[EVENT_NAME_JUNP] = false;
        already_used_flag_[EVENT_NAME_JUNP] = true;
      }
    p_player_->SetMoveStop(true);
    }
    break;
  case EVENT_NAME_CHARGE_JUNP:
    {
      if (!p_uriel_->CheckBoro()){
        use_flag_[EVENT_NAME_CHARGE_JUNP] = false;
        already_used_flag_[EVENT_NAME_CHARGE_JUNP] = true;
      }
    }
    break;
  default:
    break;
  }
}
