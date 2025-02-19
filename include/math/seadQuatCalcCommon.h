#pragma once

#include <math/seadMathPolicies.h>

namespace sead
{
template <typename T>
class QuatCalcCommon
{
public:
    using Base = typename Policies<T>::QuatBase;
    using Vec3 = typename Policies<T>::Vec3Base;

    static T length(const Base& v);
    static T normalize(Base& v);
    static T dot(const Base& a, const Base& b);
    static void slerpTo(Base& out, const Base& q1, const Base& q2, f32 t);
    static void makeUnit(Base& q);
    static bool makeVectorRotation(Base& q, const Vec3& from, const Vec3& to);
    static void set(Base& q, T w, T x, T y, T z);
};

}  // namespace sead

#define SEAD_MATH_QUAT_CALC_COMMON_H_
#include "math/seadQuatCalcCommon.hpp"
#undef SEAD_MATH_QUAT_CALC_COMMON_H_
