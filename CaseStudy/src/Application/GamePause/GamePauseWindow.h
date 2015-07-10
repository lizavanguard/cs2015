//******************************************************************************
//
// GamePauseWindow  [GamePauseWindow.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _GAMEPAUSEWINDOW_H_
#define _GAMEPAUSEWINDOW_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/Scene/SceneManager.h"
#include "GamePause.h"

//******************************************************************************
// �N���X��`
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