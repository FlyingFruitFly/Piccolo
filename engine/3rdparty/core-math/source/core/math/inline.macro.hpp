// No #pragma once intentionally
#ifdef SS_MATH_OPS_INLINE
    #undef SS_MATH_OPS_INLINE
#endif

#if 0
    #elif defined(__linux__) || defined(__APPLE__) || defined(__EMSCRIPTEN__)
        #ifdef SS_MATH_OPS_IMPLEMENTATION
            #define SS_MATH_OPS_INLINE
        #else
            #define SS_MATH_OPS_INLINE inline
        #endif

    #elif defined(_WIN32)
        #ifdef SS_MATH_OPS_IMPLEMENTATION
            #define SS_MATH_OPS_INLINE extern inline
        #else
            #define SS_MATH_OPS_INLINE extern inline
        #endif
#endif

#undef SS_MATH_OPS_IMPLEMENTATION

