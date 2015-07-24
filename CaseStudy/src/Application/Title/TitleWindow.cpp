//******************************************************************************
//
// TitleWindow  [TitleWindow.cpp]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/22
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "TitleWindow.h"
#include "Framework\FrameworkOption.h"
#include "Application\Game\SceneGameFactory.h"
#include "Application\Title\SceneTitleFactory.h"
#include "Application\StageSelect\SceneStageSelectFactory.h"
#include "Application\Tutorial\SceneTutorialFactory.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework\Scene\SceneManager.h"
#include "Framework/Input/InputXInput.h"

#include "Application/Object/Object2D/WindowBack.h"
#include "Application\Object\Object2D\Char.h"
#include "Application\GameCursor\GameCursor.h"

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// グローバル宣言
//******************************************************************************
namespace{
    const D3DXVECTOR3 kCharPos[] = { { kWindowWidth * 0.5f, kWindowHeight * 0.5f + 150.0f, 0.0f }, 
                                     { kWindowWidth * 0.5f, kWindowHeight * 0.5f + 270.0f, 0.0f },
                               };
    const D3DXVECTOR2 kCharSize[] = { { 300.0f, 75.0f },
                                    { 300.0f, 75.0f },
                                };
    const D3DXVECTOR3 kBoroPos[] = { { kWindowWidth * 0.5f + 200.0f, kWindowHeight * 0.5f + 150.0f, 0.0f },
                                     { kWindowWidth * 0.5f + 200.0f, kWindowHeight * 0.5f + 270.0f, 0.0f }
                                  };

    const char* kPauseCharTextureFileName[] = { { "data/Texture/title_stageSelect.png"} ,
                                                { "data/Texture/title_tutorial.png" },
                                    };

    const D3DXVECTOR2 kCursorSize = { 100.0f, 100.0f };
    const char* kCursorTextureFilename = "data/Texture/bo-ro.png";

    const float kRot = 0.0f;

}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/22
//==============================================================================
TitleWindow::TitleWindow()
    : p_char_(nullptr)
    , p_game_cursor_(nullptr){

    p_char_ = new Char *[MAX];

    for (int i = 0; i < MAX; i++){
        p_char_[i] = new Char(kCharPos[i], kRot, kCharSize[i], kPauseCharTextureFileName[i]);
    }

    GameCursor::PositionContainer position_list;
    for (int thumb_count = 0; thumb_count < MAX; ++thumb_count) {
        position_list.push_back(kBoroPos[thumb_count]);
    }
    p_game_cursor_ = new GameCursor(kCursorSize, DIK_RIGHT, DIK_LEFT, DIK_RETURN, DIK_BACKSPACE, position_list);
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/22
//==============================================================================
TitleWindow::~TitleWindow() {
    for (int i = 0; i < MAX; i++){
        SafeDelete(p_char_[i]);
    }
    SafeDeleteArray(p_char_);
    SafeDelete(p_game_cursor_);
}


//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/22
//==============================================================================
void TitleWindow::Update(SceneManager* p_scene_manager, const float elapsed_time) {
    for (int i = 0; i < MAX; i++){
        p_char_[i]->Update();
    }

    p_game_cursor_->Update(elapsed_time);

    const int index = p_game_cursor_->GetCursorIndex();

    auto& keyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
    auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
    if (keyboard.IsTrigger(DIK_RETURN) || pJoypad.IsTrigger(InputDevice::Pads::PAD_A)) {
        if (index == STAGE_SELECT)
            p_scene_manager->PushNextSceneFactory(new SceneStageSelectFactory());
        else if (index == TUTORIAL)
            p_scene_manager->PushNextSceneFactory(new SceneTutorialFactory());
    }

}


//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/22
//==============================================================================
void TitleWindow::Draw(void) {

    for (int i = 0; i < MAX; i++){
        p_char_[i]->Draw();
    }

    p_game_cursor_->Draw();
}



// EOF