//==============================================================================
//
// SingletonHolder [SingletonHolder.hpp]
// Created : Shimizu Shoji
// �|���V�[
// 1.Creation: �C���X�^���X�������� �ʏ��new������ŗp������
// 2.Lifetime:
//  (a) C++�̋K���ɏ]��(�Ō�ɐ������ꂽ���̂��ŏ��ɔj�������=static)
//  (b) ��������(Phoenix Singleton)
//  (c) ���[�U����ł���(�������w�肷��)
//  (d) ����(���[�N����A�I�u�W�F�N�g�͔j������Ȃ�)
// 3.ThreadingModel: ST, MT(Mutex��Double-Checked Locking��p����), �����̂Ȃ��X���b�h�E���f��
//
// �N���C�A���g�͈ȏ��3�̃|���V�[��C�ӂɑg�ݍ��킹�A���R�x�̍���Singleton�R���e�i���\�z�ł���
// �܂�A�i�[�ΏۃN���X��3�̃|���V�[�̌v4�̃e���v���[�g��g�ݍ��킹�Ďg�p����
// �܂��A�i�[�ΏۃN���X�ł́A�R���X�g���N�^�A�f�X�g���N�^�A�R�s�[�R���X�g���N�^����ё�����Z�q��
// ����J�ɂ��邱�ƂŁA�����S�ɉ^�p�ł���
//
//==============================================================================
#pragma once
#ifndef __HPP_LIZAGENERICSINGLETONHOLDER_HPP__
#define __HPP_LIZAGENERICSINGLETONHOLDER_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <assert.h>
#include <stdexcept>	// for logic_error

// policy
#include "Creation.hpp"
#include "Lifetime.hpp"
#include "ThreadingModel.hpp"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace generic {

//------------------------------------------------
// SingletonHolder
//------------------------------------------------
template<
	class T,
	template<class> class CreationPolicy = CreateUsingNew,
	template<class> class LifetimePolicy = DefaultLifetime,
	template<class> class ThreadingModel = SingleThreaded
>
class SingletonHolder {
public:
	// alias
	typedef typename ThreadingModel<T>::VolatileType InstanceType;

public:
	// method
	static T& Instance( void );

private:
	// helper
	static void DestroySingleton( void );

	// protection
	SingletonHolder();
	SingletonHolder( const SingletonHolder& );
	SingletonHolder& operator=( const SingletonHolder& );
	~SingletonHolder();

	// property
	static InstanceType* pInstance_;
	static bool destroyed_;
};


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
template<
	class T,
	template<class> class CreationPolicy,
	template<class> class LifetimePolicy,
	template<class> class ThreadingModel
>
typename SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::InstanceType*
SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::pInstance_ = nullptr;

template<
	class T,
	template<class> class CreationPolicy,
	template<class> class LifetimePolicy,
	template<class> class ThreadingModel
>
bool SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::destroyed_ = false;


//------------------------------------------------
// Instance
//------------------------------------------------
template<
	class T,
	template<class> class CreationPolicy,
	template<class> class LifetimePolicy,
	template<class> class ThreadingModel
>
T& SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::Instance( void ) {
	// if ��������Ă��Ȃ�������
	if( !pInstance_ ) {
		// ���b�N
		typename ThreadingModel<T>::Lock guard;
		// if �܂���������Ă��Ȃ�������(Double-Checked Locking)
		if( !pInstance_ ) {
			// if �j��ς݂Ȃ�����Ǘ��ɔC����
			if( destroyed_ ) {
				LifetimePolicy<T>::OnDeadReference();
				destroyed_ = false;
			}

			// ����
			pInstance_ = CreationPolicy<T>::Create();
			// �����Ǘ��̍Đݒ�
			LifetimePolicy<T>::ScheduleDestruction( &DestroySingleton );
		}
	}
	return *pInstance_;
}


//------------------------------------------------
// Destroy singleton instance
//------------------------------------------------
template<
	class T,
	template<class> class CreationPolicy,
	template<class> class LifetimePolicy,
	template<class> class ThreadingModel
>
void SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::DestroySingleton( void ) {
	assert( !destroyed_ );
	CreationPolicy<T>::Destroy( pInstance_ );
	pInstance_ = nullptr;
	destroyed_ = true;
}

	} // namespace generic
} // namespace liza


#endif // __HPP_LIZAGENERICSINGLETONHOLDER_HPP__