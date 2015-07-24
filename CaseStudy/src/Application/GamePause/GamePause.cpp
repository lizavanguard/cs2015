//******************************************************************************
//
// GamePause  [GamePause.cpp]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "GamePause.h"
#include "Framework/FrameworkOption.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/Game/SceneGameFactory.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputXInput.h"

#include "Application/GamePause/GamePauseWindow.h"

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �O���[�o���錾
//******************************************************************************


//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//==============================================================================
GamePause::GamePause()
  : is_end_(false)
  , is_pause_(false)
  , p_game_pause_window_(nullptr){

    p_game_pause_window_ = new GamePauseWindow;
}

//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//==============================================================================
GamePause::~GamePause() {
    SafeDelete(p_game_pause_window_);
}


//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//==============================================================================
void GamePause::Update(SceneManager* p_scene_manager, const float elapsed_time, GamePause* p_game_pause_) {
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  // �^�C�g���E�X�e�[�W�Z���N�g�E���g���C�E�߂�
  if (is_pause_){
      p_game_pause_window_->Update(p_scene_manager, elapsed_time, p_game_pause_);
    // Next TitleScene
  }
  if (pJoypad.IsTrigger(InputDevice::Pads::PAD_START) || InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_P)) {
      if (is_pause_)
        SetPause(false);
      else
        SetPause(true);
  }
}


//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/07
//==============================================================================
void GamePause::Draw(void) {
  if (is_pause_){
      p_game_pause_window_->Draw();
  }
}



// EOF