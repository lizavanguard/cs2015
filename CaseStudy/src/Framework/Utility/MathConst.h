//==============================================================================
//
// 数学用汎用定数定義 [MathConst.h]
// Created : Shimizu Shoji
//
//==============================================================================
#ifndef __H_LIZAMATHMATHCONST_H__
#define __H_LIZAMATHMATHCONST_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 定数定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace math {

// 円周率PI 3.14159265358979323846264338327950288...
const float  kPIf = 3.14159265f;
const double kPId = 3.141592653589793;
// PI/2 1.57079632679489661923...
const float  kPIHalff = 1.57079632f;
const double kPIHalfd = 1.570796326794896;
// PI/4 0.78539816339744830962...
const float  kPIQuarterf = 0.78539816f;
const double kPIQuarterd = 0.785398163397448;
// 2PI 6.2831853071795864769252...
const float  k2PIf = 6.28318530f;
const double k2PId = 6.283185307179586;

// PIの逆数(1/PI) 0.31830988618379067154...
const float  kReciprocalOfPIf = 0.31830988f;
const double kReciprocalOfPId = 0.318309886183790;
// 2/PI 0.63661977236758134308...
const float  kTwoOverPIf = 0.63661977f;
const double kTwoOverPId = 0.636619772367581;

// √PI 1.77245385090551602729...
const float  kSqrtPIf = 1.77245385f;
const double kSqrtPId = 1.772453850905516;
// 2/√PI 1.12837916709551257390...
const float  kTwoOverSqrtPIf = 1.12837916f;
const double kTwoOverSqrtPId = 1.128379167095512;

// 1度あたりのラジアン
const float  kRadianPerDegreef = kPIf / 180.f;
const double kRadianPerDegreed = kPId / 180.0;

// 1ラジアンあたりの度
const float  kDegreePerRadianf = 180.f / kPIf;
const double kDegreePerRadiand = 180.0 / kPId;

// ネイピア数 2.7182818284590452354...
const float  kNapierf = 2.71828182f;
const double kNapierd = 2.718281828459045;

// log2e 1.4426950408889634074...
const float  kLog2ef = 1.44269504f;
const double kLog2ed = 1.442695040888963;

// log10e 0.43429448190325182765...
const float  kLog10ef = 0.43429448f;
const double kLog10ed = 0.434294481903251;

// loge2 0.69314718055994530942...
const float  kLoge2f = 0.69314718f;
const double kLoge2d = 0.693147180559945;

// loge10 2.30258509299404568402...
const float  kLog10f = 2.30258509f;
const double kLog10d = 2.302585092994045;

// logePI 1.14472988584940017414...
const float  kLogePIf = 1.14472988f;
const double kLogePId = 1.144729885849400;

// √2 1.41421356237309504880...
const float  kSqrtTwof = 1.41421356f;
const double kSqrtTwod = 1.414213562373095;

// √3 1.73205080756887729352...
const float  kSqrtThreef = 1.73205080f;
const double kSqrtThreed = 1.732050807568877;

// 1/√2 0.70710678118654752440...
const float  kReciprocalOfSqrtTwof = 0.70710678f;
const double kReciprocalOfSqrtTwod = 0.707106781186547;

// オイラー定数 0.57721566490153286061...
const float  kEulerf = 0.57721566f;
const double kEulerd = 0.577215664901532;

	} // namespacae math
} // namespace liza


#endif // __H_LIZAMATHMATHCONST_H__