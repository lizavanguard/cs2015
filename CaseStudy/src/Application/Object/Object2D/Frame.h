//==============================================================================
//
// Frame
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/Object2D/Object2D.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Frame : public Object2D {
public:
  // ctor
  Frame(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

protected:
  // DrawÇÃëOå„èàóù
  void _PreProcessOfDraw(void) override;
  void _PostProcessOfDraw(void) override;
};
