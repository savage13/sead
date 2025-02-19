#pragma once

#include <basis/seadTypes.h>
#include <cmath>
#include <limits>
#include <math/seadMathPolicies.h>
#include <math/seadVector.h>

namespace sead
{
template <typename T>
struct Quat : public Policies<T>::QuatBase
{
private:
    typedef Quat<T> Self;
    typedef Vector3<T> Vec3;

public:
    Quat() {}
    Quat(const Quat& other) { *this = other; }
    Quat(T x, T y, T z, T w);

    Quat& operator=(const Quat& other)
    {
        this->w = other.w;
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    friend Quat operator*(const Quat& a, T t)
    {
        auto result = a;
        result *= t;
        return result;
    }

    friend Quat operator*(const Quat& a, const Quat& b)
    {
        auto result = a;
        result *= b;
        return result;
    }

    friend Quat operator*(T t, const Quat& a) { return operator*(a, t); }

    // I don't think this is right?
    Quat& operator*=(const Quat& t)
    {
        this->w *= t.w;
        this->x *= t.x;
        this->y *= t.y;
        this->z *= t.z;
        return *this;
    }

    Quat& operator*=(T t)
    {
        this->w *= t;
        this->x *= t;
        this->y *= t;
        this->z *= t;
        return *this;
    }

    T length() const;
    T normalize();
    T dot(const Self& q);
    void inverse(Self* q);

    void makeUnit();
    bool makeVectorRotation(const Vec3& from, const Vec3& to);
    void set(T x, T y, T z, T w);

    static const Quat unit;
};

using Quatf = Quat<f32>;

template <>
const Quatf Quatf::unit;

}  // namespace sead

#define SEAD_MATH_QUAT_H_
#include <math/seadQuat.hpp>
#undef SEAD_MATH_QUAT_H_
