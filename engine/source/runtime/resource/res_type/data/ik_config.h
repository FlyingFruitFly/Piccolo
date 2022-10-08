#pragma once
#include "runtime/core/math/transform.h"
#include "runtime/core/meta/reflection/reflection.h"
#include <string>
#include <vector>
namespace Piccolo
{

    REFLECTION_TYPE(IKConfig)
    CLASS(IKConfig, Fields)
    {
        REFLECTION_BODY(IKConfig);

    public:
        std::vector<int> convert;
    };
} // namespace Piccolo