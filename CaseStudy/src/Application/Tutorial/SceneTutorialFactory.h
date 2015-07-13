//==============================================================================
//
// SceneTutorialFactory [SceneTutorialFactory.h]
// Author : Yujimomoi
//
//==============================================================================
#pragma once
#pragma warning( disable : 4481 )
#ifndef __H_SCENETUTORIALFACTORY_H__
#define __H_SCENETUTORIALFACTORY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Scene/SceneFactory.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneTutorial;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneTutorialFactory : public SceneFactory {
public:
  // ctor/dtor
  SceneTutorialFactory();
  virtual ~SceneTutorialFactory();

  // method
  Scene* Create(void) override;

private:
  // property
};


#endif // __H_SCENEGAMEFACTORY_H__