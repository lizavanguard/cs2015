//==============================================================================
//
// ThreadingModel Policy [ThreadingModel.hpp]
// Created : Shimizu Shoji
// MEMO:
// スレッド環境時の動作を規定
// 要件定義)
// [internal class] Lock: ロックセマンティクスを安全に行う
// [alias] VolatileType: MT状況下に適応させるか、STでの最適化を図るかを指定する
//
//==============================================================================
#pragma once
#ifndef __HPP_LIZAGENERICTHREADINGMODEL_HPP__
#define __HPP_LIZAGENERICTHREADINGMODEL_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "MutexCreator.h"
#include "Mutex.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace generic {

//------------------------------------------------
// STなのですることはない
//------------------------------------------------
template<typename T>
class SingleThreaded {
public:
	// internal class
	class Lock {
	public:
		Lock() {}
		Lock( T& rhs ) {}
	};

	class ReadLock {
	public:
		ReadLock() {}
		ReadLock( T& rhs ) {}
	};

	// alias
	typedef T VolatileType;

};


//------------------------------------------------
// クラスレベルのロック
//------------------------------------------------
template<typename T>
struct ClassLevelLockable {
public:
	// internal class
	class Lock {
	public:
		// ctor/dtor
		Lock() : spMutex_( nullptr ) { _Lock(); }
		Lock( T& rhs )  : spMutex_( nullptr ) { _Lock(); }
		~Lock() { spMutex_ = nullptr; }

	private:
		// method
		void _Lock( void ) {
			spMutex_ = mutexCreator_.Create();
			spMutex_->Lock();
		}

		// property
		std::shared_ptr<liza::Mutex> spMutex_;
	};

	//alias
	typedef T VolatileType;

private:
	// property
	static MutexCreator mutexCreator_;
};

template<typename T>
liza::MutexCreator ClassLevelLockable<T>::mutexCreator_;


////------------------------------------------------
//// インスタンスレベルのロック
//// mutex_ = CreateMutex( nullptr, FALSE, name_.c_str() );
//// CloseHnadle
//// どこでCreateしてどこでCloseするのか
//// その際に文字列の扱いはどうなるのか？
////------------------------------------------------
//template<typename T>
//struct InstanceLevelLockable {
//public:
//	class Lock {
//	public:
//		Lock() { _Lock(); }
//		Lock( T& rhs ) { _Lock(); }
//		~Lock() {
//			ReleaseMutex( handle_ );
//		}
//
//	private:
//		// method
//		void _Lock( void ) {
//			handle_ = OpenMutex( MUTEX_ALL_ACCESS, FALSE, name_.c_str() );
//			WaitForSingleObject( handle_, INFINITE );
//		}
//
//		// property
//		HANDLE handle_;
//	};
//
//	class ReadLock {
//	};
//
//private:
//	HANDLE mutex_;
//	static std::string name_;
//};


	} // namespace generic
} // namespace liza


#endif // __HPP_LIZAGENERICTHREADINGMODEL_HPP__