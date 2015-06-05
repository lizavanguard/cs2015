//==============================================================================
//
// SceneGameFactory [SceneGameFactory.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#pragma warning( disable : 4481 )
#ifndef __H_SCENEGAMEFACTORY_H__
#define __H_SCENEGAMEFACTORY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Scene/SceneFactory.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneGame;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneGameFactory : public SceneFactory {
public:
  // ctor/dtor
  SceneGameFactory();
  virtual ~SceneGameFactory();

  // method
  Scene* Create(void) override;

private:
  // property
};


#endif // __H_SCENEGAMEFACTORY_H__