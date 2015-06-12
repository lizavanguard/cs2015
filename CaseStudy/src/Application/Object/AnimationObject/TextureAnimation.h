//==============================================================================
//
// テクスチャーアニメーション [TextureAnimation.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_TEXTURE_ANIMATION_H__
#define __H_TEXTURE_ANIMATION_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DIVISION_NUMBER_X (4.0f)  // テクスチャの横方向の分割数
#define DIVISION_NUMBER_Y (4.0f)  // テクスチャの縦方向の分割数

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//アニメーションリスト
typedef enum
{
  ANIMATION_NONE = -1,                  // テクスチャ無し
  ANIMATION_URIEL_NONE,                 // ウリエルアニメーション無し
  ANIMATION_URIEL_NEUTRAL,              // ウリエルニュートラル
  ANIMATION_URIEL_CRAWL,                // ウリエルハイハイ
  ANIMATION_URIEL_JUMP,                 // ウリエルジャンプ
  ANIMATION_URIEL_RUNAWAY,              // ウリエル暴走
  ANIMATION_URIEL_SLEEP,                // ウリエル眠り
  ANIMATION_URIEL_CHARGE,               // ウリエルチャージ
  ANIMATION_URIEL_GOAL,                 // ウリエル回転(ゴール時の演出)
  ANIMATION_PLAYER_RATTEL_NONE,         // ガラガラアニメーション無し
  ANIMATION_PLAYER_RATTEL_BORO,         // ボーロアニメーション
  ANIMATION_PLAYER_RATTEL_GIMMICK,      // ギミック
  ANIMATION_PLAYER_RATTEL_SHAKE,        // ガラガラを振る
  ANIMATION_TORI_NONE,                  // 鳥アニメーション無し
  ANIMATION_TORI_HAPPY,                 // 鳥喜ぶ
  ANIMATION_TORI_FLY_TOP,               // 鳥が上へ飛ぶ
  ANIMATION_MAX                         // 
}ANIMATION_EVENT;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TextureAnimation{
public:
  // ctor
  TextureAnimation();

  // dtor
  virtual ~TextureAnimation();

  // アニメーションの更新
  void UpdateAnimation(void);
  // アニメーションの設定
  int SetAnimation(ANIMATION_EVENT animation_event);
  // テクスチャのUV取得
  D3DXVECTOR2 GetTextureUV(void){ return texture_uv_; }
  // テクスチャのオフセット取得
  D3DXVECTOR2 GetTextureUVOffset(void){ return D3DXVECTOR2(1 / DIVISION_NUMBER_X, 1 / DIVISION_NUMBER_Y); }
  // アニメーションが終端かどうか(終端ならtrueが返る)
  bool GetAnimationEnd(void){ return animation_end_flag_; }
  // 今のアニメーション切り替え時間が返る
  int GetAnimationChangeTime(void);
  // 今のアニメーション総時間取得
  int GetAnimationTime(void);

private:
  D3DXVECTOR2 texture_uv_;
  ANIMATION_EVENT animation_;
  int animation_number_;
  int timer_;
  bool animation_end_flag_;
};

#endif // __H_TEXTURE_ANIMATION_H__

// EOF
