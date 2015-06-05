//==============================================================================
//
// SingletonHolder [SingletonHolder.hpp]
// Created : Shimizu Shoji
// ポリシー
// 1.Creation: インスタンス生成方式 通常はnewを内部で用いられる
// 2.Lifetime:
//  (a) C++の規則に従う(最後に生成されたものが最初に破棄される=static)
//  (b) 復活する(Phoenix Singleton)
//  (c) ユーザ制御できる(寿命を指定する)
//  (d) 無限(リークする、オブジェクトは破棄されない)
// 3.ThreadingModel: ST, MT(MutexとDouble-Checked Lockingを用いる), 可搬性のないスレッド・モデル
//
// クライアントは以上の3つのポリシーを任意に組み合わせ、自由度の高いSingletonコンテナを構築できる
// つまり、格納対象クラスと3つのポリシーの計4つのテンプレートを組み合わせて使用する
// また、格納対象クラスでは、コンストラクタ、デストラクタ、コピーコンストラクタおよび代入演算子を
// 非公開にすることで、より安全に運用できる
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
	// if 生成されていなかったら
	if( !pInstance_ ) {
		// ロック
		typename ThreadingModel<T>::Lock guard;
		// if まだ生成されていなかったら(Double-Checked Locking)
		if( !pInstance_ ) {
			// if 破壊済みなら寿命管理に任せる
			if( destroyed_ ) {
				LifetimePolicy<T>::OnDeadReference();
				destroyed_ = false;
			}

			// 生成
			pInstance_ = CreationPolicy<T>::Create();
			// 寿命管理の再設定
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