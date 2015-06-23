//==============================================================================
//
// BackGround
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/Object.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class BackGround : public Object {
public:
  // ctor
  BackGround(const char* p_filename, float speed_u);

  // dtor
  ~BackGround();

  // Update
  virtual void Update(void);

protected:
  // Draw
  virtual void _PreProcessOfDraw(void);
  virtual void _PostProcessOfDraw(void);
private:
  float speed_u_;
};
