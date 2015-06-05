//==============================================================================
//
// ThreadingModel Policy [ThreadingModel.hpp]
// Created : Shimizu Shoji
// MEMO:
// �X���b�h�����̓�����K��
// �v����`)
// [internal class] Lock: ���b�N�Z�}���e�B�N�X�����S�ɍs��
// [alias] VolatileType: MT�󋵉��ɓK�������邩�AST�ł̍œK����}�邩���w�肷��
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
// ST�Ȃ̂ł��邱�Ƃ͂Ȃ�
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
// �N���X���x���̃��b�N
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
//// �C���X�^���X���x���̃��b�N
//// mutex_ = CreateMutex( nullptr, FALSE, name_.c_str() );
//// CloseHnadle
//// �ǂ���Create���Ăǂ���Close����̂�
//// ���̍ۂɕ�����̈����͂ǂ��Ȃ�̂��H
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