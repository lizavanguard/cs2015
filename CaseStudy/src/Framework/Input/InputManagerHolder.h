//==============================================================================
//
// インプットマネージャホルダー [InputManagerHolder.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_INPUTMANAGERHOLDER_H__
#define __H_INPUTMANAGERHOLDER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Input/InputManager.h"
#include "Framework/Utility/SingletonHolder.hpp"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _InputManagerHolder {
public:
  // ctor
  _InputManagerHolder() {}

  // dtor
  ~_InputManagerHolder() {}

  // get
  const InputManager& GetInputManager(void) const { return *pInputManager_; }

  // set
  void SetInputManager(InputManager* pInputManager) { pInputManager_ = pInputManager; }

private:
  InputManager* pInputManager_;
};

// singleton
typedef liza::generic::SingletonHolder<_InputManagerHolder> InputManagerHolder;


#endif // __H_INPUTMANAGERHOLDER_H__
