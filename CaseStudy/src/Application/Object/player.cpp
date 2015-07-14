//******************************************************************************
//
// プレイヤー処理  [plyaer.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Sound/sound.h"
#include "Framework\FrameworkOption.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/Input/InputXInput.h"
#include "AnimationObject\TextureAnimation.h"
#include "Application\Stage\Stage.h"
#include "Application\Camera\camera.h"
#include "player.h"

//******************************************************************************
// 定数定義
//******************************************************************************
namespace {

const float kPlayerMoveSpeed = 10.0f;
const int kBoroRecastTime = 30;
const int kGuideTriggerTime = 15;

const D3DXVECTOR3 kBoroPosOffset = {
  -20.0f, 93.0f, 0.0f
};

}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  ANIMATION_EVENT animation_event
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//==============================================================================
Player::Player(ANIMATION_EVENT animation_event , Stage* stage)
  : AnimationObject(animation_event)
  , player_mode_(MODE_NORMAL)
  , count_(0)
  , is_eat_(false)
  , is_gimmick_(false) 
  , move_stop_flag_(false){
    stage_ = stage;
    stageSize_ = stage_->GetStageSize();
    pos_ = stage_->GetStartMaptip();
    pos_.y += 50.0f;
}

//==============================================================================
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//==============================================================================
Player::~Player(void){
}

//==============================================================================
// 更新処理
// 引数    :  Uriel *uriel_
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//==============================================================================
void Player::Update(Uriel *uriel_){
  if (!move_stop_flag_){
    auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
    auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
    // 移動
    if (!is_gimmick_)
    {
      if (pJoypad.IsPress(InputDevice::Pads::PAD_LTHUMB_UP) || pKeyboard.IsPress(DIK_W)) {
        pos_.y += kPlayerMoveSpeed;
        if (pos_.y + size_.y * 0.5f > stageSize_.y / 2.0f){
          pos_.y = stageSize_.y / 2.0f - size_.y * 0.5f;
        }
      }
      if (pJoypad.IsPress(InputDevice::Pads::PAD_LTHUMB_RIGHT) || pKeyboard.IsPress(DIK_D)) {
        pos_.x += kPlayerMoveSpeed;
        if (pos_.x + size_.x * 0.5f > stageSize_.x / 2.0f){
          pos_.x = stageSize_.x / 2.0f - size_.x * 0.5f;
        }
      }
      if (pJoypad.IsPress(InputDevice::Pads::PAD_LTHUMB_DOWN) || pKeyboard.IsPress(DIK_S)) {
        pos_.y -= kPlayerMoveSpeed;
        if (pos_.y - size_.y * 0.5f < -stageSize_.y / 2.0f){
          pos_.y = -stageSize_.y / 2.0f + size_.y * 0.5f;
        }
      }
      if (pJoypad.IsPress(InputDevice::Pads::PAD_LTHUMB_LEFT) || pKeyboard.IsPress(DIK_A)) {
        pos_.x -= kPlayerMoveSpeed;
        if (pos_.x - size_.x * 0.5f < -stageSize_.x / 2.0f){
          pos_.x = -stageSize_.x / 2.0f + size_.x * 0.5f;
        }
      }
    }

    if (pKeyboard.IsPress(DIK_9)) {
      //uriel_->SetAnimaton(ANIMATION_URIEL_RUNAWAY);
      uriel_->BoroChage();
    }

    // ガラガラモード切替
    // 誘導
    static bool is_press = false;
    if (pJoypad.IsTrigger(InputDevice::Pads::PAD_A) || pKeyboard.IsTrigger(DIK_RETURN)) {
      ChangeAnimation(MODE_GUIDE);
      is_press = true;
    }
    else if (pJoypad.IsRelease(InputDevice::Pads::PAD_A) || pKeyboard.IsRelease(DIK_RETURN)) {
      is_press = false;
      ChangeAnimation(MODE_NORMAL);
    }
    // ギミックON/OFF
    if (pJoypad.IsTrigger(InputDevice::Pads::PAD_Y) || pKeyboard.IsTrigger(DIK_G)) {
      ChangeAnimation(MODE_GIMMICK);
      PlaySound(SOUND_LABEL_SE_CALL1);
      is_gimmick_ = true;
    }
    else if (pJoypad.IsRelease(InputDevice::Pads::PAD_Y) || pKeyboard.IsRelease(DIK_G)) {
      is_gimmick_ = false;
    }

    // ボーロ
    if (!is_eat_) {
      if (pJoypad.IsTrigger(InputDevice::Pads::PAD_X) || pKeyboard.IsTrigger(DIK_B)) {
        ChangeAnimation(MODE_BORO);
      }
      else if (pJoypad.IsRelease(InputDevice::Pads::PAD_X) || pKeyboard.IsRelease(DIK_B)){
        ChangeAnimation(MODE_NORMAL);
      }
    }

    // モード
    switch (player_mode_) {
    case MODE_NORMAL: // 通常時
      break;
    case MODE_BORO: // ボーロ
      break;
    case MODE_GUIDE: // 誘導
      // 誘導モードが一定時間以上
      if ((count_ % p_texture_animation_->GetAnimationTime()) == kGuideTriggerTime) {
        uriel_->SetDestPos(pos_);
      }
      break;
    case MODE_GIMMICK: // ギミック
      // if ギミックのアニメーションが終了したら 通常モードに戻す
      if (count_ >= /*p_texture_animation_->GetAnimationTime()*/ 60) {
        ChangeAnimation(MODE_NORMAL);
      }
      break;
    }

    // アニメーション更新
    p_texture_animation_->UpdateAnimation();

    // ボーロが食べられていたら 一定時間経過で元に戻す
    if (is_eat_ && count_ > kBoroRecastTime) {
      is_eat_ = false;
    }

    ++count_;
  }

  move_stop_flag_ = false;
}

//==============================================================================
// ボーロの位置を返す
// 引数    :  無し
// 戻り値  :  const D3DXVECTOR3
// Author  :  SHOJI SHIMIZU
// 更新日  :  2015/06/29
//==============================================================================
const D3DXVECTOR3 Player::GetBoroPos(void) const {
  return pos_ + kBoroPosOffset;
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//==============================================================================
void Player::_PreProcessOfDraw(void){
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
      texture_uv_.x += texture_uv_offset_.x;
      texture_uv_offset_.x *= -1;
  }

  start_uv_ = texture_uv_;
  end_uv_ = texture_uv_ + texture_uv_offset_;
}

//==============================================================================
// アニメーションセット処理
// 引数    :  PLAYER_MODE mode_
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/29
//==============================================================================
void Player::ChangeAnimation(PLAYER_MODE mode){
  // if プレイヤーモードが一致していなかったら アニメーションの変更
  if (player_mode_ != mode){
    switch (mode){
    case MODE_NORMAL:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_NONE);
      break;
    case MODE_BORO:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_BORO);
      break;
    case MODE_GUIDE:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
      break;
    case MODE_GIMMICK:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_GIMMICK);
      break;
    }
    player_mode_ = mode;
  }

  // カウントリセット
  count_ = 0;
}

//==============================================================================
// ボーロ状態の終了
// 引数    :  void
// 戻り値  :  無し
// Author  :  SHOJI SHIMIZU
// 更新日  :  2015/06/22
//==============================================================================
void Player::FinishBoroState(void) {
  ChangeAnimation(MODE_NORMAL);
  is_eat_ = true;
}


// EOF