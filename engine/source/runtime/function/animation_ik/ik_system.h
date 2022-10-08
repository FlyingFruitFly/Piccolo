#pragma once
#include "ss_skeleton.h"
#include "runtime/resource/res_type/data/ik_config.h"

namespace Piccolo
{
    class IKManager
    {
    private:
        static std::map<std::string, std::shared_ptr<IKConfig>> m_ik_config_cache;

    public:
        static std::shared_ptr<IKConfig> tryGetIKConfig(std::string ik_config_path);
        static void resolve(Skeleton& skeleton, const BlendState& blend_state);
    };
} // namespace Piccolo
