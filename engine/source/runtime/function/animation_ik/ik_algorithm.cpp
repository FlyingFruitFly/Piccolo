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

    void XPBDIKSolver::calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement) 
    {
        // initialize data
        m_last_position.clear();
        m_position.clear();
        m_velocity.clear();
        m_length_constraints.clear();
        m_invmass.clear();
        m_skeleton = &skeleton;
        m_bone_count = skeleton.getBoneCount();

        for (int i = 0; i < m_bone_count; i++)
        {
            ssBone* bone = skeleton.getBone(i);
            m_last_position.push_back(bone->_getDerivedPosition());
            m_position.push_back(0.f);
            m_velocity.push_back(0.f);
         
             if (bone->getName() == "biped L Calf" || bone->getName() == "biped R Calf")
            {
                 m_force.push_back(DirectionForce(ss::math::Vector3(0.f, -0.2, 0.2f), bone->getID()));
            }

            float k = 1.f;
            if (bone->getName() == "biped L UpperArm" || bone->getName() == "biped R UpperArm" ||
                bone->getName() == "biped L Forearm" || bone->getName() == "biped R Forearm" ||
                bone->getName() == "biped L Hand" || bone->getName() == "biped R Hand" ||/*
                bone->getName() == "biped L Thigh" || bone->getName() == "biped R Thigh" ||*/
                bone->getName() == "biped L Calf" || bone->getName() == "biped R Calf" /*||
                bone->getName() == "biped L Foot" || bone->getName() == "biped R Foot"*/)
            {
                m_invmass.push_back(1.f);
            }
            else
            {
                m_invmass.push_back(0.001f);
            }

            if (bone->m_parent != bone)
            {
                m_length_constraints.push_back(
                    LengthConstraint(k, length(bone->getPosition()), bone->getID(), bone->m_parent_id));
            }
        }

        for (auto& force : m_force)
        {
            m_velocity[force.i] += force.m_force * m_invmass[force.i] * m_persudo_time;
        }
        // simulate for a while of time
        for (int i = 0; i < m_moment_step; i++)
        {
            processMoment();
        }

        reachByRotation();
        //for (int i = 0; i < m_bone_count; i++)
        //{
        //    skeleton.getBone(i)->m_derived_position = m_position[i];
        //}
        //skeleton.getBoneByName("biped L Toe0")->update();
        //skeleton.getBoneByName("biped R Toe0")->update();
    }

    void XPBDIKSolver::processMoment() 
    { 
        for (int i = 0; i < m_bone_count; i++)
        {
            m_position[i] = m_last_position[i] + m_velocity[i]; // + external force * invmass[i]
        }
        for (auto& end_effector : IKManager::m_end_effectors)
        {
            m_position[m_skeleton->getBoneByName(end_effector.first)->getID()] = end_effector.second;
        }
        for (auto& constraint : m_length_constraints)
        {
            constraint.resetLambda();
        }
        for (int i = 0; i < m_iter_times; i++)
        {
            processIter();
        }
        for (auto& end_effector : IKManager::m_end_effectors)
        {
            m_position[m_skeleton->getBoneByName(end_effector.first)->getID()] = end_effector.second;
        }
        for (int i = 0; i < m_bone_count; i++)
        {
            m_velocity[i] = m_position[i] - m_last_position[i];
            m_last_position[i] = m_position[i];
        }
    }

    void XPBDIKSolver::processIter() 
    {
        for (auto& constraint : m_length_constraints)
        {
            constraint.updateData(*this);

            int   i            = constraint.i;
            int   j            = constraint.j;

            // solve delta_lambda
            float alpha_tilde  = constraint.m_k / m_persudo_time_sqr;
            float delta_lambda = (-constraint.m_constraint_result - alpha_tilde * constraint.m_lambda) /
                                 (m_invmass[i] + m_invmass[j] + alpha_tilde);
            // solve delta_x
            ss::math::Vector3 correction_vector = delta_lambda * normalize(constraint.m_dx);

            // update
            constraint.m_lambda += delta_lambda;
            m_position[constraint.i] += m_invmass[i] * correction_vector;
            m_position[constraint.j] -= m_invmass[j] * correction_vector;
        }
    }

    void XPBDIKSolver::reachByRotation() 
    { 
        for (int i = 1; i < m_bone_count; i++)  // skip root bone
        {
            ssBone* bone = m_skeleton->getBone(i);
            bone->updateDerivedTransform();

            ss::math::Vector3 old_bone_direction(0, 0, 0);
            ss::math::Vector3 new_bone_direction(0, 0, 0);
            int               child_count = bone->m_children.size();

            if (child_count == 0)
            {
                continue;
            }

            for (auto& child : bone->m_children)
            {
                ssBone* child_bone = static_cast<ssBone*>(child);
                int     child_index = child_bone->getID();

                child_bone->updateDerivedTransform();
                old_bone_direction = old_bone_direction + child_bone->_getDerivedPosition();
                new_bone_direction = new_bone_direction + m_position[child_index];
            }

            old_bone_direction = old_bone_direction / float(child_count) - bone->_getDerivedPosition();
            new_bone_direction = new_bone_direction / float(child_count) - bone->_getDerivedPosition();

            ss::math::Quaternion parent_rotation = getRotationTo(old_bone_direction, new_bone_direction);
            bone->rotate(parent_rotation, ssNode::TransformSpace::OBJECT);
            bone->updateDerivedTransform();
        }
    }

    LengthConstraint::LengthConstraint(float k, float default_length, int i, int j) :
        m_k(k), m_lambda(0),m_default_length(default_length), i(i), j(j), m_dx(0, 0, 0), m_constraint_result(0.f)
    {}

    void LengthConstraint::resetLambda() 
    {
        m_lambda = 0.f;
    }

    void LengthConstraint::updateData(XPBDIKSolver& solver) 
    { 
        m_dx = solver.m_position[i] - solver.m_position[j];
        m_constraint_result = length(m_dx) - m_default_length;
    }

    DirectionForce::DirectionForce(ss::math::Vector3 force, int i) : m_force(force), i(i)
    {}

} // namespace Piccolo