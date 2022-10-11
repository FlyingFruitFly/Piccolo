#include "runtime/function/animation_ik/ik_algorithm.h"
#include "runtime/function/animation_ik/ik_system.h"
#include "core/math/all.hpp"
#include "runtime/core/math/math.h"

namespace Piccolo
{
    void TwoBoneIKSolver::calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement)
    {
        for (auto& end_effector : IKManager::m_end_effectors)
        {
            std::string       name            = end_effector.first;
            ss::math::Vector3 target_position = end_effector.second;
            target_position.z -= root_displacement;

            ssBone* end_joint = skeleton.getBoneByName(name);
            assert(end_joint);
            ssBone* mid_joint = static_cast<ssBone*>(end_joint->getParent());
            assert(mid_joint);
            ssBone* start_joint = static_cast<ssBone*>(mid_joint->getParent());
            assert(start_joint);

            ss::math::Vector3 end_position = end_joint->_getDerivedPosition();
            ss::math::Vector3 mid_position = mid_joint->_getDerivedPosition();
            ss::math::Vector3 start_position = start_joint->_getDerivedPosition();

            ss::math::Vector3 ik_vector = mid_position - start_position;
            ss::math::Vector3 origin_target = target_position - start_position;
            ss::math::Vector3 pole_vector   = cross(origin_target, ik_vector);
            ss::math::Vector3 proj_dir      = normalize(cross(pole_vector, origin_target));
            ss::math::Vector3 rad_dir       = normalize(origin_target);
            ss::math::Vector3 mid_target;

            float a = length(mid_position - start_position);
            float b = length(end_position - mid_position);
            float c = length(origin_target);

            if (a + b <= c)
            {
                mid_target = start_position + rad_dir * a;
                target_position = start_position + rad_dir * (a + b);
            }
            else
            {
                float cos_angle = (a * a + c * c - b * b) / (a * c * 2);
                float sin_angle = Math::sqrt(1 - cos_angle * cos_angle);
                float proj_dist = a * sin_angle;
                float rad_dist  = a * cos_angle;
                mid_target      = start_position + (proj_dir * proj_dist) + (rad_dir * rad_dist);
            }

            ss::math::Quaternion start_rotation =
                getRotationTo(mid_position - start_position, mid_target - start_position);
            start_joint->rotate(start_rotation, ssNode::TransformSpace::OBJECT);
            start_joint->updateDerivedTransform();
            mid_joint->updateDerivedTransform();
            end_joint->updateDerivedTransform();

            ss::math::Quaternion mid_rotation = getRotationTo(
                end_joint->_getDerivedPosition() - mid_joint->_getDerivedPosition(), target_position - mid_target);
            mid_joint->rotate(mid_rotation, ssNode::TransformSpace::OBJECT);
        }
        ssBone* root = skeleton.getBoneByName("root");
        root->translate(ss::math::Vector3(0,0,root_displacement));
    }

}