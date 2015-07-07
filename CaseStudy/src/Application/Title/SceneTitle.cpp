//******************************************************************************
//
// SceneTitle  [SceneTitle.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "SceneTitle.h"
#include "Framework\FrameworkOption.h"
#include "Application\Game\SceneGameFactory.h"
//#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"

#include "Framework\Scene\SceneManager.h"
#include "Application\TitleBase\TitleCharBase.h"
#include "Application/Object/Object2D/StartSymbol.h"

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
// �X�V��  :  2015/06/26
//==============================================================================
SceneTitle::SceneTitle()
  : is_end_(false)
  , p_start_symbol_(nullptr)
  , p_object2D(nullptr)
  , p_title_char_base(nullptr){

    p_start_symbol_ = new StartSymbol(D3DXVECTOR3(640.0f, 550.0f, 0.0f), 0.0f, D3DXVECTOR2(256.0f, 100.0f));

    p_object2D = new Object2D(D3DXVECTOR3(kWindowWidth * 0.5f, 380.0f, 0.0f), D3DXVECTOR2(kWindowWidth, 760.0f), "data/Texture/�^�C�g��(��).png");

    p_title_char_base = new TitleCharBase();
}

//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//==============================================================================
SceneTitle::~SceneTitle() {
  SafeDelete(p_start_symbol_);
  SafeDelete(p_object2D);
  SafeDelete(p_title_char_base);
}


//==============================================================================
// �X�V����
// ����    :  SceneManager* p_scene_manager, const float elapsed_time
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//==============================================================================
void SceneTitle::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  p_start_symbol_->Update();

  p_title_char_base->Update();

  // Next TitleScene
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_N)) {
      SceneGameFactory* pGameSceneFactory = new SceneGameFactory();
      p_scene_manager->PushNextSceneFactory(pGameSceneFactory);
  }
}


//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/26
//==============================================================================
void SceneTitle::Draw(void) {
    p_object2D->Draw();

    p_title_char_base->Draw();

    p_start_symbol_->Draw();
}



// EOF