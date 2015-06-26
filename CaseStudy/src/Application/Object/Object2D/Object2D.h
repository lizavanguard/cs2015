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
  Object2D(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const char* p_texture_filename);

  // dtor
  ~Object2D();

protected:
  // ï`âÊÇÃëOå„èàóù
  void _PreProcessOfDraw(void) override {};
  void _PostProcessOfDraw(void) override {};

private:
  void _Draw(void);
};
