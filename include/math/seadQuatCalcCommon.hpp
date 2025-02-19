#pragma once

#ifndef SEAD_MATH_QUAT_CALC_COMMON_H_
#include <math/seadQuatCalcCommon.h>
#endif

#include <limits>
#include <math/seadMathCalcCommon.h>
#include <math/seadQuat.h>

namespace sead
{
template <typename T>
inline T QuatCalcCommon<T>::length(const Base& v)
{
    return std::sqrt(dot(v, v));
}

template <typename T>
inline T QuatCalcCommon<T>::normalize(Base& v)
{
    const T len = length(v);
    if (len > 0)
    {
        const T inv_len = 1 / len;
        v.w *= inv_len;
        v.x *= inv_len;
        v.y *= inv_len;
        v.z *= inv_len;
    }

    return len;
}

template <typename T>
inline T QuatCalcCommon<T>::dot(const Base& u, const Base& v)
{
    return (u.w * v.w) + (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

template <typename T>
inline void QuatCalcCommon<T>::slerpTo(Base& out, const Base& q1, const Base& q2, f32 t)
{
    T dot = (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
    if (dot > 1)
        dot = 1;
    else if (dot < -1)
        dot = -1;

    const T dot_0 = dot;
    if (dot < 0)
        dot = -dot;

    T a, b;
    const T theta_0 = MathCalcCommon<T>::acos(dot);
    const T sin_theta_0 = std::sin(theta_0);
    if (MathCalcCommon<T>::abs(sin_theta_0) < std::numeric_limits<T>::epsilon())
    {
        a = 1.0f - t;
        b = t;
    }
    else
    {
        const T theta = theta_0 * t;
        const T sin_theta_0_inv = 1.0f / sin_theta_0;
        a = sin_theta_0_inv * std::sin(theta_0 - theta);
        b = sin_theta_0_inv * std::sin(theta);
    }

    if (dot_0 < 0)
        b = -b;

    out.x = a * q1.x + b * q2.x;
    out.y = a * q1.y + b * q2.y;
    out.z = a * q1.z + b * q2.z;
    out.w = a * q1.w + b * q2.w;
}

template <typename T>
inline void QuatCalcCommon<T>::makeUnit(Base& q)
{
    q = Quat<T>::unit;
}

template <typename T>
inline bool QuatCalcCommon<T>::makeVectorRotation(Base& q, const Vec3& from, const Vec3& to)
{
    // Based on The Shortest Arc Quaternion from Game Programming Gems 1
    Vec3 cross;
    Vector3CalcCommon<T>::cross(cross, from, to);
    const T dot = Vector3CalcCommon<T>::dot(from, to) + 1;

    if (dot <= MathCalcCommon<T>::epsilon())
    {
        makeUnit(q);
        return false;
    }
    else
    {
        T s = MathCalcCommon<T>::sqrt(2 * dot);
        T rs = 1 / s;
        set(q, s * 0.5f, cross.x * rs, cross.y * rs, cross.z * rs);
        return true;
    }
}

template <typename T>
inline void QuatCalcCommon<T>::set(Base& q, T w, T x, T y, T z)
{
    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
}

}  // namespace sead
