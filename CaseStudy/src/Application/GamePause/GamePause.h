//******************************************************************************
//
// GamePause  [GamePause.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/Scene/SceneManager.h"

//******************************************************************************
// クラス定義
//******************************************************************************
class GamePauseWindow;
class GamePause{
public:
    // ctor/dtor
    GamePause();
    virtual ~GamePause();

    // method
    void Update(SceneManager* p_scene_manager, const float elapsed_time, GamePause* p_game_pause_);
    void Draw(void);

    // set
    void End(void) { is_end_ = true; }
    void SetPause(bool pause){ is_pause_ = pause; }
    // get
    bool GetPause(void){ return is_pause_; }

private:
    // property
    bool is_end_;
    bool is_pause_;

    GamePauseWindow* p_game_pause_window_;
};

#endif
// EOF