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
#include "Framework/Texture/TextureManagerHolder.h"
#include "AnimationObject\TextureAnimation.h"
#include "Uriel.h"
#include "player.h"

//******************************************************************************
// マクロ定義
//******************************************************************************


//******************************************************************************
// プロトタイプ宣言
//******************************************************************************


//******************************************************************************
// メンバ変数:
//******************************************************************************


//******************************************************************************
// グローバル変数:
//******************************************************************************


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
Player::Player(ANIMATION_EVENT animation_event) :AnimationObject(animation_event){
  player_mode_ = MODE_NONE;
  action_flag_ = false;
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
      AddPosY(PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_S)) {
      AddPosY(-PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_A)) {
      AddPosX(-PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_D)) {
      AddPosX(PLAYER_MOVE_SPEED);
  }
  // ガラガラモード切替
  // ・誘導
  if (pKeyboard.IsPress(DIK_RETURN)){
      SetAnimation(MODE_GUIDE);
      action_flag_ = true;
  }
  else if (pKeyboard.IsRelease(DIK_RETURN)){
      SetAnimation(MODE_NONE);
      action_flag_ = false;
  }


  if (player_mode_ == MODE_GUIDE){
      uriel_->SetDestPos(GetPos());
  }
  // 誘導モードが一定時間以上

  // ギミックON/OFF
  //if (pKeyboard.IsTrigger(DIK_K)){
  //    SetAnimation(MODE_GIMMICK);
  //    action_flag_ = true;
  //}

  // アニメーション更新
  p_texture_animation_->UpdateAnimation();
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//==============================================================================
void Player::PreProccessOfDraw(void){
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
      texture_uv_.x += texture_uv_offset_.x;
      texture_uv_offset_.x *= -1;
  }

  SetStartUV(D3DXVECTOR2(texture_uv_));
  SetEndUV(D3DXVECTOR2(texture_uv_ + texture_uv_offset_));
}

//==============================================================================
// アニメーションセット処理
// 引数    :  PLAYER_MODE mode_
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/29
//==============================================================================
void Player::SetAnimation(PLAYER_MODE mode_){
    if (player_mode_ != mode_){
        switch (mode_){
        case MODE_NONE:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_NONE);
            break;
        case MODE_GUIDE:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
            break;
        case MODE_GIMMICK:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
            break;
        }
        player_mode_ = mode_;
    }
}

// EOF