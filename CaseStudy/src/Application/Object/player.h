//******************************************************************************
//
// プレイヤー処理  [plyaer.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/05/22
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Uriel.h"
#include "AnimationObject/AnimationObject.h"

//******************************************************************************
// クラス定義
//******************************************************************************
class Player : public AnimationObject {
public:
  // modemanaged
  typedef enum {
    MODE_NORMAL = 0,
    MODE_BORO,
    MODE_GUIDE,
    MODE_GIMMICK,
    kModeMax
  } PLAYER_MODE;

  // funciton ==================================
public:
  // ctor
  Player(ANIMATION_EVENT animation_event , Stage* stage);
  // dtor
  virtual ~Player();
  // update
  void Update(Uriel *uriel_);

  // draw
  virtual void _PreProcessOfDraw(void);

  // アニメーションの変更
  void ChangeAnimation(PLAYER_MODE mode);

  // ボーロ状態の終了
  void FinishBoroState(void);

  // get
  const D3DXVECTOR3& GetPos(void) const { return pos_; }
  const D3DXVECTOR3 GetBoroPos(void) const;
  bool IsActing(void) const { return player_mode_ != MODE_NORMAL; }
  bool IsBoroState(void) const { return player_mode_ == MODE_BORO; }
  PLAYER_MODE GetPlayerMode(void) const { return player_mode_; }

  // parameter =================================
private:
  // プレイヤーのモード
  PLAYER_MODE player_mode_;
  int count_;
  bool is_eat_;
  Stage* stage_;
  D3DXVECTOR2 stageSize_;
};

#endif
// EOF