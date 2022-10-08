#include "ss_Node.h"
#include "runtime/function/animation_ik/ss_Node.h"
#include "core/math/ops.hpp"
#include "function/animation/utilities.h"

namespace Piccolo
{
    //-----------------------------------------------------------------------
    ssNode::ssNode(const std::string name) { m_name = name; }
    ssNode::~ssNode()
    {
        // clear();
    }
    //-----------------------------------------------------------------------
    void ssNode::clear() {}
    //-----------------------------------------------------------------------
    ssNode* ssNode::getParent(void) const { return m_parent; }

    //-----------------------------------------------------------------------
    void ssNode::setParent(ssNode* parent)
    {
        m_parent = parent;
        setDirty();
    }
    //-----------------------------------------------------------------------
    void ssNode::update()
    {
        // Update transforms from parent
        updateDerivedTransform();
        m_is_dirty = false;
    }
    //-----------------------------------------------------------------------
    void ssNode::updateDerivedTransform(void)
    {
        if (m_parent)
        {
            // Update orientation
            const ss::math::Quaternion& parentOrientation = m_parent->_getDerivedOrientation();
            {
                // Combine orientation with that of parent
                m_derived_orientation = parentOrientation * m_orientation;
                m_derived_orientation = ss::math::op::normalize(m_derived_orientation);
            }

            // Update scale
            const ss::math::Vector3& parentScale = m_parent->_getDerivedScale();
            {
                // Scale own position by parent scale, NB just combine
                // as equivalent axes, no shearing
                m_derived_scale = parentScale * m_scale;
            }

            // Change position vector based on parent's orientation & scale
            m_derived_position = parentOrientation * (parentScale * m_position);

            // Add altered position vector to parents
            m_derived_position = m_derived_position + m_parent->_getDerivedPosition();
        }
        else
        {
            // Root ssNode, no parent
            m_derived_orientation = m_orientation;
            m_derived_position    = m_position;
            m_derived_scale       = m_scale;
        }
    }

    //-----------------------------------------------------------------------
    const ss::math::Quaternion& ssNode::getOrientation() const { return m_orientation; }

    //-----------------------------------------------------------------------
    void ssNode::setOrientation(const ss::math::Quaternion& q)
    {
        // ASSERT(!q.ss::math::op::isNaN() && "Invalid orientation supplied as parameter");
        if (ss::math::op::isNaN(q))
        {
            // LOG_ERROR(__FUNCTION__, "Invalid orientation supplied as parameter");
            m_orientation = ss::math::Quaternion();
        }
        else
        {
            m_orientation = q;
            m_orientation = ss::math::op::normalize(m_orientation);
        }
        setDirty();
    }
    //-----------------------------------------------------------------------
    void ssNode::resetOrientation(void)
    {
        m_orientation = ss::math::Quaternion();
        setDirty();
    }

    //-----------------------------------------------------------------------
    void ssNode::setPosition(const ss::math::Vector3& pos)
    {
        if (ss::math::op::isNaN(pos))
        {
            // LOG_ERROR
        }
        m_position = pos;
        setDirty();
    }

    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::getPosition(void) const { return m_position; }
    //-----------------------------------------------------------------------
    void ssNode::translate(const ss::math::Vector3& d, TransformSpace relativeTo)
    {
        switch (relativeTo)
        {
            case TransformSpace::LOCAL:
                // position is relative to parent so transform downwards
                m_position = m_position + m_orientation * d;
                break;
            case TransformSpace::OBJECT:
                // position is relative to parent so transform upwards
                if (m_parent)
                {
                    m_position =
                        m_position + (ss::math::op::inverse(m_parent->_getDerivedOrientation()) * d) / m_parent->_getDerivedScale();
                }
                else
                {
                    m_position = m_position + d;
                }
                break;
            case TransformSpace::AREN:
                m_position = m_position + d;
                break;
        }
        setDirty();
    }

    //-----------------------------------------------------------------------
    void ssNode::rotate(const ss::math::Quaternion& q, TransformSpace relativeTo)
    {
        // Normalize ss::math::Quaternionernion to avoid drift
        ss::math::Quaternion qnorm = ss::math::op::normalize(q);

        switch (relativeTo)
        {
            case TransformSpace::AREN:
                // Rotations are normally relative to local axes, transform up
                m_orientation = qnorm * m_orientation;
                break;
            case TransformSpace::OBJECT:
                // Rotations are normally relative to local axes, transform up
                m_orientation = m_orientation * ss::math::op::inverse(_getDerivedOrientation()) * qnorm *
                                _getDerivedOrientation();
                break;
            case TransformSpace::LOCAL:
                // Note the order of the mult, i.e. q comes after
                m_orientation = m_orientation * qnorm;
                break;
        }
        setDirty();
    }

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    const ss::math::Quaternion& ssNode::_getDerivedOrientation(void) const { return m_derived_orientation; }
    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::_getDerivedPosition(void) const { return m_derived_position; }
    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::_getDerivedScale(void) const { return m_derived_scale; }

    const ss::math::Matrix4& ssNode::_getInverseTpose(void) const { return m_inverse_Tpose; }

    //-----------------------------------------------------------------------
    void ssNode::setScale(const ss::math::Vector3& inScale)
    {
        if (ss::math::op::isNaN(inScale))
        {
            // LOG_ERROR
        }
        m_scale = inScale;
        setDirty();
    }
    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::getScale(void) const { return m_scale; }
    //-----------------------------------------------------------------------
    void ssNode::scale(const ss::math::Vector3& inScale)
    {
        m_scale = m_scale * inScale;
        setDirty();
    }
    //-----------------------------------------------------------------------
    const std::string& ssNode::getName(void) const { return m_name; }
    //-----------------------------------------------------------------------
    void ssNode::setAsInitialPose(void)
    {
        m_initial_position    = m_position;
        m_initial_orientation = m_orientation;
        m_initial_scale       = m_scale;
    }
    //-----------------------------------------------------------------------
    void ssNode::resetToInitialPose(void)
    {
        // m_position = {};// m_initial_position;
        // m_orientation = { {},0,0,0,1 };// m_initial_orientation;
        // m_scale = { {},1,1,1 };//m_initial_scale;
        m_position    = m_initial_position;
        m_orientation = m_initial_orientation;
        m_scale       = m_initial_scale;
        setDirty();
    }
    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::getInitialPosition(void) const { return m_initial_position; }
    //-----------------------------------------------------------------------
    const ss::math::Quaternion& ssNode::getInitialOrientation(void) const { return m_initial_orientation; }
    //-----------------------------------------------------------------------
    const ss::math::Vector3& ssNode::getInitialScale(void) const { return m_initial_scale; }
    //-----------------------------------------------------------------------
    void ssNode::setDirty() { m_is_dirty = true; }

    bool ssNode::isDirty() const { return m_is_dirty; }
    //---------------------------------------------------------------------
    ssBone::ssBone() : ssNode(std::string()) {}

    void ssBone::copyFrom(const Bone& bone) 
    { 
        m_id = bone.getID();
        m_parent_id = bone.m_parent_id;
        m_name      = bone.m_name;
        m_orientation = convertFrom(bone.m_orientation);
        m_position    = convertFrom(bone.m_position);
        m_scale       = convertFrom(bone.m_scale);
        m_derived_orientation = convertFrom(bone.m_derived_orientation);
        m_derived_position    = convertFrom(bone.m_derived_position);
        m_derived_scale       = convertFrom(bone.m_derived_scale);
    }

    void ssBone::copyTo(Bone& bone) 
    {
        bone.m_orientation    = convertFrom(m_orientation);
        bone.m_position       = convertFrom(m_position);
        bone.m_scale          = convertFrom(m_scale);
        bone.m_derived_orientation = convertFrom(m_derived_orientation);
        bone.m_derived_position    = convertFrom(m_derived_position);
        bone.m_derived_scale       = convertFrom(m_derived_scale);
    }

    size_t ssBone::getID(void) const { return m_id; }

//     void ssBone::initialize(std::shared_ptr<RawBone> definition, ssBone* parent_ssBone)
//     {
//         m_definition = definition;
// 
//         if (definition)
//         {
//             m_name = definition->name;
//             setOrientation(definition->binding_pose.m_rotation);
//             setPosition(definition->binding_pose.m_position);
//             setScale(definition->binding_pose.m_scale);
//             m_inverse_Tpose = definition->tpose_matrix;
//             setAsInitialPose();
//         }
//         m_parent = parent_ssBone;
//     }
// 
//     //---------------------------------------------------------------------
//     size_t ssBone::getID(void) const
//     {
//         if (m_definition)
//         {
//             return m_definition->index;
//         }
//         return std::numeric_limits<size_t>().max();
//     }
} // namespace Piccolo