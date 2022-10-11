#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <core/math/types.hpp>

namespace Piccolo
{
    class Bone;
    class RawBone;
    class SkeletonData;
    class ssBone;
    class Vector3;
    class Quaternion;
    class Transform;

    template<typename T>
    size_t index(const std::vector<T>& vec, const T& value)
    {
        return std::distance(vec.begin(), std::find(vec.begin(), vec.end(), value));
    }

    template<typename T>
    void append_vector(std::vector<T>& base, const std::vector<T>& addition)
    {
        base.insert(base.end(), addition.begin(), addition.end());
    }

    Bone*                    find_by_index(Bone* bones, int key, int size, bool is_flat = false);
    ssBone*                  find_by_index(ssBone* bones, size_t key, size_t size, bool is_flat);
    std::shared_ptr<RawBone> find_by_index(std::vector<std::shared_ptr<RawBone>>& bones, int key, bool is_flat = false);
    int                      find_index_by_name(const SkeletonData& skeleton, const std::string& name);

    ss::math::Vector3    convertFrom(const Vector3& other);
    Vector3              convertFrom(const ss::math::Vector3& other);
    ss::math::Quaternion convertFrom(const Quaternion& other);
    Quaternion           convertFrom(const ss::math::Quaternion& other);
    
    Vector3 transformPositionToWorld(const Vector3& local_position, const Transform& global_transform);
    Vector3 transformPositionToLocal(const Vector3& world_position, const Transform& global_transform);
} // namespace Piccolo