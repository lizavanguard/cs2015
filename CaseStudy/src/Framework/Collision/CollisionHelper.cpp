//==============================================================================
//
// CollisionHelper
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "CollisionHelper.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// prototype
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//------------------------------------------------
// 2�_�Ԃ̋�����2���Ԃ�[2D]
// ���Z�ƌ��Z���o���邱�Ƃ��Öق̌^����
//------------------------------------------------
template<typename T>
T CalcDist2(const T& ax, const T& ay, const T& bx, const T& by);

//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// ��x���̏Փ˔���[2D]
//------------------------------------------------
bool IsSphereHit2(const float ax, const float ay, const float ar,
                  const float bx, const float by, const float br) {
  const float length = CalcDist2(ax, ay, bx, by);
  return (ar + br) * (ar + br) > length;
}

//==============================================================================
// internal function implementation
//==============================================================================
//------------------------------------------------
// 2�_�Ԃ̋�����2���Ԃ�[2D]
// ���Z�ƌ��Z���o���邱�Ƃ��Öق̌^����
//------------------------------------------------
template<typename T>
T CalcDist2(const T& ax, const T& ay, const T& bx, const T& by) {
  const T dx = (ax - bx) * (ax - bx);
  const T dy = (ay - by) * (ay - by);
  return dx + dy;
}