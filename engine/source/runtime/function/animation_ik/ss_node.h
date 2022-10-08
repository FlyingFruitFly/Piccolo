#pragma once
#include "core/math/types.hpp"
#include "runtime/function/animation/node.h"
#include <memory>
#include <string>

namespace Piccolo
{
    class ssNode
    {
        friend class ssBone;

    public:
        // Enumeration denoting the spaces which a transform can be relative to.
        enum class TransformSpace
        {
            /// Transform is relative to the local space
            LOCAL,
            /// Transform is relative to the space of the parent pNode
            AREN,
            /// Transform is relative to object space
            OBJECT
        };
#ifdef _DEBUG
    public:
#else
    protected:
#endif
        ssNode* m_parent {nullptr};

        std::string m_name;

        /// Stores the orientation/position/scale of the pNode relative to it's parent.
        ss::math::Quaternion m_orientation {ss::math::Quaternion()};
        ss::math::Vector3    m_position {ss::math::Vector3(0, 0, 0)};
        ss::math::Vector3    m_scale {ss::math::Vector3(1, 1, 1)};

        // Cached combined orientation/position/scale.
        ss::math::Quaternion m_derived_orientation {ss::math::Quaternion()};
        ss::math::Vector3    m_derived_position {ss::math::Vector3()};
        ss::math::Vector3    m_derived_scale {ss::math::Vector3(1, 1, 1)};

        /// The position/orientation/scale to use as a base for keyframe animation
        ss::math::Vector3    m_initial_position {ss::math::Vector3()};
        ss::math::Quaternion m_initial_orientation {ss::math::Quaternion()};
        ss::math::Vector3    m_initial_scale {ss::math::Vector3(1, 1, 1)};

        ss::math::Matrix4 m_inverse_Tpose;

        bool m_is_dirty {true};

    protected:
        /// Only available internally - notification of parent.
        virtual void setParent(ssNode* parent);

    public:
        ssNode(const std::string name);
        virtual ~ssNode();
        void               clear();
        const std::string& getName(void) const;
        virtual ssNode*    getParent(void) const;

        virtual const ss::math::Quaternion& getOrientation() const;

        virtual void setOrientation(const ss::math::Quaternion& q);
        virtual void resetOrientation(void);

        virtual void                     setPosition(const ss::math::Vector3& pos);
        virtual const ss::math::Vector3& getPosition(void) const;

        virtual void                     setScale(const ss::math::Vector3& scale);
        virtual const ss::math::Vector3& getScale(void) const;

        virtual void scale(const ss::math::Vector3& scale);

        // Triggers the pNode to update it's combined transforms.
        virtual void updateDerivedTransform(void);

        virtual void translate(const ss::math::Vector3& d, TransformSpace relativeTo = TransformSpace::AREN);

        // Rotate the pNode around an aritrary axis using a Quarternion.
        virtual void rotate(const ss::math::Quaternion& q, TransformSpace relativeTo = TransformSpace::LOCAL);

        // Gets the orientation of the pNode as derived from all parents.
        virtual const ss::math::Quaternion& _getDerivedOrientation(void) const;
        virtual const ss::math::Vector3&    _getDerivedPosition(void) const;
        virtual const ss::math::Vector3&    _getDerivedScale(void) const;
        virtual const ss::math::Matrix4&    _getInverseTpose(void) const;

        // dirty and update
        virtual bool isDirty() const;
        virtual void setDirty();
        virtual void update();

        virtual void setAsInitialPose(void);
        virtual void resetToInitialPose(void);

        virtual const ss::math::Vector3&    getInitialPosition(void) const;
        virtual const ss::math::Quaternion& getInitialOrientation(void) const;
        virtual const ss::math::Vector3&    getInitialScale(void) const;
    };

    class ssBone : public ssNode
    {
        friend class ssSkeleton;

    protected:
        // physics simulation and actor status
        size_t m_id {0};
        size_t m_parent_id {0};

    public:
        ssBone();

        void   copyFrom(const Bone& bone);
        void   copyTo(Bone& bone);
        size_t getID(void) const;
    };
} // namespace Piccolo