//==============================================================================
//
// �e�N�X�`���[�A�j���[�V���� [TextureAnimation.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "TextureAnimation.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\���̒�`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
  int time_;           // �A�j���[�V�����̎���
  int start_number_;   // �A�j���[�V�����̊J�n�ԍ�
  int number_;         // �A�j���[�V�����̌�
  char *data_;         // �A�j���[�V�����f�[�^�̖��O(�摜)
}ANIM_DATA;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �A�j���[�V�����f�[�^
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const ANIM_DATA s_AnimaitionData[] = {
  // �A�j���[�V�����̐؂�ւ�鎞��  // �A�j���[�V�����̊J�n�ԍ�  // �A�j���[�V�����̌�  // �e�N�X�`���̖��O
  { 0, 0, 0, "data/Texture/tex_anim_00.png" },                    // �E���G���A�j���[�V��������
  { 5, 4, 4, "data/Texture/tex_anim_00.png" },                    // �E���G���j���[�g����
  { 5, 8, 16, "data/Texture/tex_anim_00.png" },                   // �E���G���n�C�n�C
  { 5, 8, 16, "data/Texture/tex_anim_00.png" },                   // �E���G���W�����v
  { 2, 4, 8, "data/Texture/tex_anim_02.png" },                    // �E���G���\��
  { 5, 12, 4, "data/Texture/tex_anim_02.png" },                   // �E���G������
  { 3, 0, 4, "data/Texture/tex_anim_02.png" },                    // �E���G���n�C�n�C(�`���[�W)
  { 5, 0, 4, "data/Texture/tex_anim_02.png" },                    // �E���G���W�����v(�`���[�W)
  { 30, 8, 16, "data/Texture/tex_anim_00.png" },                  // �E���G����](�S�[�����̉��o)
  { 0, 0, 0, "data/Texture/tex_anim_00.png" },                    // �K���K���A�j���[�V��������
  { 0, 0, 0, "data/Texture/tex_anim_03.png" },                    // �{�[���A�j���[�V����
  { 0, 0, 0, "data/Texture/tex_anim_04.png" },                    // �M�~�b�N
  { 2, 0, 4, "data/Texture/tex_anim_00.png" },                    // �K���K����U��
  { 0, 0, 0, "data/Texture/tex_anim_01.png" },                    // ���A�j���[�V��������
  { 0, 1, 0, "data/Texture/tex_anim_01.png" },                    // �����
  { 15, 2, 2, "data/Texture/tex_anim_01.png" },                   // ������֔��
};

bool TextureAnimation::texture_load_ = false;
int TextureAnimation::texture_id_data_[ANIMATION_MAX];

//==============================================================================
// class implementation
//==============================================================================
// ctor
TextureAnimation::TextureAnimation(){
  texture_uv_ = D3DXVECTOR2(0.0f, 0.0f);
  animation_ = ANIMATION_NONE;
  animation_number_ = 0;
  timer_ = 0;
  animation_end_flag_ = false;

  if (!texture_load_){
    for (int i = 0; i < ANIMATION_MAX; ++i){
      texture_id_data_[i] = -1;
    }
    TextureLoad();
    texture_load_ = true;
  }
}

// dtor
TextureAnimation::~TextureAnimation(){
}

//=============================================================================
// �A�j���[�V�����̍X�V
//-----------------------------------------------------------------------------
void TextureAnimation::UpdateAnimation(void){
  ++timer_;
  animation_end_flag_ = false;

  if (timer_ >= s_AnimaitionData[animation_].time_ &&
      s_AnimaitionData[animation_].time_ != 0){
    timer_ = 0;
    ++animation_number_;

    int number_ = s_AnimaitionData[animation_].number_ + s_AnimaitionData[animation_].start_number_;
    number_ = number_ > DIVISION_NUMBER_X * DIVISION_NUMBER_Y ? 16 : number_;

    if (animation_number_ >= number_){
      animation_number_ = s_AnimaitionData[animation_].start_number_;
      animation_end_flag_ = true;
    }

    float uv_x_ = (animation_number_ % (int)DIVISION_NUMBER_X) / DIVISION_NUMBER_X;
    float uv_x_offset_ = 1 / DIVISION_NUMBER_X;

    float uv_y_ = (int)animation_number_ / (int)DIVISION_NUMBER_Y / DIVISION_NUMBER_Y;
    float uv_y_offset_ = 1 / DIVISION_NUMBER_Y;

    texture_uv_.x = uv_x_;
    texture_uv_.y = uv_y_;
  }
}

//=============================================================================
// �A�j���[�V�����̐ݒ�
//-----------------------------------------------------------------------------
int TextureAnimation::SetAnimation(ANIMATION_EVENT animation_event){
  animation_ = animation_event;
  timer_ = 0;
  animation_number_ = s_AnimaitionData[animation_].start_number_;

  float uv_x_ = (animation_number_ % (int)DIVISION_NUMBER_X) / DIVISION_NUMBER_X;
  float uv_x_offset_ = 1 / DIVISION_NUMBER_X;

  float uv_y_ = (int)animation_number_ / (int)DIVISION_NUMBER_Y / DIVISION_NUMBER_Y;
  float uv_y_offset_ = 1 / DIVISION_NUMBER_Y;

  texture_uv_.x = uv_x_;
  texture_uv_.y = uv_y_;

  animation_number_ = s_AnimaitionData[animation_].start_number_;

  return texture_id_data_[animation_event];
}

//=============================================================================
// �A�j���[�V�������Ԃ̎擾
//-----------------------------------------------------------------------------
int TextureAnimation::GetAnimationChangeTime(void){
  return s_AnimaitionData[animation_].time_;
}

//=============================================================================
// ���̃A�j���[�V���������Ԏ擾
//-----------------------------------------------------------------------------
int TextureAnimation::GetAnimationTime(void){
  return s_AnimaitionData[animation_].time_ * s_AnimaitionData[animation_].number_;
}

//=============================================================================
// �e�N�X�`���[���[�h
//-----------------------------------------------------------------------------
void TextureAnimation::TextureLoad(void){
  for (int i = 0; i < ANIMATION_MAX; ++i){
    bool load = false;
    for (int cnt = 0; cnt < i; ++cnt){
      int name_len = 0;
      char* name_cpy = s_AnimaitionData[i].data_;
      while (*name_cpy++ != '\0'){
        ++name_len;
      }
      if (strncmp(s_AnimaitionData[cnt].data_,s_AnimaitionData[i].data_,name_len) == 0){
        texture_id_data_[i] = texture_id_data_[cnt];
        load = true;
        break;
      }
    }
    if (!load){
      texture_id_data_[i] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(s_AnimaitionData[i].data_);
    }
  }
}

// EOF