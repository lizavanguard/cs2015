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
#include "Framework/Texture/TextureManagerHolder.h"
#include "AnimationObject\TextureAnimation.h"
#include "Uriel.h"
#include "player.h"

//******************************************************************************
// 定数定義
//******************************************************************************
namespace {

const float kPlayerMoveSpeed = 10.0f;
const int kBoroRecastTime = 60;

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
Player::Player(ANIMATION_EVENT animation_event)
  : AnimationObject(animation_event)
  , player_mode_(MODE_NORMAL)
  , count_(0)
  , is_eat_(false) {
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
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  // 移動
  if (pKeyboard.IsPress(DIK_W)) {
    pos_.y += kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_S)) {
    pos_.y -= kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_A)) {
    pos_.x -= kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_D)) {
    pos_.x += kPlayerMoveSpeed;
  }

  if (pKeyboard.IsPress(DIK_9)) {
	  //uriel_->SetAnimaton(ANIMATION_URIEL_RUNAWAY);
	  uriel_->BoroChage();
  }

  // ガラガラモード切替
  // 誘導
  if (pKeyboard.IsPress(DIK_RETURN)){
    ChangeAnimation(MODE_GUIDE);
    PlaySound(SOUND_LABEL_SE_CALL0);
  }
  else if (pKeyboard.IsRelease(DIK_RETURN)){
    ChangeAnimation(MODE_NORMAL);
  }
  // ギミックON/OFF
  if (pKeyboard.IsTrigger(DIK_G)){
    ChangeAnimation(MODE_GIMMICK);
    PlaySound(SOUND_LABEL_SE_CALL1);
  }

  // ボーロ
  if (pKeyboard.IsTrigger(DIK_B)) {
    // ウリエルちゃんが食べていなかったら ボーロが出る
    if (!is_eat_) {
      ChangeAnimation(MODE_BORO);
      PlaySound(SOUND_LABEL_SE_EAT);
    }
  }
  else if (pKeyboard.IsRelease(DIK_B)) {
    ChangeAnimation(MODE_NORMAL);
  }


  // モード
  switch (player_mode_) {
    case MODE_NORMAL: // 通常時
      break;
    case MODE_BORO: // ボーロ
      // if ウリエルちゃんがボーロ食べたら 通常状態に戻す
      // if (uriel->BoroCharge()) {
      if (pKeyboard.IsTrigger(DIK_N)) {
         ChangeAnimation(MODE_NORMAL);
         is_eat_ = true;
       }

      break;
    case MODE_GUIDE: // 誘導
      // ウリエルちゃん移動
      uriel_->SetDestPos(pos_);
      // 誘導モードが一定時間以上
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

// EOF