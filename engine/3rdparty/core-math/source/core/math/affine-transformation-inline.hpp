#pragma once
//! This file implements most functions from <core/math/affine-transformation.hpp>
//! as inline functions. This may be faster to run but definitely compiles slower!
//! If compilation speed is a concern, #include <core/math/affine-transformation.hpp> instead.
//!
//! Light-weight math operations are inlined here.
//! Heavy-weight ones are never inlined.
#include "affine-transformation.hpp"
#include "ops.hpp"
#include <ostream>

#include <core/math/inline.macro.hpp>

namespace ss
{
    namespace math
    {
        inline namespace op
        {
            SS_MATH_OPS_INLINE auto scale(Affine_Transformation& xform, Vector3 const& factor)         noexcept -> void { xform.mutable_config().scaling  *= factor; }
            SS_MATH_OPS_INLINE auto move_globally(Affine_Transformation& xform, Vector3 const& offset) noexcept -> void { xform.mutable_config().position += offset; }
            SS_MATH_OPS_INLINE auto move_locally(Affine_Transformation& xform, Vector3 const& offset)  noexcept -> void { move_globally(xform, xform.config().rotation * offset); }

            SS_MATH_OPS_INLINE auto rotate(Affine_Transformation& xform, Quaternion const& rot) noexcept -> void { xform.mutable_config().rotation *= rot; }
            SS_MATH_OPS_INLINE auto rotate(Affine_Transformation& xform, Matrix3 const& x) noexcept -> void { rotate(xform, mat_to_quat(x)); }
            SS_MATH_OPS_INLINE auto rotate(Affine_Transformation& xform, Matrix4 const& x) noexcept -> void { rotate(xform, Matrix3{x}); }

            SS_MATH_OPS_INLINE auto xrotate(Affine_Transformation& xform, float a) noexcept -> void { rotate(xform, quat_from_angle_axis(a, {1.0f, 0.0f, 0.0f})); }
            SS_MATH_OPS_INLINE auto yrotate(Affine_Transformation& xform, float a) noexcept -> void { rotate(xform, quat_from_angle_axis(a, {0.0f, 1.0f, 0.0f})); }
            SS_MATH_OPS_INLINE auto zrotate(Affine_Transformation& xform, float a) noexcept -> void { rotate(xform, quat_from_angle_axis(a, {0.0f, 0.0f, 1.0f})); }

            SS_MATH_OPS_INLINE auto operator == (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> bool { return (a.matrix() == b.matrix()); }
            SS_MATH_OPS_INLINE auto operator == (Affine_Transformation const& a, Matrix4 const& b) noexcept -> bool { return (a.matrix() == b); }
            SS_MATH_OPS_INLINE auto operator == (Matrix4 const& a, Affine_Transformation const& b) noexcept -> bool { return (a == b.matrix()); }

            SS_MATH_OPS_INLINE auto operator != (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> bool { return (a.matrix() != b.matrix()); }
            SS_MATH_OPS_INLINE auto operator != (Affine_Transformation const& a, Matrix4 const& b) noexcept -> bool { return (a.matrix() != b); }
            SS_MATH_OPS_INLINE auto operator != (Matrix4 const& a, Affine_Transformation const& b) noexcept -> bool { return (a != b.matrix()); }

            SS_MATH_OPS_INLINE auto operator *= (Affine_Transformation& a, Affine_Transformation const& b) noexcept -> Affine_Transformation& { a.mutable_matrix() *= b.matrix(); return a; }
            SS_MATH_OPS_INLINE auto operator *= (Affine_Transformation& a, Matrix4 const& b) noexcept -> Affine_Transformation& { a.mutable_matrix() *= b; return a; }
            SS_MATH_OPS_INLINE auto operator *= (Matrix4& a, Affine_Transformation const& b) noexcept -> Matrix4& { a *= b.matrix(); return a; }

            SS_MATH_OPS_INLINE auto operator * (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation { return Affine_Transformation{a.matrix() * b.matrix()}; }
            SS_MATH_OPS_INLINE auto operator * (Affine_Transformation const& a, Matrix4 const& b) noexcept -> Affine_Transformation { return Affine_Transformation{a.matrix() * b}; }
            SS_MATH_OPS_INLINE auto operator * (Matrix4 const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation { return Affine_Transformation{a * b.matrix()}; }

            SS_MATH_OPS_INLINE auto operator * (Affine_Transformation const& a, Vector3 const& b) noexcept -> Vector3 { return a.matrix() * b; }
            SS_MATH_OPS_INLINE auto operator * (Affine_Transformation const& a, Vector4 const& b) noexcept -> Vector4 { return a.matrix() * b; }

            SS_MATH_OPS_INLINE auto operator * (Vector3 const& a, Affine_Transformation const& b) noexcept -> Vector3 { return a * b.matrix(); }
            SS_MATH_OPS_INLINE auto operator * (Vector4 const& a, Affine_Transformation const& b) noexcept -> Vector4 { return a * b.matrix(); }

            SS_MATH_OPS_INLINE auto operator << (std::ostream& o, Affine_Transformation const& a) noexcept -> std::ostream& { return (o << "Affine_Transformation{\n\x20\x20\x20\x20" << a.config().rotation << ",\n\x20\x20\x20\x20" << a.config().position << ",\n\x20\x20\x20\x20" << a.config().scaling << ",\n}"); }

            SS_MATH_OPS_INLINE auto inverse(Affine_Transformation const& a) noexcept -> Affine_Transformation { return Affine_Transformation{inverse(a.matrix())}; }
            SS_MATH_OPS_INLINE auto transpose(Affine_Transformation const& a) noexcept -> Affine_Transformation { return Affine_Transformation{transpose(a.matrix())}; }

            SS_MATH_OPS_INLINE auto rotation(Vector3 const& Euler_angles) noexcept -> Affine_Transformation { return rotation(Euler_to_quat(Euler_angles)); }
            SS_MATH_OPS_INLINE auto rotation(Quaternion const& a) noexcept -> Affine_Transformation { Affine_Transformation x; x.mutable_config().rotation = a; return x; }
            SS_MATH_OPS_INLINE auto position(Vector3 const& a) noexcept -> Affine_Transformation { Affine_Transformation x; x.mutable_config().position = a; return x; }
            SS_MATH_OPS_INLINE auto scaling(Vector3 const& a) noexcept -> Affine_Transformation { Affine_Transformation x; x.mutable_config().scaling = a; return x; }

            SS_MATH_OPS_INLINE auto operator | (Vector3 const& a, Affine_Transformation const& b) noexcept -> Vector3 { return b * a; }
            SS_MATH_OPS_INLINE auto operator | (Vector4 const& a, Affine_Transformation const& b) noexcept -> Vector4 { return b * a; }
            SS_MATH_OPS_INLINE auto operator | (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation { return b * a; }
        }
    }
}

#include <core/math/inline.undef.hpp>

