//******************************************************************************
//
// �v���C���[����  [plyaer.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Uriel.h"
#include "AnimationObject/AnimationObject.h"

//******************************************************************************
// �N���X��`
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

  // �A�j���[�V�����̕ύX
  void ChangeAnimation(PLAYER_MODE mode);

  // �{�[����Ԃ̏I��
  void FinishBoroState(void);

  // get
  const D3DXVECTOR3& GetPos(void) const { return pos_; }
  const D3DXVECTOR3 GetBoroPos(void) const;
  bool IsActing(void) const { return player_mode_ != MODE_NORMAL; }
  bool IsBoroState(void) const { return player_mode_ == MODE_BORO; }
  PLAYER_MODE GetPlayerMode(void) const { return player_mode_; }
  void SetMoveStop(bool move_stop_flag){ move_stop_flag_ = move_stop_flag; }  // �`���[�g���A���p�ɒǉ�(by Momoi) 2015/07/13

  // parameter =================================
private:
  // �v���C���[�̃��[�h
  PLAYER_MODE player_mode_;
  int count_;
  bool is_eat_;
  Stage* stage_;
  D3DXVECTOR2 stageSize_;
  bool move_stop_flag_;    // �`���[�g���A���p�ɒǉ�(by Momoi) 2015/07/13
};

#endif
// EOF