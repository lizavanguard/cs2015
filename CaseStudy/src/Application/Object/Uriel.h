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
#define URIEL_MOVE_RUNAWAY_SPPD (URIEL_MOVE_SPPD * 2.0f)     // ウリエルの移動速度(暴走)
#define URIEL_RUNAWAY_TIME (120)                             // ウリエルの暴走時間
#define URIEL_INDUCIBLE (400.0f)                             // ウリエルの誘導可能距離
#define URIEL_SLEEP_TIME (180)                               // ウリエルの眠り時間
#define URIEL_BOROCHAGE_INTERVAL (60)                        // ボーロチャージできるまでのインターバル時間
#define URIEL_BOROGAGE_ADD_AMOUNT (60.0f)                    // ボーロチャージで増えるゲージの量
#define URIEL_BOROGAGE_SUB_AMOUNT (0.1f)                     // ボーロチャージゲージの減少量(暴走してない時)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum {
  URIEL_STATAS_NONE = -1,                                 // 状態エラー
  URIEL_STATAS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,         // ニュートラル状態
  URIEL_STATAS_CRAWL = ANIMATION_URIEL_CRAWL,             // ハイハイ状態
  URIEL_STATAS_JUMP = ANIMATION_URIEL_JUMP,               // ジャンプ状態
  URIEL_STATAS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,         // 暴走状態
  URIEL_STATAS_SLEEP = ANIMATION_URIEL_SLEEP,             // 眠り状態
  URIEL_STATAS_CHARGECRAWL = ANIMATION_URIEL_CHARGECRAWL, // ハイハイ(チャージ)状態
  URIEL_STATAS_CHARGEJUMP = ANIMATION_URIEL_CHARGEJUMP,   // ジャンプ(チャージ)状態
  URIEL_STATAS_GOAL = ANIMATION_URIEL_GOAL,               // ゴール時の演出
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
  int GetStatas(void){ return statas_; }

  // set
  void SetPos(const D3DXVECTOR3& pos) { pos_ = pos; }
  void SetRot(const D3DXVECTOR2& rot) { rot_ = rot; }
  void SetSize(const D3DXVECTOR2& size) { size_ = size; }
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }
  void SetAnimaton(ANIMATION_EVENT animation_event);
  void SetDestPos(const D3DXVECTOR3& pos);

  // ボーロチャージ(ボーロチャージ出来ればtrueが返る)
  bool BoroChage(void);

private:
  void UpdateNeutral(void);
  void UpdateCrawl(void);
  void UpdateJump(void);
  void UpdateRunaway(void);
  void UpdateSleep(void);
  void UpdateChargeCrawl(void);
  void UpdateChargeJump(void);
  void UpdateGoal(void);
  D3DXVECTOR3 dest_position_;
  float move_speed_;
  Stage* p_stage_;
  int statas_;
  float boro_gage_;
  bool boro_gage_max_;
  int boro_interval_;
  bool charge_flag_;
  int runaway_timer_;
  int sleep_timer_;
};


#endif // __H_URIEL_H__
