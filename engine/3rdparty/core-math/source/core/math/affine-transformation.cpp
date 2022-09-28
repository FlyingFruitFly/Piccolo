#include "affine-transformation.hpp"
//! This file defines a copy of those inlined ops via #include-ing the header.
//! Those who use <core/math/affine-transformation.hpp> can then link successfully to
//! the copy of functions here.
//!
//! Heavy-weight functions, which are never inlined, are also defined here.
#include "ops-inline.hpp"

#define SS_MATH_OPS_IMPLEMENTATION
#include "affine-transformation-inline.hpp"

namespace ss
{
    namespace math
    {
        namespace
        {
            auto normalize_in_place_for_size(Vector3& a) noexcept -> float
            {
                constexpr auto eps = 1e-16f;

                auto len = length(a);
                if (len < eps) {
                    a = 0.0f;
                    return 0.0f;
                } else {
                    a /= len;
                    return len;
                }
            }

            auto is_left_handed(Matrix3 const& m) noexcept -> bool
            {
                return (dot(cross(m[0], m[1]), m[2]) < 0.0f);
            }
        }

        auto Affine_Transformation::update_matrix_if_outdated() const noexcept -> void
        {
            if (outdated_ != Outdated::matrix) return;
            outdated_ = Outdated::none;

            matrix_ = Matrix4{
                quat_to_mat(config_.rotation) * Matrix3{config_.scaling},
                config_.position,
            };
        }

        auto Affine_Transformation::update_config_if_outdated() const noexcept -> void
        {
            if (outdated_ != Outdated::config) return;
            outdated_ = Outdated::none;

            auto position = math::Vector3{matrix_[3]};
            auto rotation = math::Matrix3{matrix_};
            auto scaling = math::Vector3{
                normalize_in_place_for_size(rotation[0]),
                normalize_in_place_for_size(rotation[1]),
                normalize_in_place_for_size(rotation[2]),
            };

            if (is_left_handed(rotation)) {
                rotation = -rotation;
                scaling = -scaling;
            }

            config_ = {
                mat_to_quat(rotation),
                position,
                scaling,
            };
        }

        inline namespace op
        {
            auto rotate(Affine_Transformation& xform, Vector3 const& offset_euler_angles) noexcept -> void
            {
                auto euler_angles = quat_to_Euler(xform.config().rotation);
                euler_angles += offset_euler_angles;
                euler_angles.x = glm::clamp(euler_angles.x, glm::radians(-89.0f), glm::radians(89.0f));
                xform.mutable_config().rotation = Euler_to_quat(euler_angles);
            }
        }
    }
}

