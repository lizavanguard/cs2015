//******************************************************************************
//
// SceneResultFactory  [SceneResultFactory.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _SCENERESULTFACTORY_H_
#define _SCENERESULTFACTORY_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/Scene/SceneFactory.h"

//******************************************************************************
// �N���X��`
//******************************************************************************
class SceneResultFactory : public SceneFactory {
public:
    // ctor/dtor
    SceneResultFactory();
    virtual ~SceneResultFactory();

    // method
    Scene* Create(void) override;

private:
    // property
};

#endif
// EOF