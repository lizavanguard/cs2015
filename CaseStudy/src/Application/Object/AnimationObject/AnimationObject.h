//==============================================================================
//
// �A�j���[�V�����I�u�W�F�N�g [AnimationObject.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_ANIMATION_OBJECT_H__
#define __H_ANIMATION_OBJECT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "../Object.h"
#include "TextureAnimation.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class AnimationObject : public Object {
public:

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // �񋓑̒�`
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  typedef enum {
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
  }DIRECTION;

  typedef enum{
    ANIM_OBJ_TYPE_NONE = 0,
    ANIM_OBJ_TYPE_BUTTERFLY,
    ANIM_OBJ_TYPE_FLOWER,
    ANIM_OBJ_TYPE_PLAYER,
    ANIM_OBJ_TYPE_URIEL,
    ANIM_OBJ_TYPE_MAX
  }ANIM_OBJ_TYPE;

  // ctor
  AnimationObject(ANIMATION_EVENT animation_event);

  // dtor
  virtual ~AnimationObject();

  static AnimationObject* Create(ANIMATION_EVENT animation_event, const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

  // draw
  virtual void _PreProcessOfDraw(void);
  virtual void _PostProcessOfDraw(void);

  virtual void Update(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // set
  virtual void SetPos(const D3DXVECTOR3& pos){ pos_ = pos; }
  void SetAnimaton(ANIMATION_EVENT animation_event);

  // get
  D3DXVECTOR3 GetPos(void){ return pos_; }
  virtual DIRECTION GetDirection(void){ return move_direction_; }

  // �I�u�W�F�N�g�Ǘ��p
  void SetPrevAnimationObject(AnimationObject* prev){ animation_object_prev_ = prev; }
  void SetNextAnimationObject(AnimationObject* next){ animation_object_next_ = next; }
  AnimationObject* GetPrevAnimationObject(void){ return animation_object_prev_; }
  AnimationObject* GetNextAnimationObject(void){ return animation_object_next_; }
  // �I�u�W�F�^�C�v���ʗp
  void SetAnimObjType(ANIM_OBJ_TYPE anim_obj_type){ anim_obj_type_ = anim_obj_type; }
  ANIM_OBJ_TYPE GetAnimObjType(void){ return anim_obj_type_; }

protected:
  TextureAnimation *p_texture_animation_;
  DIRECTION move_direction_;

private:
  // �I�u�W�F�N�g�Ǘ��p
  AnimationObject* animation_object_prev_;
  AnimationObject* animation_object_next_;
  // �I�u�W�F�^�C�v���ʗp
  ANIM_OBJ_TYPE anim_obj_type_;
};


#endif // __H_ANIMATION_OBJECT_H__
