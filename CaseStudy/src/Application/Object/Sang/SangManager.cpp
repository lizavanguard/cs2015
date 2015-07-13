//==============================================================================
//
// 障害物管理クラス [SangManager.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SangManager.h"
#include "Application/Object/AnimationObject/AnimationObject.h"
#include "Application/Object/Uriel.h"

AnimationObject* SangManager::sang_object_top_ = nullptr;
AnimationObject* SangManager::sang_object_cur_ = nullptr;

//==============================================================================
// class implementation
//==============================================================================
// ctor
SangManager::SangManager(){
  sang_object_top_ = nullptr;
  sang_object_cur_ = nullptr;
}

// dtor
SangManager::~SangManager() {
  AnimationObject* list = sang_object_top_;
  AnimationObject* list_next = nullptr;

  while (list){
    list_next = list->GetNextAnimationObject();
    if (list_next == nullptr){
      SafeDelete(list);
      return;
    }
    SafeDelete(list);
    list = list_next;
  }
}

// update
void SangManager::Update(void){
  AnimationObject* list = sang_object_top_;

  D3DXVECTOR3 pos, near_pos, uriel_pos;
  AnimationObject::ANIM_OBJ_TYPE anim_obj_type = AnimationObject::ANIM_OBJ_TYPE_NONE;
  AnimationObject::DIRECTION direction = AnimationObject::DIRECTION_RIGHT;
  AnimationObject* sang = nullptr;
  uriel_pos = p_uriel_->GetPos();
  near_pos = D3DXVECTOR3(0,0,0);
  while (list){
    float answer_length,near_length = 500.0f;
    pos = list -> GetPos();
    answer_length = abs(pos.x - uriel_pos.x);
    if (answer_length < kSetSangViewLength){
      if (answer_length < near_length){
        near_pos = pos;
        near_length = answer_length;
        anim_obj_type = list->GetAnimObjType();
        direction = list->GetDirection();
        sang = list;
      }
    }
    list = list -> GetNextAnimationObject();
  }

  p_uriel_->SetDestPos(near_pos, anim_obj_type, direction, sang);

  list = sang_object_top_;

  while (list){
    list -> Update();
    list = list -> GetNextAnimationObject();
  }
}

// draw
void SangManager::Draw(void){
  AnimationObject* list = sang_object_top_;

  while (list){
    list -> Draw();
    list = list -> GetNextAnimationObject();
  }
}

// AddTo
void SangManager::AddToSang(AnimationObject* sang, AnimationObject::ANIM_OBJ_TYPE anim_obj_type){
  if (sang_object_top_ == nullptr){
    sang_object_top_ = sang;
    sang_object_cur_ = sang;
    sang->SetPrevAnimationObject(nullptr);
    sang->SetNextAnimationObject(nullptr);
  } else {
    sang_object_cur_->SetNextAnimationObject(sang);
    sang->SetPrevAnimationObject(sang_object_cur_);
    sang_object_cur_ = sang;
    sang->SetNextAnimationObject(nullptr);
  }

  // アニメーションオブジェクトタイプ設定
  sang->SetAnimObjType(anim_obj_type);
}

// EOF