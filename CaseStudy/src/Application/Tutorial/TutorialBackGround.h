//==============================================================================
//
// チュートリアルBG [TutorialBackGround.h]
// Author : Yuji Momoi
//
//==============================================================================
#pragma once
#ifndef __H_TUTORIAL_BACKGROUND_H__
#define __H_TUTORIAL_BACKGROUND_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Application/Object/Object.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TutorialBackGround : public Object {
public:
  // ctor
  TutorialBackGround(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const char* p_texture_filename);

  // dtor
  virtual ~TutorialBackGround();

  // draw
  virtual void _PreProcessOfDraw(void);
  virtual void _PostProcessOfDraw(void);

  virtual void Update(void);

  // set
  virtual void SetPos(const D3DXVECTOR3& pos){ pos_ = pos; }

  // get
  D3DXVECTOR3 GetPos(void){ return pos_; }



private:

};


#endif // __H_TUTORIAL_BACKGROUND_H__
