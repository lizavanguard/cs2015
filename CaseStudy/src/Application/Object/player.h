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
  Player(ANIMATION_EVENT animation_event);
  // dtor
  virtual ~Player();
  // update
  void Update(Uriel *uriel_);

  // draw
  virtual void PreProccessOfDraw(void);

  // �A�j���[�V�����̕ύX
  void ChangeAnimation(PLAYER_MODE mode);

  // get
  bool IsActing(void) const { return player_mode_ != MODE_NORMAL; }
  PLAYER_MODE GetPlayerMode(void) const { return player_mode_; }

  // parameter =================================
private:
  // �v���C���[�̃��[�h
  PLAYER_MODE player_mode_;
  int count_;
  bool is_eat_;
};

#endif
// EOF