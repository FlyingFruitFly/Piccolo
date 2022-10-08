#pragma once
#include "runtime/function/animation/skeleton.h"
#include "runtime/function/animation_ik/ss_node.h"

namespace Piccolo
{
    class ssSkeleton
    {
    private:
        bool    m_is_flat {false};
        size_t  m_bone_count {0};
        ssBone* m_bones {nullptr};

    public:
        ~ssSkeleton();

        int  getBoneCount() const;
        void copyFrom(Skeleton const& skeleton);
        void copyTo(Skeleton &skeleton);
        ssBone* getBoneByName(const std::string& name) const;
    };
}