//==============================================================================
//
// ValueClampingAndWrapping
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ValueClampingAndWrapping {
public:
  // ctor
  ValueClampingAndWrapping(float min, float max);

  // dtor
  ~ValueClampingAndWrapping();

  // Clamp
  float Clamp(float value);

  // Wrap
  float Wrap(float value);

private:
  float min_;
  float max_;
};
