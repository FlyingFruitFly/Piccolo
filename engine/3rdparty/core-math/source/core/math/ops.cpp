#include "ops.hpp"
//! This file defines a copy of those inlined ops via #include-ing the header.
//! Those who use <core/math/ops.hpp> can then link successfully to
//! the copy of functions here.
//!
//! Heavy-weight functions, which are never inlined, are also defined here.
#include "constants.hpp"

#define SS_MATH_OPS_IMPLEMENTATION
#include "ops-inline.hpp"

namespace ss
{
    namespace math
    {
        static_assert(alignof(Vector1) >= alignof(float), "Bad alignment");
        static_assert(alignof(Vector2) >= alignof(glm::vec2), "Bad alignment");
        static_assert(alignof(Vector3) >= alignof(glm::vec3), "Bad alignment");
        static_assert(alignof(Vector4) >= alignof(glm::vec4), "Bad alignment");
        static_assert(alignof(Quaternion) >= alignof(glm::quat), "Bad alignment");
        static_assert(alignof(Matrix3) >= alignof(glm::mat3), "Bad alignment");
        static_assert(alignof(Matrix4) >= alignof(glm::mat4), "Bad alignment");

        static_assert(sizeof(Vector1) == sizeof(float), "Bad size");
        static_assert(sizeof(Vector2) == sizeof(glm::vec2), "Bad size");
        static_assert(sizeof(Vector3) == sizeof(glm::vec3), "Bad size");
        static_assert(sizeof(Vector4) == sizeof(glm::vec4), "Bad size");
        static_assert(sizeof(Quaternion) == sizeof(glm::quat), "Bad size");
        static_assert(sizeof(Matrix3) == sizeof(glm::mat3), "Bad size");
        static_assert(sizeof(Matrix4) == sizeof(glm::mat4), "Bad size");

        inline namespace op
        {
            namespace
            {
                auto normalize_quat(Quaternion const& a) noexcept -> Quaternion
                {
                    auto len = length(math::Vector4{a.x, a.y, a.z, a.w});
                    if (len == 0.0f) {
                        return {1.0f, 0.0f, 0.0f, 0.0f};
                    } else {
                        return a / len;
                    }
                }
            }

            // Modified from `mat3_normalized_to_quat` function in the Blender source code.
            // This is much more robust than the one from GLM.
            auto mat_to_quat(Matrix3 const& a) noexcept -> Quaternion
            {
                auto q = [&] () -> Quaternion {
                    auto tr = a.x.x + a.y.y + a.z.z + 1.0f;

                    if (tr > 4e-4f) {
                        auto s = std::sqrt(tr);
                        auto s2 = 0.5f / s;
                        return {
                            s * 0.5f,
                            (a.y.z - a.z.y) * s2,
                            (a.z.x - a.x.z) * s2,
                            (a.x.y - a.y.x) * s2,
                        };
                    } else {
                        if (a.x.x > a.y.y && a.x.x > a.z.z) {
                            auto s = std::sqrt(a.x.x - a.y.y - a.z.z + 1.0f);
                            auto s2 = 0.5f / s;
                            return {
                                (a.y.z - a.z.y) * s2,
                                s * 0.5f,
                                (a.x.y + a.y.x) * s2,
                                (a.z.x + a.x.z) * s2,
                            };
                        } else if (a.y.y > a.z.z) {
                            auto s = std::sqrt(a.y.y - a.x.x - a.z.z + 1.0f);
                            auto s2 = 0.5f / s;
                            return {
                                (a.z.x - a.x.z) * s2,
                                (a.x.y + a.y.x) * s2,
                                s * 0.5f,
                                (a.y.z + a.z.y) * s2,
                            };
                        } else {
                            auto s = std::sqrt(a.z.z - a.x.x - a.y.y + 1.0f);
                            auto s2 = 0.5f / s;
                            return {
                                (a.x.y - a.y.x) * s2,
                                (a.z.x + a.x.z) * s2,
                                (a.y.z + a.z.y) * s2,
                                s * 0.5f,
                            };
                        }
                    }
                } ();

                return normalize_quat(q);
            }

            // Modified from `quat_to_eulO` function in the Blender source code.
            // This implementation...
            // - ...does not have the gimbal lock problem.
            // - ...keeps "roll" zero when it should be zero (unlike glm::eulerAngles).
            auto quat_to_Euler(Quaternion const& a) noexcept -> Vector3
            {
                // This gives limited result:
                //
                //   return from_glm(glm::eulerAngles(as_glm(a)));
                //
                // The Yaw is restricted to range (-π/2, π/2),
                // which means you cannot look behind.
                //
                // And that's why the Blender's implementation is used.

                auto mat = quat_to_mat(a);
                auto cy = std::hypot(mat[2][2], mat[2][0]);

                if (cy > math::eps) {
                    auto Euler1 = Vector3{
                        glm::atan(-mat[2][1], cy),
                        glm::atan(mat[2][0], mat[2][2]),
                        glm::atan(mat[0][1], mat[1][1]),
                    };

                    auto Euler2 = Vector3{
                        glm::atan(-mat[2][1], -cy),
                        glm::atan(-mat[2][0], -mat[2][2]),
                        glm::atan(-mat[0][1], -mat[1][1]),
                    };

                    auto d1 = glm::abs(Euler1.x) + glm::abs(Euler1.y) + glm::abs(Euler1.z);
                    auto d2 = glm::abs(Euler2.x) + glm::abs(Euler2.y) + glm::abs(Euler2.z);
                    return (d1 < d2 ? Euler1 : Euler2);
                } else {
                    return {
                        glm::atan(-mat[2][1], cy),
                        0.0f,
                        glm::atan(-mat[1][0], mat[0][0]),
                    };
                }
            }

            // Modified from `eulO_to_quat` function in the Blender source code.
            auto Euler_to_quat(Vector3 const& Euler_angles) noexcept -> Quaternion
            {
                auto ti = Euler_angles.z * 0.5f;
                auto tj = Euler_angles.x * 0.5f;
                auto tk = Euler_angles.y * 0.5f;

                auto ci = glm::cos(ti);
                auto cj = glm::cos(tj);
                auto ck = glm::cos(tk);

                auto si = glm::sin(ti);
                auto sj = glm::sin(tj);
                auto sk = glm::sin(tk);

                auto cc = ci * ck;
                auto cs = ci * sk;
                auto sc = si * ck;
                auto ss = si * sk;

                return { // wxyz order
                    cj * cc + sj * ss,
                    cj * ss + sj * cc,
                    cj * cs - sj * sc,
                    cj * sc - sj * cs,
                };
            }

            bool isNaN(Vector3 const& vec)
            {
                return std::isnan(vec.x) || std::isnan(vec.y) || std::isnan(vec.z);
            }

            bool isNaN(Quaternion const& quat)
            {
                return std::isnan(quat.x) || std::isnan(quat.y) || std::isnan(quat.z) || std::isnan(quat.w);
            }

            ss::math::type::Quaternion getRotationTo(const Vector3 & origin, const Vector3 & dest, const Vector3 & fallbackAxis)
            {
                Quaternion q;
                Vector3 v0 = normalize(origin);
                Vector3 v1 = normalize(dest);

                float d = dot(v0,v1);
                if (d >= 1.0f)
                {
                    return Quaternion(1,0,0,0);
                }
                if (d < 1e-6f - 1.0f)
                {
                    if (fallbackAxis != Vector3(0, 0, 0))
                    {
                        q = quat_from_angle_axis(pi, fallbackAxis);
                    }
                    else
                    {
                        Vector3 axis = cross(Vector3(1,0,0), origin);
                        if (length(axis) < 0.0001f)
                        {
                            axis = cross(Vector3(0,1,0), origin);
                        }
                        normalize(axis);
                        q = quat_from_angle_axis(pi, axis);
                    }
                }
                else
                {
                    float s = sqrt((1+d)*2);
                    float invs = 1/s;
                    Vector3 c = cross(v0, v1);
                    q.x = c.x*invs;
                    q.y = c.y*invs;
                    q.z = c.z*invs;
                    q.w = s*0.5f;
                    q = normalize(q);
                }
                return q;
            }
        }
    }
}

