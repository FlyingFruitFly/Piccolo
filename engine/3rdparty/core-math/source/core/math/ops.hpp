#pragma once
//! Include this file to call operators on math types.
//! All ops generate function calls.
//!
//! You may #include <core/math/ops-inline.hpp> to get them inlined,
//! which may run faster but definitely compiles slower.
#include "types.hpp"
#include <iosfwd>

namespace ss
{
    namespace math
    {
        inline namespace op
        {
            template <class Fn> auto spread(Vector1 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Vector1 { for (int i=0; i< 1; i++) a[i] = fn(a[i]); return a; }
            template <class Fn> auto spread(Vector2 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Vector2 { for (int i=0; i< 2; i++) a[i] = fn(a[i]); return a; }
            template <class Fn> auto spread(Vector3 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Vector3 { for (int i=0; i< 3; i++) a[i] = fn(a[i]); return a; }
            template <class Fn> auto spread(Vector4 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Vector4 { for (int i=0; i< 4; i++) a[i] = fn(a[i]); return a; }
            template <class Fn> auto spread(Matrix3 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Matrix3 { for (int i=0; i< 9; i++) a[i] = fn(a[i]); return a; }
            template <class Fn> auto spread(Matrix4 a, Fn&& fn) noexcept(noexcept(fn(0.0f))) -> Matrix4 { for (int i=0; i<16; i++) a[i] = fn(a[i]); return a; }

            auto operator == (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator == (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator == (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator == (Vector4 const& a, Vector4 const& b) noexcept -> bool;
            auto operator == (Matrix3 const& a, Matrix3 const& b) noexcept -> bool;
            auto operator == (Matrix4 const& a, Matrix4 const& b) noexcept -> bool;
            auto operator == (Quaternion const& a, Quaternion const& b) noexcept -> bool;

            auto operator != (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator != (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator != (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator != (Vector4 const& a, Vector4 const& b) noexcept -> bool;
            auto operator != (Matrix3 const& a, Matrix3 const& b) noexcept -> bool;
            auto operator != (Matrix4 const& a, Matrix4 const& b) noexcept -> bool;
            auto operator != (Quaternion const& a, Quaternion const& b) noexcept -> bool;

            auto operator < (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator < (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator < (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator < (Vector4 const& a, Vector4 const& b) noexcept -> bool;

            auto operator > (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator > (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator > (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator > (Vector4 const& a, Vector4 const& b) noexcept -> bool;

            auto operator <= (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator <= (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator <= (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator <= (Vector4 const& a, Vector4 const& b) noexcept -> bool;

            auto operator >= (Vector1 const& a, Vector1 const& b) noexcept -> bool;
            auto operator >= (Vector2 const& a, Vector2 const& b) noexcept -> bool;
            auto operator >= (Vector3 const& a, Vector3 const& b) noexcept -> bool;
            auto operator >= (Vector4 const& a, Vector4 const& b) noexcept -> bool;

            auto conjunction(Vector1 const& a) noexcept -> bool;
            auto conjunction(Vector2 const& a) noexcept -> bool;
            auto conjunction(Vector3 const& a) noexcept -> bool;
            auto conjunction(Vector4 const& a) noexcept -> bool;

            auto disjunction(Vector1 const& a) noexcept -> bool;
            auto disjunction(Vector2 const& a) noexcept -> bool;
            auto disjunction(Vector3 const& a) noexcept -> bool;
            auto disjunction(Vector4 const& a) noexcept -> bool;

            auto equal_to(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto equal_to(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto equal_to(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto equal_to(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto not_equal_to(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto not_equal_to(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto not_equal_to(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto not_equal_to(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto less(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto less(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto less(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto less(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto greater(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto greater(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto greater(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto greater(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto less_equal(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto less_equal(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto less_equal(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto less_equal(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto greater_equal(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto greater_equal(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto greater_equal(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto greater_equal(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto operator &= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator &= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator &= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator &= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;

            auto operator |= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator |= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator |= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator |= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;

            auto operator ^= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator ^= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator ^= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator ^= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;

            auto operator && (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator && (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator && (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator && (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto operator || (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator || (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator || (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator || (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto operator ^ (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator ^ (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator ^ (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator ^ (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto operator ! (Vector1 const& a) noexcept -> Vector1;
            auto operator ! (Vector2 const& a) noexcept -> Vector2;
            auto operator ! (Vector3 const& a) noexcept -> Vector3;
            auto operator ! (Vector4 const& a) noexcept -> Vector4;

            auto operator + (Vector1 const& a) noexcept -> Vector1;
            auto operator + (Vector2 const& a) noexcept -> Vector2;
            auto operator + (Vector3 const& a) noexcept -> Vector3;
            auto operator + (Vector4 const& a) noexcept -> Vector4;
            auto operator + (Matrix3 const& a) noexcept -> Matrix3;
            auto operator + (Matrix4 const& a) noexcept -> Matrix4;
            auto operator + (Quaternion const& a) noexcept -> Quaternion;

            auto operator - (Vector1 const& a) noexcept -> Vector1;
            auto operator - (Vector2 const& a) noexcept -> Vector2;
            auto operator - (Vector3 const& a) noexcept -> Vector3;
            auto operator - (Vector4 const& a) noexcept -> Vector4;
            auto operator - (Matrix3 const& a) noexcept -> Matrix3;
            auto operator - (Matrix4 const& a) noexcept -> Matrix4;
            auto operator - (Quaternion const& a) noexcept -> Quaternion;

            auto operator += (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator += (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator += (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator += (Vector4& a, Vector4 const& b) noexcept -> Vector4&;
            auto operator += (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3&;
            auto operator += (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4&;
            auto operator += (Quaternion& a, Quaternion const& b) noexcept -> Quaternion&;

            auto operator -= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator -= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator -= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator -= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;
            auto operator -= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3&;
            auto operator -= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4&;
            auto operator -= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion&;

            auto operator *= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator *= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator *= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator *= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;
            auto operator *= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3&;
            auto operator *= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4&;
            auto operator *= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion&;
            auto operator *= (Quaternion& a, float b) noexcept -> Quaternion&;

            auto operator /= (Vector1& a, Vector1 const& b) noexcept -> Vector1&;
            auto operator /= (Vector2& a, Vector2 const& b) noexcept -> Vector2&;
            auto operator /= (Vector3& a, Vector3 const& b) noexcept -> Vector3&;
            auto operator /= (Vector4& a, Vector4 const& b) noexcept -> Vector4&;
            auto operator /= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3&;
            auto operator /= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4&;
            auto operator /= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion&;
            auto operator /= (Quaternion& a, float b) noexcept -> Quaternion&;

            auto operator + (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator + (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator + (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator + (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;
            auto operator + (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3;
            auto operator + (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4;
            auto operator + (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion;

            auto operator - (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator - (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator - (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator - (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;
            auto operator - (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3;
            auto operator - (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4;
            auto operator - (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion;

            auto operator * (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator * (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator * (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator * (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;
            auto operator * (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3;
            auto operator * (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4;
            auto operator * (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion;

            auto operator * (Matrix3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator * (Matrix4 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator * (Matrix4 const& a, Vector4 const& b) noexcept -> Vector4;
            auto operator * (Quaternion const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator * (Quaternion const& a, float b) noexcept -> Quaternion;

            auto operator * (Vector3 const& a, Matrix3 const& b) noexcept -> Vector3;
            auto operator * (Vector3 const& a, Matrix4 const& b) noexcept -> Vector3;
            auto operator * (Vector4 const& a, Matrix4 const& b) noexcept -> Vector4;
            auto operator * (float a, Quaternion const& b) noexcept -> Quaternion;

            auto operator / (Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto operator / (Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto operator / (Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator / (Vector4 const& a, Vector4 const& b) noexcept -> Vector4;
            auto operator / (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3;
            auto operator / (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4;
            auto operator / (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion;

            auto operator / (Quaternion const& a, float b) noexcept -> Quaternion;

            auto operator << (std::ostream& o, Vector1 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Vector2 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Vector3 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Vector4 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Matrix3 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Matrix4 const& a) noexcept -> std::ostream&;
            auto operator << (std::ostream& o, Quaternion const& a) noexcept -> std::ostream&;

            auto dot(Vector1 const& a, Vector1 const& b) noexcept -> float;
            auto dot(Vector2 const& a, Vector2 const& b) noexcept -> float;
            auto dot(Vector3 const& a, Vector3 const& b) noexcept -> float;
            auto dot(Vector4 const& a, Vector4 const& b) noexcept -> float;
            auto dot(Quaternion const& a, Quaternion const& b) noexcept -> float;

            auto cross(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;

            auto floor(Vector1 const& a) noexcept -> Vector1;
            auto floor(Vector2 const& a) noexcept -> Vector2;
            auto floor(Vector3 const& a) noexcept -> Vector3;
            auto floor(Vector4 const& a) noexcept -> Vector4;

            auto ceil(Vector1 const& a) noexcept -> Vector1;
            auto ceil(Vector2 const& a) noexcept -> Vector2;
            auto ceil(Vector3 const& a) noexcept -> Vector3;
            auto ceil(Vector4 const& a) noexcept -> Vector4;

            auto round(Vector1 const& a) noexcept -> Vector1;
            auto round(Vector2 const& a) noexcept -> Vector2;
            auto round(Vector3 const& a) noexcept -> Vector3;
            auto round(Vector4 const& a) noexcept -> Vector4;

            auto min(Vector1 const& a) noexcept -> float;
            auto min(Vector2 const& a) noexcept -> float;
            auto min(Vector3 const& a) noexcept -> float;
            auto min(Vector4 const& a) noexcept -> float;

            auto max(Vector1 const& a) noexcept -> float;
            auto max(Vector2 const& a) noexcept -> float;
            auto max(Vector3 const& a) noexcept -> float;
            auto max(Vector4 const& a) noexcept -> float;

            auto min(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto min(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto min(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto min(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto max(Vector1 const& a, Vector1 const& b) noexcept -> Vector1;
            auto max(Vector2 const& a, Vector2 const& b) noexcept -> Vector2;
            auto max(Vector3 const& a, Vector3 const& b) noexcept -> Vector3;
            auto max(Vector4 const& a, Vector4 const& b) noexcept -> Vector4;

            auto mix(Vector1 const& a, Vector1 const& b, float t) noexcept -> Vector1;
            auto mix(Vector2 const& a, Vector2 const& b, float t) noexcept -> Vector2;
            auto mix(Vector3 const& a, Vector3 const& b, float t) noexcept -> Vector3;
            auto mix(Vector4 const& a, Vector4 const& b, float t) noexcept -> Vector4;
            auto mix(Quaternion const& a, Quaternion const& b, float t) noexcept -> Quaternion;

            auto squared_length(Vector1 const& a) noexcept -> float;
            auto squared_length(Vector2 const& a) noexcept -> float;
            auto squared_length(Vector3 const& a) noexcept -> float;
            auto squared_length(Vector4 const& a) noexcept -> float;

            auto length(Vector1 const& a) noexcept -> float;
            auto length(Vector2 const& a) noexcept -> float;
            auto length(Vector3 const& a) noexcept -> float;
            auto length(Vector4 const& a) noexcept -> float;

            auto normalize(Vector1 const& a) noexcept -> Vector1;
            auto normalize(Vector2 const& a) noexcept -> Vector2;
            auto normalize(Vector3 const& a) noexcept -> Vector3;
            auto normalize(Vector4 const& a) noexcept -> Vector4;
            auto normalize(Quaternion const& a) noexcept -> Quaternion;

            auto inverse(Matrix3 const& a) noexcept -> Matrix3;
            auto inverse(Matrix4 const& a) noexcept -> Matrix4;
            auto inverse(Quaternion const& a) noexcept -> Quaternion;

            auto transpose(Matrix3 const& a) noexcept -> Matrix3;
            auto transpose(Matrix4 const& a) noexcept -> Matrix4;

            auto quat_to_mat(Quaternion const& a) noexcept -> Matrix3;
            // The Matrix3 cannot have scaling components.
            auto mat_to_quat(Matrix3 const& a) noexcept -> Quaternion;

            // result.x: Rotation around X-axis (pitch), range in (-π/2, π/2)
            // result.y: Rotation around Y-axis (yaw),   range in [-π, π)
            // result.z: Rotation around Z-axis (roll),  range in [-π, π)
            // The Euler angles ordering is ZXY.
            CCTT_INTROSPECT();
            auto quat_to_Euler(Quaternion const& a) noexcept -> Vector3;
            // euler_angles.x: Rotation around X-axis (pitch)
            // euler_angles.y: Rotation around Y-axis (yaw)
            // euler_angles.z: Rotation around Z-axis (roll)
            // The Euler angles ordering is ZXY.
            CCTT_INTROSPECT();
            auto Euler_to_quat(Vector3 const& Euler_angles) noexcept -> Quaternion;

            auto quat_from_angle_axis(float angle, Vector3 axis) noexcept -> Quaternion;
            bool isNaN(Vector3 const& vec);
            bool isNaN(Quaternion const& quat);

            Quaternion getRotationTo(const Vector3 & origin, const Vector3 & dest, const Vector3 & fallbackAxis = Vector3(0,0,0));
        }
    }
}

