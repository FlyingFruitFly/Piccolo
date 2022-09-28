#pragma once
//! All math types with accessor member functions.
//!
//! - Vectors default initialize to zero vectors.
//! - Quaternions default initialize to no rotation.
//! - Matrices default initialize to identity matrices.

namespace ss
{
    namespace math
    {
        inline namespace type
        {
            // A monadic container for a single float value.
            // It has NO REAL USE but exists for type completeness and consistency.
            CCTT_INTROSPECT();
            struct alignas(4) Vector1 final
            {
                float x;

                constexpr Vector1(float x) noexcept: x{x} {}
                constexpr Vector1() noexcept: Vector1{0.0f} {}

                // A special feature that only Vector1 has: non-explicit degrading conversion.
                // (Or, automatic "return" in monads jargon).
                constexpr operator float() const noexcept { return x; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return &x; }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return &x; }

                constexpr auto operator [] (int i)       noexcept -> float&       { return ptr()[i]; }
                constexpr auto operator [] (int i) const noexcept -> float const& { return ptr()[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(8) Vector2 final
            {
                float x;
                float y;

                constexpr Vector2(float x, float y) noexcept: x{x}, y{y} {}
                constexpr Vector2(float x) noexcept: Vector2{x, x} {}
                constexpr Vector2() noexcept: Vector2{0.0f} {}

                constexpr explicit operator Vector1() const noexcept { return {x}; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return &x; }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return &x; }

                constexpr auto operator [] (int i)       noexcept -> float&       { return ptr()[i]; }
                constexpr auto operator [] (int i) const noexcept -> float const& { return ptr()[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(4) Vector3 final
            {
                float x;
                float y;
                float z;

                constexpr Vector3(float x, float y, float z) noexcept: x{x}, y{y}, z{z} {}
                constexpr Vector3(float x) noexcept: Vector3{x, x, x} {}
                constexpr Vector3() noexcept: Vector3{0.0f} {}

                constexpr explicit Vector3(Vector2 xy, float z=0.0f) noexcept: Vector3{xy.x, xy.y, z} {}
                constexpr explicit Vector3(float x, Vector2 yz) noexcept: Vector3{x, yz.x, yz.y} {}

                constexpr explicit operator Vector1() const noexcept { return {x}; }
                constexpr explicit operator Vector2() const noexcept { return {x, y}; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return &x; }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return &x; }

                constexpr auto operator [] (int i)       noexcept -> float&       { return ptr()[i]; }
                constexpr auto operator [] (int i) const noexcept -> float const& { return ptr()[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(8) Vector4 final
            {
                float x;
                float y;
                float z;
                float w;

                constexpr Vector4(float x, float y, float z, float w) noexcept: x{x}, y{y}, z{z}, w{w} {}
                constexpr Vector4(float x) noexcept: Vector4{x, x, x, x} {}
                constexpr Vector4() noexcept: Vector4{0.0f} {}

                constexpr explicit Vector4(Vector3 xyz, float w=0.0f) noexcept: Vector4{xyz.x, xyz.y, xyz.z, w} {}
                constexpr explicit Vector4(float x, Vector3 yzw) noexcept: Vector4{x, yzw.x, yzw.y, yzw.z} {}
                constexpr explicit Vector4(Vector2 xy, Vector2 zw) noexcept: Vector4{xy.x, xy.y, zw.x, zw.y} {}

                constexpr explicit operator Vector1() const noexcept { return {x}; }
                constexpr explicit operator Vector2() const noexcept { return {x, y}; }
                constexpr explicit operator Vector3() const noexcept { return {x, y, z}; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return &x; }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return &x; }

                constexpr auto operator [] (int i)       noexcept -> float&       { return ptr()[i]; }
                constexpr auto operator [] (int i) const noexcept -> float const& { return ptr()[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(8) Quaternion final
            {
                // Must be XYZW order!
                // This keeps compatibility with GLM.
                float x;
                float y;
                float z;
                float w;

                // Must be WXYZ order!
                // This is different from data layout.
                // It IS weird. But it keeps compatibility with GLM.
                constexpr Quaternion(float w, float x, float y, float z) noexcept: x{x}, y{y}, z{z}, w{w} {}
                constexpr Quaternion() noexcept: Quaternion{1.0f, 0.0f, 0.0f, 0.0f} {}

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return &x; }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return &x; }

                constexpr auto operator [] (int i)       noexcept -> float&       { return ptr()[i]; }
                constexpr auto operator [] (int i) const noexcept -> float const& { return ptr()[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(4) Matrix3 final
            {
                Vector3 x;
                Vector3 y;
                Vector3 z;

                constexpr explicit Matrix3(Vector3 x, Vector3 y, Vector3 z) noexcept: x{x}, y{y}, z{z} {}
                constexpr explicit Matrix3(Vector3 diag) noexcept
                    : x{diag.x, {}, {}}
                    , y{{}, diag.y, {}}
                    , z{{}, {}, diag.z}
                {}
                constexpr Matrix3() noexcept: Matrix3{Vector3{1.0f}} {}

                constexpr explicit Matrix3(float xdiag, float ydiag, float zdiag) noexcept: Matrix3{Vector3{xdiag, ydiag, zdiag}} {}
                constexpr explicit Matrix3(float diag) noexcept: Matrix3{Vector3{diag}} {}

                constexpr explicit operator Vector1() const noexcept { return {x.x}; }
                constexpr explicit operator Vector2() const noexcept { return {x.x, y.y}; }
                constexpr explicit operator Vector3() const noexcept { return {x.x, y.y, z.z}; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return x.ptr(); }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return x.ptr(); }

                constexpr auto operator [] (int i)       noexcept -> Vector3&       { return (&x)[i]; }
                constexpr auto operator [] (int i) const noexcept -> Vector3 const& { return (&x)[i]; }
            };

            CCTT_INTROSPECT();
            struct alignas(8) Matrix4 final
            {
                Vector4 x;
                Vector4 y;
                Vector4 z;
                Vector4 w;

                constexpr explicit Matrix4(Vector4 x, Vector4 y, Vector4 z, Vector4 w) noexcept: x{x}, y{y}, z{z}, w{w} {}
                constexpr explicit Matrix4(Vector4 diag) noexcept
                    : x{diag.x, {}, {}, {}}
                    , y{{}, diag.y, {}, {}}
                    , z{{}, {}, diag.z, {}}
                    , w{{}, {}, {}, diag.w}
                {}
                constexpr Matrix4() noexcept: Matrix4{Vector4{1.0f}} {}

                constexpr explicit Matrix4(float xdiag, float ydiag, float zdiag, float wdiag=1.0f) noexcept: Matrix4{Vector4{xdiag, ydiag, zdiag, wdiag}} {}
                constexpr explicit Matrix4(float diag) noexcept: Matrix4{Vector4{diag}} {}

                constexpr explicit Matrix4(Vector3 diag, float wdiag=1.0f) noexcept: Matrix4{Vector4{diag, wdiag}} {}

                constexpr explicit Matrix4(Vector3 x, Vector3 y, Vector3 z, Vector3 pos={}) noexcept
                    : Matrix4{
                        Vector4{x},
                        Vector4{y},
                        Vector4{z},
                        Vector4{pos, 1.0f},
                    }
                {}
                constexpr explicit Matrix4(Matrix3 a, Vector3 pos={}) noexcept: Matrix4{a.x, a.y, a.z, pos} {}

                constexpr explicit operator Vector1() const noexcept { return {x.x}; }
                constexpr explicit operator Vector2() const noexcept { return {x.x, y.y}; }
                constexpr explicit operator Vector3() const noexcept { return {x.x, y.y, z.z}; }
                constexpr explicit operator Vector4() const noexcept { return {x.x, y.y, z.z, w.w}; }
                constexpr explicit operator Matrix3() const noexcept { return Matrix3{Vector3{x}, Vector3{y}, Vector3{z}}; }

                CCTT_INTROSPECT(overload <() noexcept -> float*> ptr);
                constexpr auto ptr() noexcept -> float* { return x.ptr(); }

                CCTT_INTROSPECT(overload <() const noexcept -> float const*> cptr);
                constexpr auto ptr() const noexcept -> float const* { return x.ptr(); }

                constexpr auto operator [] (int i)       noexcept -> Vector4&       { return (&x)[i]; }
                constexpr auto operator [] (int i) const noexcept -> Vector4 const& { return (&x)[i]; }
            };
        }
    }
}

