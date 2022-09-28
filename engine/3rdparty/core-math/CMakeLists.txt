project(core-math)

add_library(core-math STATIC)
file(GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    "source/*.cpp"
)
target_sources(core-math PRIVATE ${sources})
target_include_directories(core-math SYSTEM PUBLIC source)
target_include_directories(core-math SYSTEM PUBLIC library-glm/include)
target_compile_options(core-math PUBLIC -DGLM_ENABLE_EXPERIMENTAL=1 -DGLM_FORCE_RADIANS=1 -DGLM_FORCE_SIZE_FUNC=1)
file(GLOB
    cctt_header
    CONFIGURE_DEPENDS
    "introspect.hpp"
)
target_compile_options(core-math PUBLIC "SHELL:$<IF:$<CXX_COMPILER_ID:MSVC>,-FI,-include> ${cctt_header}")
target_compile_options(core-math PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:$<IF:$<CXX_COMPILER_ID:MSVC>,-std:c++20,-std=c++20>>")

