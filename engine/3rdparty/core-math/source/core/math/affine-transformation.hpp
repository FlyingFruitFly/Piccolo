#pragma once
//! Defines an Affine_Transformation type to simplify conversion
//! between matrices and scaling/rotation/position components.
//!
//! Light-weight type conversion/forwarding functions are inlined.
//! Functions requiring math operations generate function calls.
//! To get them inlined, you can #include <core/math/affine-transformation-inline.hpp>.
//! To get their math operations inlined, you can #include <core/math/ops-inline.hpp> together.
//!
//! Heavy-weight functions are never inlined.
#include "types.hpp"
#include <iosfwd>

namespace ss
{
    namespace math
    {
        CCTT_INTROSPECT();
        struct Affine_Transformation final
        {
            struct Config final
            {
                Quaternion rotation{};
                Vector3 position{};
                Vector3 scaling{1.0f};
            };

            Affine_Transformation() noexcept { mark_matrix_outdated(false); }
            Affine_Transformation(Config config_) noexcept: config_{config_} { mark_matrix_outdated(false); }

            Affine_Transformation(Matrix3 const& rot_scale, Vector3 const& pos) noexcept
                : Affine_Transformation{Matrix4{rot_scale, pos}}
            {}

            explicit Affine_Transformation(Matrix4 const& m) noexcept: matrix_{m} { mark_config_outdated(false); }

            CCTT_INTROSPECT(ignore);
            explicit operator Matrix4 () const noexcept { return matrix(); }

            auto         matrix() const noexcept -> Matrix4 const& { update_matrix_if_outdated(); return matrix_; }
            auto mutable_matrix()       noexcept -> Matrix4&       {      mark_config_outdated(); return matrix_; }

            auto         config() const noexcept -> Config const& { update_config_if_outdated(); return config_; }
            auto mutable_config()       noexcept -> Config&       {      mark_matrix_outdated(); return config_; }

        private:
            enum struct Outdated
            {
                none,
                matrix,
                config,
            };

            mutable Matrix4 matrix_{};
            mutable Config config_{};
            mutable Outdated outdated_{};

            auto mark_matrix_outdated(bool update=true) const noexcept -> void { if (update) update_config_if_outdated(); outdated_ = Outdated::matrix; }
            auto mark_config_outdated(bool update=true) const noexcept -> void { if (update) update_matrix_if_outdated(); outdated_ = Outdated::config; }

            auto update_matrix_if_outdated() const noexcept -> void;
            auto update_config_if_outdated() const noexcept -> void;
        };

        inline namespace op
        {
            CCTT_INTROSPECT(overload<(ss::math::Affine_Transformation&, ss::math::Quaternion const&) noexcept -> void> rotate_by_quat)
            auto rotate(Affine_Transformation& xform, Quaternion const& rot) noexcept -> void;

            CCTT_INTROSPECT(overload<(ss::math::Affine_Transformation&, ss::math::Vector3 const&) noexcept -> void> rotate_by_Euler_angles)
            auto rotate(Affine_Transformation& xform, Vector3 const& offset_Euler_angles) noexcept -> void;

            CCTT_INTROSPECT(overload<(ss::math::Affine_Transformation&, ss::math::Matrix3 const&) noexcept -> void> rotate_by_mat3)
            auto rotate(Affine_Transformation& xform, Matrix3 const& x) noexcept -> void;

            CCTT_INTROSPECT(overload<(ss::math::Affine_Transformation&, ss::math::Matrix4 const&) noexcept -> void> rotate_by_mat4)
            auto rotate(Affine_Transformation& xform, Matrix4 const& x) noexcept -> void;

            CCTT_INTROSPECT();
            auto xrotate(Affine_Transformation& xform, float a) noexcept -> void;

            CCTT_INTROSPECT();
            auto yrotate(Affine_Transformation& xform, float a) noexcept -> void;

            CCTT_INTROSPECT();
            auto zrotate(Affine_Transformation& xform, float a) noexcept -> void;

            CCTT_INTROSPECT();
            auto move_globally(Affine_Transformation& xform, Vector3 const& offset) noexcept -> void;

            CCTT_INTROSPECT();
            auto move_locally(Affine_Transformation& xform, Vector3 const& offset)  noexcept -> void;

            CCTT_INTROSPECT();
            auto scale(Affine_Transformation& xform, Vector3 const& factor) noexcept -> void;

            auto operator == (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> bool;
            auto operator == (Affine_Transformation const& a, Matrix4 const& b) noexcept -> bool;
            auto operator == (Matrix4 const& a, Affine_Transformation const& b) noexcept -> bool;

            auto operator != (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> bool;
            auto operator != (Affine_Transformation const& a, Matrix4 const& b) noexcept -> bool;
            auto operator != (Matrix4 const& a, Affine_Transformation const& b) noexcept -> bool;

            auto operator *= (Affine_Transformation& a, Affine_Transformation const& b) noexcept -> Affine_Transformation&;
            auto operator *= (Affine_Transformation& a, Matrix4 const& b) noexcept -> Affine_Transformation&;
            auto operator *= (Matrix4& a, Affine_Transformation const& b) noexcept -> Matrix4&;

            auto operator * (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation;
            auto operator * (Affine_Transformation const& a, Matrix4 const& b) noexcept -> Affine_Transformation;
            auto operator * (Matrix4 const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation;

            auto operator * (Affine_Transformation const& a, Vector3 const& b) noexcept -> Vector3;
            auto operator * (Affine_Transformation const& a, Vector4 const& b) noexcept -> Vector4;

            auto operator * (Vector3 const& a, Affine_Transformation const& b) noexcept -> Vector3;
            auto operator * (Vector4 const& a, Affine_Transformation const& b) noexcept -> Vector4;

            auto operator << (std::ostream& o, Affine_Transformation const& a) noexcept -> std::ostream&;

            auto inverse(Affine_Transformation const& a) noexcept -> Affine_Transformation;
            auto transpose(Affine_Transformation const& a) noexcept -> Affine_Transformation;

            // Euler_angles.x: Rotation around X-axis (pitch)
            // Euler_angles.y: Rotation around Y-axis (yaw)
            // Euler_angles.z: Rotation around Z-axis (roll)
            // The Euler angles ordering is ZXY.
            auto rotation(Vector3 const& Euler_angles) noexcept -> Affine_Transformation;
            auto rotation(Quaternion const& a) noexcept -> Affine_Transformation;
            auto position(Vector3 const& a) noexcept -> Affine_Transformation;
            auto scaling(Vector3 const& a) noexcept -> Affine_Transformation;

            // Pipe ("then") operators.
            // > auto p1 = p0 | transform0 | transform1 | transform2;
            // > assert(p1 == transform2 * (transform1 * (transform0 * p0)));
            auto operator | (Vector3 const& a, Affine_Transformation const& b) noexcept -> Vector3;
            auto operator | (Vector4 const& a, Affine_Transformation const& b) noexcept -> Vector4;
            auto operator | (Affine_Transformation const& a, Affine_Transformation const& b) noexcept -> Affine_Transformation;
        }
    }
}

