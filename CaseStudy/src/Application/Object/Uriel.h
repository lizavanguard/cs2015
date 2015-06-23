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
#define URIEL_MOVE_SPPD (3.0f)                               // ウリエルの移動速度(通常)
#define URIEL_MOVE_CHARGE_SPEED (URIEL_MOVE_SPPD * 1.5f)     // ウリエルの移動速度(チャージ)
#define URIEL_MOVE_RUNAWAY_SPPD (URIEL_MOVE_SPPD * 2.0f)     // ウリエルの移動速度(暴走)
#define URIEL_RUNAWAY_TIME (180)                             // ウリエルの暴走時間
#define URIEL_INDUCIBLE (400.0f)                             // ウリエルの誘導可能距離
#define URIEL_SLEEP_TIME (180)                               // ウリエルの眠り時間
#define URIEL_BOROCHAGE_INTERVAL (60)                        // ボーロチャージできるまでのインターバル時間

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum {
  URIEL_STATUS_NONE = -1,                                 // 状態エラー
  URIEL_STATUS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,         // ニュートラル状態
  URIEL_STATUS_CRAWL = ANIMATION_URIEL_CRAWL,             // ハイハイ状態
  URIEL_STATUS_JUMP = ANIMATION_URIEL_JUMP,               // ジャンプ状態
  URIEL_STATUS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,         // 暴走状態
  URIEL_STATUS_SLEEP = ANIMATION_URIEL_SLEEP,             // 眠り状態
  URIEL_STATUS_CHARGECRAWL = ANIMATION_URIEL_CHARGECRAWL, // ハイハイ(チャージ)状態
  URIEL_STATUS_CHARGEJUMP = ANIMATION_URIEL_CHARGEJUMP,   // ジャンプ(チャージ)状態
  URIEL_STATUS_GOAL = ANIMATION_URIEL_GOAL,               // ゴール時の演出
  URIEL_STATUS_MAX
}URIEL_STATUS;

typedef enum{
  BLOCK_DATA_ERROR = -1,
  BLOCK_DATA_UP_STAIRS,
  BLOCK_DATA_DOWN_STAIRS,
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

  // ボーロチャージ(ボーロチャージ出来ればtrueが返る)
  bool BoroChage(void);

  // hit処理(by Ohashi)
  void HitManage();

  // オブジェクトとのHit判定(by Shimizu)
  bool CheckHit(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

private:
  void UpdateNeutral(void);
  void UpdateCrawl(void);
  void UpdateJump(void);
  void UpdateRunaway(void);
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
  D3DXVECTOR3 jump_before_pos_;
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
};


#endif // __H_URIEL_H__
