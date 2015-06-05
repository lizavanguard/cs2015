//==============================================================================
//
// Lifetime Policy [Lifetime.hpp]
// Created : Shimizu Shoji
// MEMO:
// �C���X�^���X�̔j�����X�P�W���[�����O����\��(�����Ǘ�)
// �C���X�^���X�̎����̋K���Ɉᔽ�����ۂ̓���̋K��
// �v����`)
// [static method] void ScheduleDestruction( void (*)( void ) ): �j���^�C�~���O�̊Ǘ�
// [static method] void OnDeadReference( void ): ���񂾃C���X�^���X�ւ̎Q�Ǝ��̓���
//==============================================================================
#pragma once
#ifndef __HPP_LIZAGENERICLIFETIME_HPP__
#define __HPP_LIZAGENERICLIFETIME_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace generic {

//------------------------------------------------
// C++�̋K���ɂ��������Ď������Ǘ�����
// ��Ƃ̊����̂��߂�atexit���g�p
//------------------------------------------------
template<typename T>
struct DefaultLifetime {

	static void ScheduleDestruction( void (*fpDestroy)( void ) ) {
		atexit( fpDestroy );
	}

	static void OnDeadReference( void ) {
		throw std::logic_error( "Access On DeadReference" );
	}

};


//------------------------------------------------
// �C���X�^���X�̍Đ������\
//------------------------------------------------
template<typename T>
struct PhoenixSingleton {

	static void ScheduleDestruction( void (*fpDestroy)( void ) ) {
		atexit( fpDestroy );
	}

	static void OnDeadReference( void ) {
		__noop;
	}

};


//------------------------------------------------
// �N���C�A���g���������w��
// ����̎����Ԃł�C++�̋K���ɏ]���Ĕj�������(LIFO)
//------------------------------------------------
template<typename T>
struct SingletonWithLongevity {

	static void ScheduleDestruction( void (*fpDestroy)( void ) ) {
		// TODO:
		aa;
	}

	static void OnDeadReference( void ) {
		throw std::logic_error( "Access On DeadReference" );
	}

};



//------------------------------------------------
// �j�����Ȃ�
// ���[�N����
//------------------------------------------------
template<typename T>
struct NoDestroy {

	static void ScheduleDestruction( void (*fpDestroy)( void ) ) {
		(void)fpDestroy;
	}

	static void OnDeadReference( void ) {
		throw std::logic_error( "Access On DeadReference" );
	}

};

	} // namespace generic
} // namespace liza


#endif // __HPP_LIZAGENERICLIFETIME_HPP__