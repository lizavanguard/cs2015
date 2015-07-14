//******************************************************************************
//
// GamePause  [GamePause.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/Scene/SceneManager.h"

//******************************************************************************
// �N���X��`
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