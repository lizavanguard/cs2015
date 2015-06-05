//==============================================================================
//
// Lifetime Policy [Lifetime.hpp]
// Created : Shimizu Shoji
// MEMO:
// インスタンスの破棄をスケジューリングする能力(寿命管理)
// インスタンスの寿命の規則に違反した際の動作の規定
// 要件定義)
// [static method] void ScheduleDestruction( void (*)( void ) ): 破棄タイミングの管理
// [static method] void OnDeadReference( void ): 死んだインスタンスへの参照時の動作
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
// C++の規則にしたがって寿命を管理する
// 作業の完了のためにatexitを使用
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
// インスタンスの再生成が可能
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
// クライアントが寿命を指定
// 同一の寿命間ではC++の規則に従って破棄される(LIFO)
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
// 破棄しない
// リークする
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