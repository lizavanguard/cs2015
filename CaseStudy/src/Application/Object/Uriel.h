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
// 列挙体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum {
  URIEL_STATUS_NONE = -1,                                   // 状態エラー
  URIEL_STATUS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,           // ニュートラル状態
  URIEL_STATUS_CRAWL = ANIMATION_URIEL_CRAWL,               // ハイハイ状態
  URIEL_STATUS_JUMP = ANIMATION_URIEL_JUMP,                 // ジャンプ状態
  URIEL_STATUS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,           // 暴走状態
  URIEL_STATUS_RUNAWAY_JUMP = ANIMATION_URIEL_RUNAWAY_JUMP, // 暴走状態でのジャンプ
  URIEL_STATUS_SLEEP = ANIMATION_URIEL_SLEEP,               // 眠り状態
  URIEL_STATUS_CHARGE_CRAWL = ANIMATION_URIEL_CHARGE_CRAWL, // ハイハイ(チャージ)状態
  URIEL_STATUS_CHARGE_JUMP = ANIMATION_URIEL_CHARGE_JUMP,   // ジャンプ(チャージ)状態
  URIEL_STATUS_GOAL = ANIMATION_URIEL_GOAL,                 // ゴール時の演出
  URIEL_STATUS_MAX
}URIEL_STATUS;

typedef enum{
  BLOCK_DATA_ERROR = -1,
  BLOCK_DATA_UP_STAIRS,
  BLOCK_DATA_JUMP,
  BLOCK_DATA_MAX
}BLOCK_DATA;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage;
class TensionGauge;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Uriel : public AnimationObject {
public:
  // ctor
  Uriel(ANIMATION_EVENT animation_event,Stage* stage,TensionGauge* p_tension_gauge);

  // dtor
  virtual ~Uriel();

  // update
  void Update(void);

  // draw
  virtual void _PreProcessOfDraw(void);

  // set
  void SetAnimaton(ANIMATION_EVENT animation_event);
  void SetDestPos(const D3DXVECTOR3& pos);
  void SetDestPos(const D3DXVECTOR3& pos, ANIM_OBJ_TYPE anim_obj_type, DIRECTION direction, AnimationObject* anim_obj);

  // ボーロチャージ(ボーロチャージ出来ればtrueが返る)
  bool BoroChage(void);

  // ボーロチャージ可能ならtrueが返る
  bool CheckBoro(void){ return !charge_flag_; }

  // hit処理(by Ohashi)
  void HitManage();

  // オブジェクトとのHit判定
  bool CheckHit(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

  // get
  const D3DXVECTOR3& GetPos(void) const {return pos_;}
  const D3DXVECTOR3 GetEatPos(void) const;
  // 表示オブジェクトとのHit判定(by Shimizu)
  bool CheckImageHit(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

private:
  static const int kUrielMoveSpped = 3;                                      // ウリエルの移動速度(通常)
  static const int kUrielMoveChargeSpeed = (int)(kUrielMoveSpped * 1.5f);    // ウリエルの移動速度(チャージ)
  static const int kUrielMoveRunawaySpped = (int)(kUrielMoveSpped * 2.0f);   // ウリエルの移動速度(暴走)
  static const int kUrielRunnawayTime = 180;                                 // ウリエルの暴走時間
  static const int kUrielInducible = 400;                                    // ウリエルの誘導可能距離
  static const int kUrielSleepTime = 180;                                    // ウリエルの眠り時間
  static const int kUrielBorochageInterval = 60;                             // ボーロチャージできるまでのインターバル時間
  static const int kUrielAttractibleFlower = 60;                             // ウリエルが花に引き付けられている時間
  static const int kUrielLookFlowerLength = 25;                              // ウリエルが花で止まる距離
  static const int kUrielLockButterflyLength = 10;                           // ウリエルが蝶に気づく範囲
  static const int kUrielChaseTheButterflyOffset = 15;                       // 蝶を追いかけるX座標のオフセット
  void UpdateNeutral(void);
  void UpdateCrawl(void);
  void UpdateJump(void);
  void UpdateRunaway(void);
  void UpdateRunawayJump(void);
  void UpdateSleep(void);
  void UpdateChargeCrawl(void);
  void UpdateChargeJump(void);
  void UpdateGoal(void);
  BLOCK_DATA LoadCheck(void);
  BLOCK_DATA CrawlLoadCheck(void);
  BLOCK_DATA ChargeCrawlLoadCheck(void);
  // ジャンプする高さと距離と目的地の高低差とかかる重力を渡せば移動量が返ってくる(2D用)
  D3DXVECTOR2 JumpAngleSeek(float top, float length, float difference_in_height, float gravity);
  D3DXVECTOR3 dest_position_;
  D3DXVECTOR3 old_position_;
  D3DXVECTOR3 move_;
  D3DXVECTOR3 map_;
  Stage* p_stage_;
  TensionGauge* p_tension_gauge_;
  int status_;
  bool boro_gage_max_;
  int boro_interval_;
  bool charge_flag_;
  int runaway_timer_;
  int sleep_timer_;
  bool induction_flag_;
  bool sang_induction_flag_;
  D3DXVECTOR3 sang_position_;
  ANIM_OBJ_TYPE sang_type_;
  DIRECTION sang_direction_;
  AnimationObject* sang_object_;
  AnimationObject* prev_sang_object_;
  int attractible_flower_timer_;
  bool butterfly_direction_change_flag_;
};


#endif // __H_URIEL_H__
