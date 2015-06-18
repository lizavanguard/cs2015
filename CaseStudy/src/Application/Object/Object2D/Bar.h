//==============================================================================
//
// Bar
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
class Bar : public Object2D {
public:
  // ctor
  Bar(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, float max_value);

  // update value
  void UpdateValue(float value);

protected:
  // DrawÇÃëOå„èàóù
  void _PreProcessOfDraw(void) override;
  void _PostProcessOfDraw(void) override;

private:
  void _UpdatePosAndSize(float rate);

  float max_value_;
  D3DXVECTOR3 original_position_;
  D3DXVECTOR2 original_size_;
};
