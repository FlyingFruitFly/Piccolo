#include "ik_system.h"
#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/physics/physics_scene.h"
#include "runtime/function/framework/world/world_manager.h"
#include "core/math/all.hpp"
#include "function/animation/utilities.h"
#include "runtime/function/animation_ik/ik_algorithm.h"
#include <iostream>
#include <ctime>

namespace Piccolo
{
    std::map<std::string, std::shared_ptr<IKConfig>> IKManager::m_ik_config_cache;
    std::map<std::string, ss::math::Vector3>         IKManager::m_end_effectors;
    std::map<std::string, ss::math::Quaternion>      IKManager::m_stable_rotation;
    float                                            IKManager::m_root_displacement = 0.f;

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

    void IKManager::setTarget(Skeleton& skeleton, const Transform& object_transform, std::shared_ptr<IKConfig> ik_config) 
    {
        std::shared_ptr<PhysicsScene> physics_scene =
            g_runtime_global_context.m_world_manager->getCurrentActivePhysicsScene().lock();
        ASSERT(physics_scene);
        m_root_displacement = 0.f;

        std::vector<std::string>    foot_names;
        foot_names.push_back("biped L Foot");
        foot_names.push_back("biped R Foot");

        for (auto const& bone_name : foot_names)
        {

            if (false)
            {
                std::vector<PhysicsHitInfo> hits;
                bool                        first       = true;
                float                       max_z       = 0;
                float                       max_step_up = 0.5;

                Vector3 foot_position = skeleton.getBoneByName(bone_name)->_getDerivedPosition();
                float   foot_height   = foot_position.z;
                if (physics_scene->raycast(transformPositionToWorld(foot_position, object_transform) +
                                               Vector3(0, 0, max_step_up),
                                           Vector3::NEGATIVE_UNIT_Z,
                                           2.0f,
                                           hits))
                {
                    Vector3 hit_position;
                    for (auto& hit : hits)
                    {
                        if (first || hit.hit_position.z > max_z)
                        {
                            max_z        = hit.hit_position.z;
                            hit_position = hit.hit_position;
                            first        = false;
                        }
                    }
                    Vector3 hit_position_in_object = transformPositionToLocal(hit_position, object_transform);
                    if (hit_position_in_object.z < m_root_displacement)
                    {
                        m_root_displacement = hit_position_in_object.z;
                    }
                    m_end_effectors[bone_name] = convertFrom(hit_position_in_object + Vector3(0, 0, foot_height));
                }
                else
                {
                    m_end_effectors[bone_name] = convertFrom(foot_position);
                }
            }
        }

        m_end_effectors["biped L Foot"] =
            convertFrom(skeleton.getBoneByName("biped L Foot")->_getDerivedPosition() + Vector3(0, -0.2, 0.4));
        m_end_effectors["biped R Foot"] =
            convertFrom(skeleton.getBoneByName("biped R Foot")->_getDerivedPosition() + Vector3(0, 0.2, 0.4));
        m_stable_rotation["biped L Foot"] =
            convertFrom(skeleton.getBoneByName("biped L Foot")->_getDerivedOrientation());
        m_stable_rotation["biped R Foot"] =
            convertFrom(skeleton.getBoneByName("biped R Foot")->_getDerivedOrientation());
        //      m_end_effectors["biped L Hand"] =
//            convertFrom(skeleton.getBoneByName("biped L Hand")->_getDerivedPosition() + Vector3(0.4, 0, 0.4));
//        m_end_effectors["biped Head"] =
//            convertFrom(skeleton.getBoneByName("biped Head")->_getDerivedPosition());
        
    }

    void IKManager::resolve(Skeleton& skeleton, const BlendState& blend_state, std::weak_ptr<GObject> parent_object) 
    {
        if (!parent_object.lock())
            return;

        TransformComponent* transform_component = parent_object.lock()->tryGetComponent(TransformComponent);
        Transform           object_transform    = transform_component->getTransform();

        ssSkeleton converted_skeleton;
        converted_skeleton.copyFrom(skeleton);
        std::shared_ptr<IKConfig> ik_config = tryGetIKConfig(blend_state.ik_track_path);
        // do something
        setTarget(skeleton, object_transform, ik_config);
        XPBDIKSolver solver;

        clock_t start, end;
        start = clock();

        solver.calculateIKResult(*ik_config, converted_skeleton, m_root_displacement);
        //         ss::math::Quaternion test(0, 1, 0, 0);
//         ssBone*              test_left_foot = converted_skeleton.getBoneByName("biped L Foot");
//         if (test_left_foot == nullptr)
//         {
//             LOG_ERROR("cannot find");
//             return;
//         }
//        test_left_foot->rotate(test);
        for (auto& iter : m_stable_rotation)
        {
            ssBone* bone = converted_skeleton.getBoneByName(iter.first);
            bone->setOrientation(inverse(bone->getParent()->_getDerivedOrientation()) * iter.second);
            bone->m_derived_orientation = iter.second;
        }

        end = clock();
        double time_used = (double)(end - start) / CLOCKS_PER_SEC;
        static double time_sum  = 0;
        time_sum += time_used;
        static int test_cnt  = 0;
        test_cnt             = (test_cnt + 1) % 100;
        if (test_cnt == 0)
        {
            printf("%.4f s\n", time_sum/100);
            time_sum = 0;
        }
        

        converted_skeleton.copyTo(skeleton);
        static float max_delta=0.0f;
        for (auto iter : m_end_effectors)
        {
            ss::math::Vector3 actural_position = converted_skeleton.getBoneByName(iter.first)->_getDerivedPosition();
            float             now_delta        = length(iter.second - actural_position);
            if (now_delta > max_delta)
            {
                max_delta = now_delta;
                printf("%f\n", max_delta);
            }
        }
    }
}
