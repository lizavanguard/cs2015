//==============================================================================
//
// �e�N�X�`���[�A�j���[�V���� [TextureAnimation.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_TEXTURE_ANIMATION_H__
#define __H_TEXTURE_ANIMATION_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DIVISION_NUMBER_X (4.0f)  // �e�N�X�`���̉������̕�����
#define DIVISION_NUMBER_Y (4.0f)  // �e�N�X�`���̏c�����̕�����

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �񋓑̒�`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�j���[�V�������X�g
typedef enum
{
  ANIMATION_NONE = -1,                  // �e�N�X�`������
  ANIMATION_URIEL_NONE,                 // �E���G���A�j���[�V��������
  ANIMATION_URIEL_NEUTRAL,              // �E���G���j���[�g����
  ANIMATION_URIEL_CRAWL,                // �E���G���n�C�n�C
  ANIMATION_URIEL_JUMP,                 // �E���G���W�����v
  ANIMATION_URIEL_RUNAWAY,              // �E���G���\��
  ANIMATION_URIEL_SLEEP,                // �E���G������
  ANIMATION_URIEL_CHARGE,               // �E���G���`���[�W
  ANIMATION_URIEL_GOAL,                 // �E���G����](�S�[�����̉��o)
  ANIMATION_PLAYER_RATTEL_NONE,         // �K���K���A�j���[�V��������
  ANIMATION_PLAYER_RATTEL_BORO,         // �{�[���A�j���[�V����
  ANIMATION_PLAYER_RATTEL_GIMMICK,      // �M�~�b�N
  ANIMATION_PLAYER_RATTEL_SHAKE,        // �K���K����U��
  ANIMATION_TORI_NONE,                  // ���A�j���[�V��������
  ANIMATION_TORI_HAPPY,                 // �����
  ANIMATION_TORI_FLY_TOP,               // ������֔��
  ANIMATION_MAX                         // 
}ANIMATION_EVENT;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TextureAnimation{
public:
  // ctor
  TextureAnimation();

  // dtor
  virtual ~TextureAnimation();

  // �A�j���[�V�����̍X�V
  void UpdateAnimation(void);
  // �A�j���[�V�����̐ݒ�
  int SetAnimation(ANIMATION_EVENT animation_event);
  // �e�N�X�`����UV�擾
  D3DXVECTOR2 GetTextureUV(void){ return texture_uv_; }
  // �e�N�X�`���̃I�t�Z�b�g�擾
  D3DXVECTOR2 GetTextureUVOffset(void){ return D3DXVECTOR2(1 / DIVISION_NUMBER_X, 1 / DIVISION_NUMBER_Y); }
  // �A�j���[�V�������I�[���ǂ���(�I�[�Ȃ�true���Ԃ�)
  bool GetAnimationEnd(void){ return animation_end_flag_; }
  // ���̃A�j���[�V�����؂�ւ����Ԃ��Ԃ�
  int GetAnimationChangeTime(void);
  // ���̃A�j���[�V���������Ԏ擾
  int GetAnimationTime(void);

private:
  D3DXVECTOR2 texture_uv_;
  ANIMATION_EVENT animation_;
  int animation_number_;
  int timer_;
  bool animation_end_flag_;
};

#endif // __H_TEXTURE_ANIMATION_H__

// EOF
