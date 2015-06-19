//==============================================================================
//
// オブジェクト [Object.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_OBJECT_H__
#define __H_OBJECT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "ObjectBase.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Object : public ObjectBase {
public:
  // ctor
  Object();

  // dtor
  virtual ~Object();

protected:
  // Drawの前後処理
  virtual void _PreProcessOfDraw(void) = 0;
  virtual void _PostProcessOfDraw(void) = 0;

private:
  virtual void _Draw(void);
};

#endif // __H_OBJECT_H__
