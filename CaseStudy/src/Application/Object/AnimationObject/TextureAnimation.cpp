//==============================================================================
//
// テクスチャーアニメーション [TextureAnimation.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "TextureAnimation.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
  int time_;           // アニメーションの時間
  int start_number_;   // アニメーションの開始番号
  int number_;         // アニメーションの個数
  char *data_;         // アニメーションデータの名前(画像)
}ANIM_DATA;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// アニメーションデータ
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const ANIM_DATA s_AnimaitionData[] = {
  // アニメーションの切り替わる時間  // アニメーションの開始番号  // アニメーションの個数  // テクスチャの名前
  { 0, 0, 0, "data/Texture/tex_anim_00.png" },                    // ウリエルアニメーション無し
  { 5, 4, 4, "data/Texture/tex_anim_00.png" },                    // ウリエルニュートラル
  { 5, 8, 16, "data/Texture/tex_anim_00.png" },                   // ウリエルハイハイ
  { 5, 4, 4, "data/Texture/tex_anim_00.png" },                    // ウリエルジャンプ
  { 2, 8, 16, "data/Texture/tex_anim_00.png" },                   // ウリエル暴走
  { 5, 8, 16, "data/Texture/tex_anim_00.png" },                   // ウリエル眠り
  { 3, 8, 16, "data/Texture/tex_anim_00.png" },                   // ウリエルハイハイ(チャージ)
  { 5, 4, 4, "data/Texture/tex_anim_00.png" },                    // ウリエルジャンプ(チャージ)
  { 30, 8, 16, "data/Texture/tex_anim_00.png" },                  // ウリエル回転(ゴール時の演出)
  { 0, 0, 0, "data/Texture/tex_anim_00.png" },                    // ガラガラアニメーション無し
  { 5, 0, 4, "data/Texture/tex_anim_00.png" },                    // ガラガラを振る
  { 0, 0, 0, "data/Texture/tex_anim_01.png" },                    // 鳥アニメーション無し
  { 0, 1, 0, "data/Texture/tex_anim_01.png" },                    // 鳥喜ぶ
  { 15, 2, 2, "data/Texture/tex_anim_01.png" },                   // 鳥が上へ飛ぶ
};

//==============================================================================
// class implementation
//==============================================================================
// ctor
TextureAnimation::TextureAnimation(){
  texture_uv_ = D3DXVECTOR2(0.0f, 0.0f);
  animation_ = ANIMATION_NONE;
  animation_number_ = 0;
  timer_ = 0;
  animation_end_flag_ = false;
}

// dtor
TextureAnimation::~TextureAnimation(){
}

//=============================================================================
// アニメーションの更新
//-----------------------------------------------------------------------------
void TextureAnimation::UpdateAnimation(void){
  ++timer_;
  animation_end_flag_ = false;

  if (timer_ >= s_AnimaitionData[animation_].time_ &&
      s_AnimaitionData[animation_].time_ != 0){
    timer_ = 0;
    ++animation_number_;

    int number_ = s_AnimaitionData[animation_].number_ + s_AnimaitionData[animation_].start_number_;
    number_ = number_ > DIVISION_NUMBER_X * DIVISION_NUMBER_Y ? 16 : number_;

    if (animation_number_ >= number_){
      animation_number_ = s_AnimaitionData[animation_].start_number_;
      animation_end_flag_ = true;
    }

    float uv_x_ = (animation_number_ % (int)DIVISION_NUMBER_X) / DIVISION_NUMBER_X;
    float uv_x_offset_ = 1 / DIVISION_NUMBER_X;

    float uv_y_ = (int)animation_number_ / (int)DIVISION_NUMBER_Y / DIVISION_NUMBER_Y;
    float uv_y_offset_ = 1 / DIVISION_NUMBER_Y;

    texture_uv_.x = uv_x_;
    texture_uv_.y = uv_y_;
  }
}

//=============================================================================
// アニメーションの設定
//-----------------------------------------------------------------------------
int TextureAnimation::SetAnimation(ANIMATION_EVENT animation_event){
  animation_ = animation_event;
  timer_ = 0;
  animation_number_ = s_AnimaitionData[animation_].start_number_;

  float uv_x_ = (animation_number_ % (int)DIVISION_NUMBER_X) / DIVISION_NUMBER_X;
  float uv_x_offset_ = 1 / DIVISION_NUMBER_X;

  float uv_y_ = (int)animation_number_ / (int)DIVISION_NUMBER_Y / DIVISION_NUMBER_Y;
  float uv_y_offset_ = 1 / DIVISION_NUMBER_Y;

  texture_uv_.x = uv_x_;
  texture_uv_.y = uv_y_;

  animation_number_ = s_AnimaitionData[animation_].start_number_;

  return TextureManagerHolder::Instance().GetTextureManager().LoadTexture(s_AnimaitionData[animation_].data_);
}

//=============================================================================
// アニメーション時間の取得
//-----------------------------------------------------------------------------
int TextureAnimation::GetAnimationChangeTime(void){
  return s_AnimaitionData[animation_].time_;
}

//=============================================================================
// 今のアニメーション総時間取得
//-----------------------------------------------------------------------------
int TextureAnimation::GetAnimationTime(void){
  return s_AnimaitionData[animation_].time_ * s_AnimaitionData[animation_].number_;
}

// EOF