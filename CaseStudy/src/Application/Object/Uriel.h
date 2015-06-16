//==============================================================================
//
// �E���G�� [Uriel.h]
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
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define URIEL_MOVE_SPPD (5.0f)                               // �E���G���̈ړ����x(�ʏ�)
#define URIEL_MOVE_RUNAWAY_SPPD (URIEL_MOVE_SPPD * 2.0f)     // �E���G���̈ړ����x(�\��)
#define URIEL_RUNAWAY_TIME (120)                             // �E���G���̖\������
#define URIEL_INDUCIBLE (400.0f)                             // �E���G���̗U���\����
#define URIEL_SLEEP_TIME (180)                               // �E���G���̖��莞��
#define URIEL_BOROCHAGE_INTERVAL (60)                        // �{�[���`���[�W�ł���܂ł̃C���^�[�o������
#define URIEL_BOROGAGE_ADD_AMOUNT (60.0f)                    // �{�[���`���[�W�ő�����Q�[�W�̗�
#define URIEL_BOROGAGE_SUB_AMOUNT (0.1f)                     // �{�[���`���[�W�Q�[�W�̌�����(�\�����ĂȂ���)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �񋓑̒�`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum {
  URIEL_STATAS_NONE = -1,                                 // ��ԃG���[
  URIEL_STATAS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,         // �j���[�g�������
  URIEL_STATAS_CRAWL = ANIMATION_URIEL_CRAWL,             // �n�C�n�C���
  URIEL_STATAS_JUMP = ANIMATION_URIEL_JUMP,               // �W�����v���
  URIEL_STATAS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,         // �\�����
  URIEL_STATAS_SLEEP = ANIMATION_URIEL_SLEEP,             // ������
  URIEL_STATAS_CHARGECRAWL = ANIMATION_URIEL_CHARGECRAWL, // �n�C�n�C(�`���[�W)���
  URIEL_STATAS_CHARGEJUMP = ANIMATION_URIEL_CHARGEJUMP,   // �W�����v(�`���[�W)���
  URIEL_STATAS_GOAL = ANIMATION_URIEL_GOAL,               // �S�[�����̉��o
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
  virtual void _PreProcessOfDraw(void);

  // set
  void SetAnimaton(ANIMATION_EVENT animation_event);
  void SetDestPos(const D3DXVECTOR3& pos);

  // �{�[���`���[�W(�{�[���`���[�W�o�����true���Ԃ�)
  bool BoroChage(void);

  // hit����(by Ohashi)
  void HitManage();

  // �I�u�W�F�N�g�Ƃ�Hit����(by Shimizu)
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
