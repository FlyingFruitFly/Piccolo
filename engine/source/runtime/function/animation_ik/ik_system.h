#pragma once
#include "ss_skeleton.h"
#include "runtime/resource/res_type/data/ik_config.h"

namespace Piccolo
{
    class GObject;

    class IKManager
    {
    private:
        static std::map<std::string, std::shared_ptr<IKConfig>> m_ik_config_cache;

    public:
        // for only one skeleton, object space
        static std::map<std::string, ss::math::Vector3> m_end_effectors;
        static std::map<std::string, ss::math::Quaternion> m_stable_rotation;
        static float                                    m_root_displacement;

        static std::shared_ptr<IKConfig> tryGetIKConfig(std::string ik_config_path);
        static void setTarget(Skeleton& skeleton, const Transform& object_transform, std::shared_ptr<IKConfig> ik_config);
        static void resolve(Skeleton& skeleton, const BlendState& blend_state, std::weak_ptr<GObject> m_parent_object);
    };
} // namespace Piccolo
