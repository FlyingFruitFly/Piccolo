#include "ik_system.h"
#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/function/global/global_context.h"
#include "core/math/all.hpp"

namespace Piccolo
{
    std::map<std::string, std::shared_ptr<IKConfig>> IKManager::m_ik_config_cache;

    std::shared_ptr<IKConfig> IKManager::tryGetIKConfig(std::string ik_config_path)
    {

        std::shared_ptr<IKConfig> res;
        auto                      found = m_ik_config_cache.find(ik_config_path);
        if (found == m_ik_config_cache.end())
        {
            IKConfig data;
            g_runtime_global_context.m_asset_manager->loadAsset(ik_config_path, data);
            res = std::make_shared<IKConfig>();
            m_ik_config_cache.emplace(ik_config_path, res);
        }
        else
        {
            res = found->second;
        }
        return res;
    }

    void IKManager::resolve(Skeleton& skeleton, const BlendState& blend_state) 
    { 
        ssSkeleton converted_skeleton;
        converted_skeleton.copyFrom(skeleton);
        std::shared_ptr<IKConfig> ik_config = tryGetIKConfig(blend_state.ik_track_path);
        // do something
        ss::math::Quaternion test(0, 1, 0, 0);
        ssBone*              test_left_foot = converted_skeleton.getBoneByName("biped L Foot");
        if (test_left_foot == nullptr)
        {
            LOG_ERROR("cannot find");
            return;
        }
        test_left_foot->rotate(test);
        converted_skeleton.copyTo(skeleton);
    }
}
