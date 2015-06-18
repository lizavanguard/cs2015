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
#define URIEL_MOVE_RUNAWAY_SPPD (URIEL_MOVE_SPPD * 1.5f)     // �E���G���̈ړ����x(�\��)
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
  URIEL_STATUS_NONE = -1,                                 // ��ԃG���[
  URIEL_STATUS_NEUTRAL = ANIMATION_URIEL_NEUTRAL,         // �j���[�g�������
  URIEL_STATUS_CRAWL = ANIMATION_URIEL_CRAWL,             // �n�C�n�C���
  URIEL_STATUS_JUMP = ANIMATION_URIEL_JUMP,               // �W�����v���
  URIEL_STATUS_RUNAWAY = ANIMATION_URIEL_RUNAWAY,         // �\�����
  URIEL_STATUS_SLEEP = ANIMATION_URIEL_SLEEP,             // ������
  URIEL_STATUS_CHARGECRAWL = ANIMATION_URIEL_CHARGECRAWL, // �n�C�n�C(�`���[�W)���
  URIEL_STATUS_CHARGEJUMP = ANIMATION_URIEL_CHARGEJUMP,   // �W�����v(�`���[�W)���
  URIEL_STATUS_GOAL = ANIMATION_URIEL_GOAL,               // �S�[�����̉��o
  URIEL_STATUS_MAX
}URIEL_STATUS;

typedef enum{
  BLOCK_DATA_ERROR = -1,
  BLOCK_DATA_STAIRS,
  BLOCK_DATA_JUMP,
  BLOCK_DATA_MAX
}BLOCK_DATA;

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

  // set
  void SetAnimaton(ANIMATION_EVENT animation_event);
  void SetDestPos(const D3DXVECTOR3& pos);

  // �{�[���`���[�W(�{�[���`���[�W�o�����true���Ԃ�)
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
  BLOCK_DATA LoadCheck(void);
  BLOCK_DATA CrawlLoadCheck(void);
  BLOCK_DATA ChargeCrawlLoadCheck(void);
  // �W�����v���鍂���Ƌ����ƖړI�n�̍��፷�Ƃ�����d�͂�n���Έړ��ʂ��Ԃ��Ă���(2D�p)
  D3DXVECTOR2 JumpAngleSeek(float top, float length, float difference_in_height, float gravity);
  D3DXVECTOR3 dest_position_;
  D3DXVECTOR3 old_position_;
  D3DXVECTOR3 jump_before_pos_;
  D3DXVECTOR3 move_;
  D3DXVECTOR3 map_;
  Stage* p_stage_;
  int status_;
  float boro_gage_;
  bool boro_gage_max_;
  int boro_interval_;
  bool charge_flag_;
  int runaway_timer_;
  int sleep_timer_;
};


#endif // __H_URIEL_H__
