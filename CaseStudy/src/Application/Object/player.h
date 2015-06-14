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
  Player(ANIMATION_EVENT animation_event);
  // dtor
  virtual ~Player();
  // update
  void Update(Uriel *uriel_);

  // draw
  virtual void PreProccessOfDraw(void);

  // アニメーションの変更
  void ChangeAnimation(PLAYER_MODE mode);

  // get
  bool IsActing(void) const { return player_mode_ != MODE_NORMAL; }
  PLAYER_MODE GetPlayerMode(void) const { return player_mode_; }

  // parameter =================================
private:
  // プレイヤーのモード
  PLAYER_MODE player_mode_;
  int count_;
  bool is_eat_;
};

#endif
// EOF