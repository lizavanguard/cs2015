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
// ライブラリのリンク
//******************************************************************************


//******************************************************************************
// マクロ定義
//******************************************************************************
#define PLAYER_MOVE_SPEED (10.0f)

//******************************************************************************
// 構造体定義
//******************************************************************************


//******************************************************************************
// クラス定義
//******************************************************************************
class Player : public AnimationObject{
  public:
  // modemanaged
  typedef enum {
    MODE_NONE = 0,
    MODE_GUIDE ,
    MODE_GIMMICK
  }PLAYER_MODE;

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
  //actionGetter(ガラガラが何もしていなければfalse)
  bool GetAction(void){ return action_flag_; }
  PLAYER_MODE GetPlayerMode(void){ return player_mode_; }

  // set
  void SetPos(const D3DXVECTOR3& pos) { pos_ = pos; }
  void SetRot(const D3DXVECTOR2& rot) { rot_ = rot; }
  void SetSize(const D3DXVECTOR2& size) { size_ = size; }
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }
  void SetAnimation(PLAYER_MODE mode_);

protected:

private:


  // parameter =================================
public:

protected:

private:
  // ガラガラモード
  PLAYER_MODE player_mode_;
  // アクションフラグ
  bool action_flag_;
};

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************



#endif
// EOF