//==============================================================================
//
// デバイスホルダー [DeviceHolder.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_DEVICEHOLDER_H__
#define __H_DEVICEHOLDER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Utility/SingletonHolder.hpp"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DeviceHolder {
public:
  // ctor
  _DeviceHolder() {}

  // dtor
  ~_DeviceHolder() {}

  // get
  LPDIRECT3DDEVICE9 GetDevice(void) const { return pDevice_; }

  // set
  void SetDevice(LPDIRECT3DDEVICE9 pDevice) { pDevice_ = pDevice; }

private:
  LPDIRECT3DDEVICE9 pDevice_;
};

// singleton
typedef liza::generic::SingletonHolder<_DeviceHolder> DeviceHolder;


#endif // __H_DEVICEHOLDER_H__
