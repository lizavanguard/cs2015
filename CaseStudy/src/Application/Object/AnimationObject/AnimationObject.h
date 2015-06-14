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

  // ctor
  AnimationObject(ANIMATION_EVENT animation_event);

  // dtor
  virtual ~AnimationObject();

  static AnimationObject* Create(ANIMATION_EVENT animation_event, const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

  // draw
  virtual void PreProccessOfDraw(void);
  virtual void PostProcessOfDraw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos);
  void AddPosX(float x);

  // set
  void SetAnimaton(ANIMATION_EVENT animation_event);

protected:
  TextureAnimation *p_texture_animation_;
  DIRECTION move_direction_;
};


#endif // __H_ANIMATION_OBJECT_H__
