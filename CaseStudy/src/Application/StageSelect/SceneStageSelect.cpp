//==============================================================================
//
// SceneStageSelect
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneStageSelect.h"

#include "Application/Object/Object2D/Object2D.h"

// HACK:
Object2D* p_object = nullptr;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTextureFilename = "data/Texture/bo-ro.png";

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneStageSelect::SceneStageSelect() {
  p_object = new Object2D(D3DXVECTOR3(100, 100, 0), D3DXVECTOR2(100, 100), kTextureFilename);
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneStageSelect::~SceneStageSelect() {
  SafeDelete(p_object);
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneStageSelect::Update(SceneManager* pSceneManager, float elapsedTime) {

}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneStageSelect::Draw(void) {
  p_object->Draw();
}
