#include "ss_skeleton.h"
#include "function/animation/utilities.h"

namespace Piccolo
{
    ssSkeleton::~ssSkeleton() 
    { 
        if (m_bones != nullptr)
        {
            delete[] m_bones;
        }
    }
    int  ssSkeleton::getBoneCount() const { return m_bone_count; }
    void ssSkeleton::copyFrom(Skeleton const& skeleton)
    {
        if (m_bone_count == skeleton.m_bone_count)
        {
            m_is_flat = skeleton.m_is_flat;
            for (size_t i = 0; i < m_bone_count; i++)
            {
                m_bones[i].copyFrom(skeleton.m_bones[i]);
            }
            return;
        }

        m_bone_count = skeleton.m_bone_count;
        if (m_bones != nullptr)
        {
            delete[] m_bones;
        }
        m_bones = new ssBone[m_bone_count];

        for (size_t i = 0; i < m_bone_count; i++)
        {
            m_bones[i].copyFrom(skeleton.m_bones[i]);
        }

        for (size_t i = 0; i < m_bone_count; i++)
        {
            m_bones[i].setParent(find_by_index(m_bones, m_bones[i].m_parent_id, m_bone_count, m_is_flat));
        }
    }

    void ssSkeleton::copyTo(Skeleton& skeleton) 
    {
        for (size_t i = 0; i < m_bone_count; i++)
        {
            m_bones[i].update();
        }
        for (size_t i = 0; i < m_bone_count; i++)
        {
            m_bones[i].copyTo(skeleton.m_bones[i]);
        }
    }

    ssBone* ssSkeleton::getBone(int i) 
    { 
        return &m_bones[i]; 
    }

    ssBone* ssSkeleton::getBoneByName(const std::string& name) const 
    {
        for (int i = 0; i < m_bone_count; i++)
        {
            if (m_bones[i].m_name == name)
            {
                return &m_bones[i];
            }
        }
        return nullptr;
    }
}

