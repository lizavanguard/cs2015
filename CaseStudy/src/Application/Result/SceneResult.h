//******************************************************************************
//
// SceneResult  [SceneResult.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/Scene/Scene.h"

//******************************************************************************
// �N���X��`
//******************************************************************************
class ResultTime;
class StartSymbol;
class Object2D;
class BackGroundManager;
class SceneResult : public Scene {
public:
    // ctor/dtor
    SceneResult();
    virtual ~SceneResult();

    // method
    void Update(SceneManager* pSceneManager, float elapsedTime) override;
    void Draw(void) override;

    // set
    void End(void) { is_end_ = true; }

private:
    // property
    bool is_end_;
    ResultTime* p_result_time;
    StartSymbol* p_start_symbol_;
	BackGroundManager* p_background_manager_;
    Object2D* p_object2D;
};

#endif
// EOF