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

//******************************************************************************
// クラス定義
//******************************************************************************
class Char;
class GameCursor;
class TitleWindow{
    // enum ======================================
public:
    // modemanaged
    typedef enum{
        STAGE_SELECT = 0,
        TUTORIAL ,
        MAX
    }Title_Char;

public:
    // ctor/dtor
    TitleWindow();
    virtual ~TitleWindow();

    // method
    void Update(SceneManager* p_scene_manager, const float elapsed_time);
    void Draw(void);

    // get
    GameCursor* GetGameCursor(void){ return p_game_cursor_; }

    // set

private:
    Char** p_char_;
    GameCursor* p_game_cursor_;
};

#endif
// EOF