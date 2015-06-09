//==============================================================================
//
// ウリエル [Uriel.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_URIEL_H__
#define __H_URIEL_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "AnimationObject/AnimationObject.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define URIEL_MOVE_SPPD (5.0f)                               // ウリエルの移動速度(通常)
#define URIEL_MOVE_RUNAWAY_SPPD (URIEL_MOVE_SPPD * 1.5f)     // ウリエルの移動速度(暴走)
#define URIEL_INDUCIBLE (400.0f)                             // ウリエルの誘導可能距離

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum {
  URIEL_STATAS_NONE = -1,                                // 状態エラー
  URIEL_STATAS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,        // ニュートラル状態
  URIEL_STATAS_CRAWL = ANIMATION_URIEL_CRAWL,            // ハイハイ状態
  URIEL_STATAS_JUMP = ANIMATION_URIEL_JUMP,              // ジャンプ状態
  URIEL_STATAS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,        // 暴走状態
  URIEL_STATAS_SLEEP = ANIMATION_URIEL_SLEEP,            // 眠り状態
  URIEL_STATAS_CHARGE = ANIMATION_URIEL_CHARGE,          // チャージ状態
  URIEL_STATAS_GOAL = ANIMATION_URIEL_GOAL,              // ゴール時の演出
  URIEL_STATAS_MAX
}URIEL_STATAS;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Uriel : public AnimationObject {
public:
  // ctor
  Uriel(ANIMATION_EVENT animation_event,Stage* stage);

  // dtor
  virtual ~Uriel();

  // update
  void Update(void);

  // draw
  virtual void PreProccessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos) { pos_ += pos; }
  void AddPosX(float x) { pos_.x += x; }
  void AddPosY(float y) { pos_.y += y; }
  void AddPosZ(float z) { pos_.z += z; }

  // add rot
  void AddRot(const D3DXVECTOR2& rot) { rot_ += rot; }

  // add size
  void AddSize(const D3DXVECTOR2& size) { size_ += size; }

  // get
  D3DXVECTOR3 GetPos(void) const { return pos_; }
  D3DXVECTOR2 GetRot(void) const { return rot_; }
  D3DXVECTOR2 GetSize(void) const { return size_; }
  bool IsAlive(void) const { return is_alive_; }
  URIEL_STATAS GetStatas(void){ return statas_; }

  // set
  void SetPos(const D3DXVECTOR3& pos) { pos_ = pos; }
  void SetRot(const D3DXVECTOR2& rot) { rot_ = rot; }
  void SetSize(const D3DXVECTOR2& size) { size_ = size; }
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }
  void SetAnimaton(ANIMATION_EVENT animation_event);
  void SetDestPos(const D3DXVECTOR3& pos);

private:
  void UpdateNeutral(void);
  void UpdateCrawl(void);
  void UpdateJump(void);
  void UpdateRunaway(void);
  void UpdateSleep(void);
  void UpdateCharge(void);
  void UpdateGoal(void);
  D3DXVECTOR3 dest_position_;
  float move_speed_;
  Stage* p_stage_;
  URIEL_STATAS statas_;
};


#endif // __H_URIEL_H__
