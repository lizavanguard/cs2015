//==============================================================================
//
// ウリエル [Uriel.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Uriel.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Application/Stage/Stage.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define GRAVITY	(-0.49f)

//==============================================================================
// class implementation
//==============================================================================
// ctor
Uriel::Uriel(ANIMATION_EVENT animation_event, Stage* stage) : AnimationObject(animation_event) {
  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_.x = URIEL_MOVE_SPPD;
  jump_before_pos_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  p_stage_ = stage;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  boro_gage_ = 0.0f;
  boro_gage_max_ = false;
  boro_interval_ = 0;
  charge_flag_ = false;
  runaway_timer_ = 0;
  sleep_timer_ = 0;
  old_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  // ステージからスタート場所を貰う
  pos_ = stage->GetStartMaptip();

  SetAnimaton(animation_event);
}

// dtor
Uriel::~Uriel() {
}

// update
void Uriel::Update(void){
  // 重力処理
  move_.y += GRAVITY;

  // 状態別の更新
  switch (status_){
  // 更新なし
  case URIEL_STATUS_NONE:
    break;
  // ニュートラル状態
  case URIEL_STATUS_NEUTRAL:
    UpdateNeutral();
    break;
  // ハイハイ状態
  case URIEL_STATUS_CRAWL:
    UpdateCrawl();
    break;
  // ジャンプ状態
  case URIEL_STATUS_JUMP:
    UpdateJump();
    break;
  // 暴走状態
  case URIEL_STATUS_RUNAWAY:
    UpdateRunaway();
    break;
  // 眠り状態
  case URIEL_STATUS_SLEEP:
    UpdateSleep();
    break;
  // ハイハイ(チャージ)状態
  case URIEL_STATUS_CHARGECRAWL:
    UpdateChargeCrawl();
    break;
  // ジャンプ(チャージ)状態
  case URIEL_STATUS_CHARGEJUMP:
    UpdateChargeJump();
    break;
  // ゴール状態
  case URIEL_STATUS_GOAL:
    UpdateGoal();
    break;
  }

  // 向きの調整
  if (move_.x > 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }

  // 移動
  pos_ += move_;

  // TODO (現状完ぺきではない)
  // 目の前が壁なら反転
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  if (move_direction_ == DIRECTION_LEFT){
    map = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x/2,pos_.y,pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (/*check.left == MAP_TYPE_NORMAL ||*/
      check.left == -1){
      move_.x *= -1;
    }
  } else {
    map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (/*check.right == MAP_TYPE_NORMAL ||*/
      check.right == -1){
      move_.x *= -1;
    }
  }

  // ボーロチャージインターバル時間の減少
  if (boro_interval_ > 0)
    -- boro_interval_;

  // ボーロゲージの減少
  if (!boro_gage_max_ && (boro_gage_ - URIEL_BOROGAGE_SUB_AMOUNT) > 0){
    boro_gage_ -= URIEL_BOROGAGE_SUB_AMOUNT;

    if (boro_gage_ < 0){
      boro_gage_ = 0;
    }
  }
  if (status_ != URIEL_STATUS_NONE){
    // アニメーション更新
    p_texture_animation_->UpdateAnimation();
  }
}

// draw
void Uriel::PreProccessOfDraw(void) {
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_RIGHT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  SetStartUV(D3DXVECTOR2(texture_uv_));
  SetEndUV(D3DXVECTOR2(texture_uv_ + texture_uv_offset_));
}

//=============================================================================
// アニメーションの設定
//-----------------------------------------------------------------------------
void Uriel::SetAnimaton(ANIMATION_EVENT animation_event){
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
  status_ = animation_event;
}

//=============================================================================
// ウリエルの目的地点設定
//-----------------------------------------------------------------------------
void Uriel::SetDestPos(const D3DXVECTOR3& pos){
  if (abs(pos.x - pos_.x) < URIEL_INDUCIBLE)
    dest_position_ = pos;
}

//=============================================================================
// ボーロチャージ
//-----------------------------------------------------------------------------
bool Uriel::BoroChage(void){
  if (!charge_flag_ && boro_interval_ <= 0){
    SetAnimaton(ANIMATION_URIEL_CHARGECRAWL);
    charge_flag_ = true;
    boro_interval_ = URIEL_BOROCHAGE_INTERVAL;
    boro_gage_ += URIEL_BOROGAGE_ADD_AMOUNT;
    if (boro_gage_ > 100.0f){
      boro_gage_ = 100.0f;
      boro_gage_max_ = true;
    }
    return true;
  }

  return false;
}

//=============================================================================
// ニュートラル状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateNeutral(void){

}

//=============================================================================
// ハイハイ状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateCrawl(void){
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > URIEL_MOVE_SPPD){
      move_.x = URIEL_MOVE_SPPD;
    } else if (dest_position_.x - pos_.x < -URIEL_MOVE_SPPD){
      move_.x = -URIEL_MOVE_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // 地面との当たり判定
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // 下が地面で目の前が登れるブロックなら
  if (check.center == MAP_TYPE_NORMAL && check.bottom == MAP_TYPE_NORMAL){
    //pos_.y = map.y + 25.0f * 1.9f + 100.0f;
  }
  // 下が地面なら
  if (check.center == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // ジャンプするかチェックしてジャンプできるならジャンプ
  if (JumpCheck()){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 150.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // ジャンプ前の座標を保存
    jump_before_pos_ = pos_;
  }
}

//=============================================================================
// ジャンプ状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateJump(void){
  // 跳べる距離の限界で地面が無かったら
  if (jump_before_pos_.y > pos_.y){
    //move_.x = 0.0f;
  }
  // 地面との当たり判定
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.center == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    move_.x = URIEL_MOVE_SPPD * (move_.x / abs(move_.x));
  }
}

//=============================================================================
// 暴走状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateRunaway(void){
  // 一定時間暴走したら眠る
  if (runaway_timer_ >= URIEL_RUNAWAY_TIME){
    SetAnimaton(ANIMATION_URIEL_SLEEP);
    runaway_timer_ = 0;
  }

  ++runaway_timer_;
}

//=============================================================================
// 眠り状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateSleep(void){
  ++ sleep_timer_;

  if (sleep_timer_ > URIEL_SLEEP_TIME){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    sleep_timer_ = 0;
    move_.x = URIEL_MOVE_SPPD;
  }
}

//=============================================================================
// ハイハイ(チャージ)状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeCrawl(void){
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > URIEL_MOVE_SPPD){
      move_.x = URIEL_MOVE_SPPD;
    } else if (dest_position_.x - pos_.x < -URIEL_MOVE_SPPD){
      move_.x = -URIEL_MOVE_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // 地面との当たり判定
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // 下が地面で目の前が登れるブロックなら
  if (check.center == MAP_TYPE_NORMAL && check.bottom == MAP_TYPE_NORMAL){
    //pos_.y = map.y + 25.0f * 1.9f + 100.0f;
  }
  // 下が地面なら
  if (check.center == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // ジャンプするかチェックしてジャンプできるならジャンプ
  if (JumpCheck()){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 250.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // ジャンプ前の座標を保存
    jump_before_pos_ = pos_;
  }

  // boro_interval_が0以下ならチャージモードを止める
  if (boro_interval_ <= 0){
    charge_flag_ = false;

    // boro_gage_max_がtrueなら暴走
    if (boro_gage_max_){
      SetAnimaton(ANIMATION_URIEL_RUNAWAY);
      runaway_timer_ = URIEL_RUNAWAY_TIME;
      move_.x = URIEL_MOVE_RUNAWAY_SPPD;
    } else {
      // 通常に戻る
      SetAnimaton(ANIMATION_URIEL_CRAWL);
      move_.x = URIEL_MOVE_SPPD;
    }
  }
}

//=============================================================================
// ジャンプ(チャージ)状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeJump(void){

}

//=============================================================================
// ゴール状態の更新
//-----------------------------------------------------------------------------
void Uriel::UpdateGoal(void){

}

//=============================================================================
// ジャンプできるかのチェック
//-----------------------------------------------------------------------------
bool Uriel::JumpCheck(void){
  switch (status_)
  {
  case URIEL_STATUS_CRAWL:
    return CrawlJumpCheck();
    break;
  case URIEL_STATUS_CHARGECRAWL:
    return ChargeCrawlJumpCheck();
    break;
  default:
    return false;
    break;
  }
}

//=============================================================================
// ハイハイ状態でジャンプできるかのチェック
//-----------------------------------------------------------------------------
bool Uriel::CrawlJumpCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.center == MAP_TYPE_NORMAL){
    // 右に進んでる場合
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.right == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.right == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
    // 左に進んでる場合
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.left == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.left == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
  }
  return false;
}

//=============================================================================
// チャージハイハイ状態でジャンプできるかのチェック
//-----------------------------------------------------------------------------
bool Uriel::ChargeCrawlJumpCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.center == MAP_TYPE_NORMAL){
    // 右に進んでる場合
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.right == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x * 2, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.center == MAP_TYPE_NONE && check.right == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
    // 左に進んでる場合
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.left == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.left == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
  }
  return false;
}

//=============================================================================
// ジャンプするたかさと距離とかかる重力を渡せば移動量が返ってくる(2D用)
//-----------------------------------------------------------------------------
D3DXVECTOR2 Uriel::JumpAngleSeek(float top, float length, float gravity)
{
  D3DXVECTOR2 move(0,0);
  float v = 0.0f;
  float rot = 0.0f;
  float time = 0.0f;
  float g = abs(gravity);
  rot = atanf((top * 4) / length);
  v = sqrtf(g * top * 2) / sinf(rot);
  time = 2 * sqrtf((2 * top) / g);
  move.x = v * cosf(rot);
  move.y = v * sinf(rot) - (g * time);
  move.x = move.x * (move_.x / abs(move_.x));
  move.y = move.y * -1;
  return move;
}
// EOF