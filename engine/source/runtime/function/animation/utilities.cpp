#include "runtime/function/animation/utilities.h"

#include "runtime/function/animation/node.h"
#include "runtime/function/animation_ik/ss_node.h"
#include "runtime/function/animation_ik/ss_skeleton.h"

namespace Piccolo
{
    Bone* find_by_index(Bone* bones, int key, int size, bool is_flat)
    {
        if (key == std::numeric_limits<int>::max())
            return nullptr;
        if (is_flat)
        {
            if (key >= size)
                return nullptr;
            else
                return &bones[key];
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (bones[i].getID() == key)
                    return &bones[i];
            }
        }
        return nullptr;
    }

    ssBone* find_by_index(ssBone* bones, size_t key, size_t size, bool is_flat)
    {
        if (key == std::numeric_limits<int>::max())
            return nullptr;
        if (is_flat)
        {
            if (key >= size)
                return nullptr;
            else
                return &bones[key];
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (bones[i].getID() == key)
                    return &bones[i];
            }
        }
        return nullptr;
    }

    std::shared_ptr<RawBone> find_by_index(std::vector<std::shared_ptr<RawBone>>& bones, int key, bool is_flat)
    {
        if (key == std::numeric_limits<int>::max())
            return nullptr;
        if (is_flat)
        {
            return bones[key];
        }
        else
        {
            const auto it = std::find_if(bones.begin(), bones.end(), [&](const auto& i) { return i->index == key; });
            if (it != bones.end())
                return *it;
        }
        return nullptr;
    }

    int find_index_by_name(const SkeletonData& skeleton, const std::string& name)
    {
        const auto it = std::find_if(
            skeleton.bones_map.begin(), skeleton.bones_map.end(), [&](const auto& i) { return i.name == name; });
        if (it != skeleton.bones_map.end())
            return it->index;
        return std::numeric_limits<int>::max();
    }

    ss::math::Vector3    convertFrom(const Vector3& other) { return ss::math::Vector3(other.x, other.y, other.z); }

    Vector3              convertFrom(const ss::math::Vector3& other) { return Vector3(other.x, other.y, other.z); }

    ss::math::Quaternion convertFrom(const Quaternion& other)
    {
        return ss::math::Quaternion(other.w, other.x, other.y, other.z);
    }

    Quaternion convertFrom(const ss::math::Quaternion& other) 
    { 
        return Quaternion(other.w, other.x, other.y, other.z); 
    }
} // namespace Piccolo
