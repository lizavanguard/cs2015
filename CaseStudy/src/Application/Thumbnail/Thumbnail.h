//==============================================================================
//
// Thumbnail
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
class Thumbnail : public Object2D {
public:
  // ctor
  Thumbnail(const D3DXVECTOR3& position, const D3DXVECTOR2& size, const char* p_texture_filename);

  // dtor
  ~Thumbnail();

  // Update
  void Update(float elpased_time);

  // Activate
  void Activate(void);

  // Deactivate
  void Deactivate(void);

  // get
  bool IsActive(void) const { return is_active_; }

private:
  bool is_active_;
};
