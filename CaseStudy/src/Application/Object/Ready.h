//==============================================================================
//
// Ready
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
class Ready : public Object2D {
public:
  // ctor
  Ready();

  // dtor
  ~Ready();

  // Update
  virtual void Update(void);

  // Draw
  virtual void _PreProcessOfDraw(void);
  virtual void _PostProcessOfDraw(void);

  // get
  bool IsEnd(void) const { return is_end_; }

private:
  static const int kTextureAnimationMax = 2;

  int count_;
  int texture_ids_[kTextureAnimationMax];
  bool is_end_;
};
