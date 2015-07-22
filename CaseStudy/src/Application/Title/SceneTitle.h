//******************************************************************************
//
// SceneTitle  [SceneTitle.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/Scene/Scene.h"

//******************************************************************************
// クラス定義
//******************************************************************************
class BackGroundManager;
class StartSymbol;
class TitleCharBase;
class SceneTitle : public Scene {
public:
    // ctor/dtor
    SceneTitle();
    virtual ~SceneTitle();

    // method
    void Update(SceneManager* pSceneManager, float elapsedTime) override;
    void Draw(void) override;

    // set
    void End(void) { is_end_ = true; }

private:
    // property
    bool is_end_;
    TitleCharBase* p_title_char_base;
    StartSymbol* p_start_symbol_;
    BackGroundManager* p_background_manager_;
};

#endif
// EOF