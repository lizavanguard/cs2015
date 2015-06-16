//==============================================================================
//
// Object2D
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/ObjectBase.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2D : public ObjectBase {
public:
  // ctor
  Object2D();

  // dtor
  ~Object2D();

protected:
  // �`��̑O�㏈��
  virtual void _PreProcessOfDraw(void) = 0;
  virtual void _PostProcessOfDraw(void) = 0;

private:
  void _Draw(void);
};
