//******************************************************************************
//
// GamePauseWindow  [GamePauseWindow.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _GAMEPAUSEWINDOW_H_
#define _GAMEPAUSEWINDOW_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/Scene/SceneManager.h"
#include "GamePause.h"

//******************************************************************************
// クラス定義
//******************************************************************************
class WindowBack;
class Char;
class Object2D;
class GameCursor;
class GamePauseWindow{
    // enum ======================================
public:
    // modemanaged
    typedef enum{
        GAMESCENE_BACK = 0,
        RETRY ,
        STAGE_SELECT ,
        TITLESCENE_BACK ,
        MAX
    }PAUSE_CHAR;

public:
    // ctor/dtor
    GamePauseWindow();
    virtual ~GamePauseWindow();

    // method
    void Update(SceneManager* p_scene_manager, const float elapsed_time ,GamePause* p_game_pause_);
    void Draw(void);

    // get
    GameCursor* GetGameCursor(void){ return p_game_cursor_; }

    // set

private:
    WindowBack* p_window_back_;
    Char** p_char_;
    Object2D* p_object2D_;
    GameCursor* p_game_cursor_;
};

#endif
// EOF