#pragma once
//! This file implements almost all ops defined in <core/math/ops.hpp>
//! as inline functions. This may be faster to run but definitely compiles slower!
//! If compilation speed is a concern, #include <core/math/ops.hpp> instead.
//!
//! Some heavy-weight functions are never inlined, and as such, are not defined here.
//!
//! This file also defines extra ops to convert to/from GLM types.
#include "ops.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>
#include <ostream>
#include <cmath>

#include <core/math/inline.macro.hpp>

namespace ss
{
    namespace math
    {
        inline namespace op
        {
            // Converting math types to GLM types, then converting back, is OK.
            // But directly converting GLM types to math types is UB.
            //
            // > Vector4 x; from_glm(as_glm(x));   is OK.
            // > glm::vec4 x; from_glm(x);         is undefined behavior.
            SS_MATH_OPS_INLINE auto as_glm(Vector1& a) noexcept -> float& { return reinterpret_cast<float&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector2& a) noexcept -> glm::vec2& { return reinterpret_cast<glm::vec2&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector3& a) noexcept -> glm::vec3& { return reinterpret_cast<glm::vec3&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector4& a) noexcept -> glm::vec4& { return reinterpret_cast<glm::vec4&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Matrix3& a) noexcept -> glm::mat3& { return reinterpret_cast<glm::mat3&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Matrix4& a) noexcept -> glm::mat4& { return reinterpret_cast<glm::mat4&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Quaternion& a) noexcept -> glm::quat& { return reinterpret_cast<glm::quat&>(a); }

            SS_MATH_OPS_INLINE auto as_glm(Vector1 const& a) noexcept -> float const& { return reinterpret_cast<float const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector2 const& a) noexcept -> glm::vec2 const& { return reinterpret_cast<glm::vec2 const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector3 const& a) noexcept -> glm::vec3 const& { return reinterpret_cast<glm::vec3 const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Vector4 const& a) noexcept -> glm::vec4 const& { return reinterpret_cast<glm::vec4 const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Matrix3 const& a) noexcept -> glm::mat3 const& { return reinterpret_cast<glm::mat3 const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Matrix4 const& a) noexcept -> glm::mat4 const& { return reinterpret_cast<glm::mat4 const&>(a); }
            SS_MATH_OPS_INLINE auto as_glm(Quaternion const& a) noexcept -> glm::quat const& { return reinterpret_cast<glm::quat const&>(a); }

            SS_MATH_OPS_INLINE auto from_glm(float& a) noexcept -> Vector1& { return reinterpret_cast<Vector1&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec2& a) noexcept -> Vector2& { return reinterpret_cast<Vector2&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec3& a) noexcept -> Vector3& { return reinterpret_cast<Vector3&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec4& a) noexcept -> Vector4& { return reinterpret_cast<Vector4&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::mat3& a) noexcept -> Matrix3& { return reinterpret_cast<Matrix3&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::mat4& a) noexcept -> Matrix4& { return reinterpret_cast<Matrix4&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::quat& a) noexcept -> Quaternion& { return reinterpret_cast<Quaternion&>(a); }

            SS_MATH_OPS_INLINE auto from_glm(float const& a) noexcept -> Vector1 const& { return reinterpret_cast<Vector1 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec2 const& a) noexcept -> Vector2 const& { return reinterpret_cast<Vector2 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec3 const& a) noexcept -> Vector3 const& { return reinterpret_cast<Vector3 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::vec4 const& a) noexcept -> Vector4 const& { return reinterpret_cast<Vector4 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::mat3 const& a) noexcept -> Matrix3 const& { return reinterpret_cast<Matrix3 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::mat4 const& a) noexcept -> Matrix4 const& { return reinterpret_cast<Matrix4 const&>(a); }
            SS_MATH_OPS_INLINE auto from_glm(glm::quat const& a) noexcept -> Quaternion const& { return reinterpret_cast<Quaternion const&>(a); }

            SS_MATH_OPS_INLINE auto operator == (Vector1 const& a, Vector1 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Vector2 const& a, Vector2 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Vector3 const& a, Vector3 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Vector4 const& a, Vector4 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Matrix3 const& a, Matrix3 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Matrix4 const& a, Matrix4 const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator == (Quaternion const& a, Quaternion const& b) noexcept -> bool { return (as_glm(a) == as_glm(b)); }

            SS_MATH_OPS_INLINE auto operator != (Vector1 const& a, Vector1 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Vector2 const& a, Vector2 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Vector3 const& a, Vector3 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Vector4 const& a, Vector4 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Matrix3 const& a, Matrix3 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Matrix4 const& a, Matrix4 const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator != (Quaternion const& a, Quaternion const& b) noexcept -> bool { return (as_glm(a) != as_glm(b)); }

            SS_MATH_OPS_INLINE auto operator < (Vector1 const& a, Vector1 const& b) noexcept -> bool { return conjunction(less(a, b)); }
            SS_MATH_OPS_INLINE auto operator < (Vector2 const& a, Vector2 const& b) noexcept -> bool { return conjunction(less(a, b)); }
            SS_MATH_OPS_INLINE auto operator < (Vector3 const& a, Vector3 const& b) noexcept -> bool { return conjunction(less(a, b)); }
            SS_MATH_OPS_INLINE auto operator < (Vector4 const& a, Vector4 const& b) noexcept -> bool { return conjunction(less(a, b)); }

            SS_MATH_OPS_INLINE auto operator > (Vector1 const& a, Vector1 const& b) noexcept -> bool { return conjunction(greater(a, b)); }
            SS_MATH_OPS_INLINE auto operator > (Vector2 const& a, Vector2 const& b) noexcept -> bool { return conjunction(greater(a, b)); }
            SS_MATH_OPS_INLINE auto operator > (Vector3 const& a, Vector3 const& b) noexcept -> bool { return conjunction(greater(a, b)); }
            SS_MATH_OPS_INLINE auto operator > (Vector4 const& a, Vector4 const& b) noexcept -> bool { return conjunction(greater(a, b)); }

            SS_MATH_OPS_INLINE auto operator <= (Vector1 const& a, Vector1 const& b) noexcept -> bool { return conjunction(less_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator <= (Vector2 const& a, Vector2 const& b) noexcept -> bool { return conjunction(less_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator <= (Vector3 const& a, Vector3 const& b) noexcept -> bool { return conjunction(less_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator <= (Vector4 const& a, Vector4 const& b) noexcept -> bool { return conjunction(less_equal(a, b)); }

            SS_MATH_OPS_INLINE auto operator >= (Vector1 const& a, Vector1 const& b) noexcept -> bool { return conjunction(greater_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator >= (Vector2 const& a, Vector2 const& b) noexcept -> bool { return conjunction(greater_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator >= (Vector3 const& a, Vector3 const& b) noexcept -> bool { return conjunction(greater_equal(a, b)); }
            SS_MATH_OPS_INLINE auto operator >= (Vector4 const& a, Vector4 const& b) noexcept -> bool { return conjunction(greater_equal(a, b)); }

            SS_MATH_OPS_INLINE auto conjunction(Vector1 const& a) noexcept -> bool { return bool(as_glm(a)); }
            SS_MATH_OPS_INLINE auto conjunction(Vector2 const& a) noexcept -> bool { return all(glm::bvec2(as_glm(a))); }
            SS_MATH_OPS_INLINE auto conjunction(Vector3 const& a) noexcept -> bool { return all(glm::bvec3(as_glm(a))); }
            SS_MATH_OPS_INLINE auto conjunction(Vector4 const& a) noexcept -> bool { return all(glm::bvec4(as_glm(a))); }

            SS_MATH_OPS_INLINE auto disjunction(Vector1 const& a) noexcept -> bool { return bool(as_glm(a)); }
            SS_MATH_OPS_INLINE auto disjunction(Vector2 const& a) noexcept -> bool { return any(glm::bvec2(as_glm(a))); }
            SS_MATH_OPS_INLINE auto disjunction(Vector3 const& a) noexcept -> bool { return any(glm::bvec3(as_glm(a))); }
            SS_MATH_OPS_INLINE auto disjunction(Vector4 const& a) noexcept -> bool { return any(glm::bvec4(as_glm(a))); }

            SS_MATH_OPS_INLINE auto equal_to(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) == as_glm(b))); }
            SS_MATH_OPS_INLINE auto equal_to(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(equal(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto equal_to(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(equal(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto equal_to(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(equal(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto not_equal_to(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) != as_glm(b))); }
            SS_MATH_OPS_INLINE auto not_equal_to(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(notEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto not_equal_to(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(notEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto not_equal_to(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(notEqual(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto less(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) < as_glm(b))); }
            SS_MATH_OPS_INLINE auto less(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(lessThan(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto less(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(lessThan(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto less(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(lessThan(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto greater(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) > as_glm(b))); }
            SS_MATH_OPS_INLINE auto greater(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(greaterThan(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto greater(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(greaterThan(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto greater(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(greaterThan(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto less_equal(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) <= as_glm(b))); }
            SS_MATH_OPS_INLINE auto less_equal(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(lessThanEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto less_equal(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(lessThanEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto less_equal(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(lessThanEqual(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto greater_equal(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(as_glm(a) >= as_glm(b))); }
            SS_MATH_OPS_INLINE auto greater_equal(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(greaterThanEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto greater_equal(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(greaterThanEqual(as_glm(a), as_glm(b)))); }
            SS_MATH_OPS_INLINE auto greater_equal(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(greaterThanEqual(as_glm(a), as_glm(b)))); }

            SS_MATH_OPS_INLINE auto operator &= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { return (a = a && b); }
            SS_MATH_OPS_INLINE auto operator &= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { return (a = a && b); }
            SS_MATH_OPS_INLINE auto operator &= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { return (a = a && b); }
            SS_MATH_OPS_INLINE auto operator &= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { return (a = a && b); }

            SS_MATH_OPS_INLINE auto operator |= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { return (a = a || b); }
            SS_MATH_OPS_INLINE auto operator |= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { return (a = a || b); }
            SS_MATH_OPS_INLINE auto operator |= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { return (a = a || b); }
            SS_MATH_OPS_INLINE auto operator |= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { return (a = a || b); }

            SS_MATH_OPS_INLINE auto operator ^= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { return (a = a ^ b); }
            SS_MATH_OPS_INLINE auto operator ^= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { return (a = a ^ b); }
            SS_MATH_OPS_INLINE auto operator ^= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { return (a = a ^ b); }
            SS_MATH_OPS_INLINE auto operator ^= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { return (a = a ^ b); }

            SS_MATH_OPS_INLINE auto operator && (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(bool(as_glm(a)) && bool(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator && (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(glm::bvec2(as_glm(a)) && glm::bvec2(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator && (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(glm::bvec3(as_glm(a)) && glm::bvec3(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator && (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(glm::bvec4(as_glm(a)) && glm::bvec4(as_glm(b)))); }

            SS_MATH_OPS_INLINE auto operator || (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(bool(as_glm(a)) || bool(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator || (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(glm::bvec2(as_glm(a)) || glm::bvec2(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator || (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(glm::bvec3(as_glm(a)) || glm::bvec3(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator || (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(glm::bvec4(as_glm(a)) || glm::bvec4(as_glm(b)))); }

            SS_MATH_OPS_INLINE auto operator ^ (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(float(bool(as_glm(a)) ^ bool(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator ^ (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(glm::vec2(glm::bvec2(as_glm(a)) ^ glm::bvec2(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator ^ (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(glm::vec3(glm::bvec3(as_glm(a)) ^ glm::bvec3(as_glm(b)))); }
            SS_MATH_OPS_INLINE auto operator ^ (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(glm::vec4(glm::bvec4(as_glm(a)) ^ glm::bvec4(as_glm(b)))); }

            SS_MATH_OPS_INLINE auto operator ! (Vector1 const& a) noexcept -> Vector1 { return from_glm(float(!bool(as_glm(a)))); }
            SS_MATH_OPS_INLINE auto operator ! (Vector2 const& a) noexcept -> Vector2 { return from_glm(glm::vec2(not_(glm::bvec2(as_glm(a))))); }
            SS_MATH_OPS_INLINE auto operator ! (Vector3 const& a) noexcept -> Vector3 { return from_glm(glm::vec3(not_(glm::bvec3(as_glm(a))))); }
            SS_MATH_OPS_INLINE auto operator ! (Vector4 const& a) noexcept -> Vector4 { return from_glm(glm::vec4(not_(glm::bvec4(as_glm(a))))); }

            SS_MATH_OPS_INLINE auto operator + (Vector1 const& a) noexcept -> Vector1 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Vector2 const& a) noexcept -> Vector2 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Vector3 const& a) noexcept -> Vector3 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Vector4 const& a) noexcept -> Vector4 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Matrix3 const& a) noexcept -> Matrix3 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Matrix4 const& a) noexcept -> Matrix4 { return a; }
            SS_MATH_OPS_INLINE auto operator + (Quaternion const& a) noexcept -> Quaternion { return a; }

            SS_MATH_OPS_INLINE auto operator - (Vector1 const& a) noexcept -> Vector1 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Vector2 const& a) noexcept -> Vector2 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Vector3 const& a) noexcept -> Vector3 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Vector4 const& a) noexcept -> Vector4 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Matrix3 const& a) noexcept -> Matrix3 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Matrix4 const& a) noexcept -> Matrix4 { return from_glm(-as_glm(a)); }
            SS_MATH_OPS_INLINE auto operator - (Quaternion const& a) noexcept -> Quaternion { return from_glm(-as_glm(a)); }

            SS_MATH_OPS_INLINE auto operator += (Vector1& a, Vector1 const& b) noexcept -> Vector1& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Vector2& a, Vector2 const& b) noexcept -> Vector2& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Vector3& a, Vector3 const& b) noexcept -> Vector3& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Vector4& a, Vector4 const& b) noexcept -> Vector4& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4& { as_glm(a) += as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator += (Quaternion& a, Quaternion const& b) noexcept -> Quaternion& { as_glm(a) += as_glm(b); return a; }

            SS_MATH_OPS_INLINE auto operator -= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4& { as_glm(a) -= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator -= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion& { as_glm(a) -= as_glm(b); return a; }

            SS_MATH_OPS_INLINE auto operator *= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion& { as_glm(a) *= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Quaternion& a, float b) noexcept -> Quaternion& { as_glm(a) *= b; return a; }

            SS_MATH_OPS_INLINE auto operator /= (Vector1& a, Vector1 const& b) noexcept -> Vector1& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Vector2& a, Vector2 const& b) noexcept -> Vector2& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Vector3& a, Vector3 const& b) noexcept -> Vector3& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Vector4& a, Vector4 const& b) noexcept -> Vector4& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Matrix3& a, Matrix3 const& b) noexcept -> Matrix3& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Matrix4& a, Matrix4 const& b) noexcept -> Matrix4& { as_glm(a) /= as_glm(b); return a; }
            SS_MATH_OPS_INLINE auto operator /= (Quaternion& a, Quaternion const& b) noexcept -> Quaternion& { a = a / b; return a; }
            SS_MATH_OPS_INLINE auto operator /= (Quaternion& a, float b) noexcept -> Quaternion& { as_glm(a) /= b; return a; }

            SS_MATH_OPS_INLINE auto operator + (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4 { return from_glm(as_glm(a) + as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator + (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion { return from_glm(as_glm(a) + as_glm(b)); }

            SS_MATH_OPS_INLINE auto operator - (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(as_glm(a) - as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator - (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(as_glm(a) - as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator - (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) - as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator - (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) - as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator - (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3 { return from_glm(as_glm(a) - as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator - (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4 { return from_glm(as_glm(a) - as_glm(b)); }
            // The `operator -` is not defined for `glm::quat`. Don't know why.
            SS_MATH_OPS_INLINE auto operator - (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion { auto c = a; c -= b; return c; }

            SS_MATH_OPS_INLINE auto operator * (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion { return from_glm(as_glm(a) * as_glm(b)); }

            SS_MATH_OPS_INLINE auto operator * (Matrix3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Matrix4 const& a, Vector3 const& b) noexcept -> Vector3 { return Vector3{a * Vector4{b, 1.0f}}; }
            SS_MATH_OPS_INLINE auto operator * (Matrix4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Quaternion const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Quaternion const& a, float b) noexcept -> Quaternion { return from_glm(as_glm(a) * b); }

            SS_MATH_OPS_INLINE auto operator * (Vector3 const& a, Matrix3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (Vector3 const& a, Matrix4 const& b) noexcept -> Vector3 { return Vector3{Vector4{a, 1.0f} * b}; }
            SS_MATH_OPS_INLINE auto operator * (Vector4 const& a, Matrix4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) * as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator * (float a, Quaternion const& b) noexcept -> Quaternion { return from_glm(a * as_glm(b)); }

            SS_MATH_OPS_INLINE auto operator / (Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Matrix3 const& a, Matrix3 const& b) noexcept -> Matrix3 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Matrix4 const& a, Matrix4 const& b) noexcept -> Matrix4 { return from_glm(as_glm(a) / as_glm(b)); }
            SS_MATH_OPS_INLINE auto operator / (Quaternion const& a, Quaternion const& b) noexcept -> Quaternion { return a * inverse(b); }

            SS_MATH_OPS_INLINE auto operator / (Quaternion const& a, float b) noexcept -> Quaternion { return from_glm(as_glm(a) / b); }

            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Vector1 const& a) noexcept -> std::ostream& { return (o << "Vector1{" << a.x << "}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Vector2 const& a) noexcept -> std::ostream& { return (o << "Vector2{" << a.x << ", " << a.y << "}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Vector3 const& a) noexcept -> std::ostream& { return (o << "Vector3{" << a.x << ", " << a.y << ", " << a.z << "}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Vector4 const& a) noexcept -> std::ostream& { return (o << "Vector4{" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << "}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Matrix3 const& a) noexcept -> std::ostream& { return (o << "Matrix3{\n\x20\x20\x20\x20" << a.x << ",\n\x20\x20\x20\x20" << a.y << ",\n\x20\x20\x20\x20" << a.z << ",\n}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Matrix4 const& a) noexcept -> std::ostream& { return (o << "Matrix4{\n\x20\x20\x20\x20" << a.x << ",\n\x20\x20\x20\x20" << a.y << ",\n\x20\x20\x20\x20" << a.z << ",\n\x20\x20\x20\x20" << a.w << ",\n}"); }
            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Quaternion const& a) noexcept -> std::ostream& { return (o << "Quaternion{w=" << a.w << ", " << a.x << ", " << a.y << ", " << a.z << "}"); }

            SS_MATH_OPS_INLINE auto dot(Vector1 const& a, Vector1 const& b) noexcept -> float { return as_glm(a) * as_glm(b); }
            SS_MATH_OPS_INLINE auto dot(Vector2 const& a, Vector2 const& b) noexcept -> float { return dot(as_glm(a), as_glm(b)); }
            SS_MATH_OPS_INLINE auto dot(Vector3 const& a, Vector3 const& b) noexcept -> float { return dot(as_glm(a), as_glm(b)); }
            SS_MATH_OPS_INLINE auto dot(Vector4 const& a, Vector4 const& b) noexcept -> float { return dot(as_glm(a), as_glm(b)); }
            SS_MATH_OPS_INLINE auto dot(Quaternion const& a, Quaternion const& b) noexcept -> float { return dot(as_glm(a), as_glm(b)); }

            SS_MATH_OPS_INLINE auto cross(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(cross(as_glm(a), as_glm(b))); }

            SS_MATH_OPS_INLINE auto floor(Vector1 const& a) noexcept -> Vector1 { return from_glm(std::floor(as_glm(a))); }
            SS_MATH_OPS_INLINE auto floor(Vector2 const& a) noexcept -> Vector2 { return from_glm(floor(as_glm(a))); }
            SS_MATH_OPS_INLINE auto floor(Vector3 const& a) noexcept -> Vector3 { return from_glm(floor(as_glm(a))); }
            SS_MATH_OPS_INLINE auto floor(Vector4 const& a) noexcept -> Vector4 { return from_glm(floor(as_glm(a))); }

            SS_MATH_OPS_INLINE auto ceil(Vector1 const& a) noexcept -> Vector1 { return from_glm(std::ceil(as_glm(a))); }
            SS_MATH_OPS_INLINE auto ceil(Vector2 const& a) noexcept -> Vector2 { return from_glm(ceil(as_glm(a))); }
            SS_MATH_OPS_INLINE auto ceil(Vector3 const& a) noexcept -> Vector3 { return from_glm(ceil(as_glm(a))); }
            SS_MATH_OPS_INLINE auto ceil(Vector4 const& a) noexcept -> Vector4 { return from_glm(ceil(as_glm(a))); }

            SS_MATH_OPS_INLINE auto round(Vector1 const& a) noexcept -> Vector1 { return from_glm(std::round(as_glm(a))); }
            SS_MATH_OPS_INLINE auto round(Vector2 const& a) noexcept -> Vector2 { return from_glm(round(as_glm(a))); }
            SS_MATH_OPS_INLINE auto round(Vector3 const& a) noexcept -> Vector3 { return from_glm(round(as_glm(a))); }
            SS_MATH_OPS_INLINE auto round(Vector4 const& a) noexcept -> Vector4 { return from_glm(round(as_glm(a))); }

            SS_MATH_OPS_INLINE auto min(Vector1 const& a) noexcept -> float { return as_glm(a); }
            SS_MATH_OPS_INLINE auto min(Vector2 const& a) noexcept -> float { return compMin(as_glm(a)); }
            SS_MATH_OPS_INLINE auto min(Vector3 const& a) noexcept -> float { return compMin(as_glm(a)); }
            SS_MATH_OPS_INLINE auto min(Vector4 const& a) noexcept -> float { return compMin(as_glm(a)); }

            SS_MATH_OPS_INLINE auto max(Vector1 const& a) noexcept -> float { return as_glm(a); }
            SS_MATH_OPS_INLINE auto max(Vector2 const& a) noexcept -> float { return compMax(as_glm(a)); }
            SS_MATH_OPS_INLINE auto max(Vector3 const& a) noexcept -> float { return compMax(as_glm(a)); }
            SS_MATH_OPS_INLINE auto max(Vector4 const& a) noexcept -> float { return compMax(as_glm(a)); }

            SS_MATH_OPS_INLINE auto min(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(std::fmin(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto min(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(min(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto min(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(min(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto min(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(min(as_glm(a), as_glm(b))); }

            SS_MATH_OPS_INLINE auto max(Vector1 const& a, Vector1 const& b) noexcept -> Vector1 { return from_glm(std::fmax(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto max(Vector2 const& a, Vector2 const& b) noexcept -> Vector2 { return from_glm(max(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto max(Vector3 const& a, Vector3 const& b) noexcept -> Vector3 { return from_glm(max(as_glm(a), as_glm(b))); }
            SS_MATH_OPS_INLINE auto max(Vector4 const& a, Vector4 const& b) noexcept -> Vector4 { return from_glm(max(as_glm(a), as_glm(b))); }

            SS_MATH_OPS_INLINE auto mix(Vector1 const& a, Vector1 const& b, float t) noexcept -> Vector1 { return from_glm((1.0f - t) * as_glm(a) + t * as_glm(b)); }
            SS_MATH_OPS_INLINE auto mix(Vector2 const& a, Vector2 const& b, float t) noexcept -> Vector2 { return from_glm(mix(as_glm(a), as_glm(b), t)); }
            SS_MATH_OPS_INLINE auto mix(Vector3 const& a, Vector3 const& b, float t) noexcept -> Vector3 { return from_glm(mix(as_glm(a), as_glm(b), t)); }
            SS_MATH_OPS_INLINE auto mix(Vector4 const& a, Vector4 const& b, float t) noexcept -> Vector4 { return from_glm(mix(as_glm(a), as_glm(b), t)); }
            SS_MATH_OPS_INLINE auto mix(Quaternion const& a, Quaternion const& b, float t) noexcept -> Quaternion { return from_glm(slerp(as_glm(a), as_glm(b), t)); }

            SS_MATH_OPS_INLINE auto squared_length(Vector1 const& a) noexcept -> float { return dot(a, a); }
            SS_MATH_OPS_INLINE auto squared_length(Vector2 const& a) noexcept -> float { return dot(a, a); }
            SS_MATH_OPS_INLINE auto squared_length(Vector3 const& a) noexcept -> float { return dot(a, a); }
            SS_MATH_OPS_INLINE auto squared_length(Vector4 const& a) noexcept -> float { return dot(a, a); }

            SS_MATH_OPS_INLINE auto length(Vector1 const& a) noexcept -> float { return as_glm(a); }
            SS_MATH_OPS_INLINE auto length(Vector2 const& a) noexcept -> float { return length(as_glm(a)); }
            SS_MATH_OPS_INLINE auto length(Vector3 const& a) noexcept -> float { return length(as_glm(a)); }
            SS_MATH_OPS_INLINE auto length(Vector4 const& a) noexcept -> float { return length(as_glm(a)); }

            SS_MATH_OPS_INLINE auto normalize(Vector1 const& a) noexcept -> Vector1 { return from_glm(1.0f); }
            SS_MATH_OPS_INLINE auto normalize(Vector2 const& a) noexcept -> Vector2 { return from_glm(normalize(as_glm(a))); }
            SS_MATH_OPS_INLINE auto normalize(Vector3 const& a) noexcept -> Vector3 { return from_glm(normalize(as_glm(a))); }
            SS_MATH_OPS_INLINE auto normalize(Vector4 const& a) noexcept -> Vector4 { return from_glm(normalize(as_glm(a))); }

            SS_MATH_OPS_INLINE auto inverse(Matrix3 const& a) noexcept -> Matrix3 { return from_glm(inverse(as_glm(a))); }
            SS_MATH_OPS_INLINE auto inverse(Matrix4 const& a) noexcept -> Matrix4 { return from_glm(inverse(as_glm(a))); }
            SS_MATH_OPS_INLINE auto inverse(Quaternion const& a) noexcept -> Quaternion { return from_glm(inverse(as_glm(a))); }

            SS_MATH_OPS_INLINE auto transpose(Matrix3 const& a) noexcept -> Matrix3 { return from_glm(transpose(as_glm(a))); }
            SS_MATH_OPS_INLINE auto transpose(Matrix4 const& a) noexcept -> Matrix4 { return from_glm(transpose(as_glm(a))); }

            SS_MATH_OPS_INLINE auto quat_to_mat(Quaternion const& a) noexcept -> Matrix3 { return from_glm(mat3_cast(as_glm(a))); }

            SS_MATH_OPS_INLINE auto quat_from_angle_axis(float angle, Vector3 axis) noexcept -> Quaternion { return from_glm(angleAxis(angle, as_glm(axis))); }
        }
    }
}

#include <core/math/inline.undef.hpp>

