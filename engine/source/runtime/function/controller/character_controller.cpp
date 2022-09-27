#include "runtime/function/controller/character_controller.h"

#include "runtime/core/base/macro.h"

#include "runtime/function/framework/component/motor/motor_component.h"
#include "runtime/function/framework/world/world_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/physics/physics_scene.h"

namespace Piccolo
{
    CharacterController::CharacterController(const Capsule& capsule) : m_capsule(capsule)
    {
        m_rigidbody_shape                                    = RigidBodyShape();
        m_rigidbody_shape.m_geometry                         = PICCOLO_REFLECTION_NEW(Capsule);
        *static_cast<Capsule*>(m_rigidbody_shape.m_geometry) = m_capsule;

        m_rigidbody_shape.m_type = RigidBodyShapeType::capsule;

        Quaternion orientation;
        orientation.fromAngleAxis(Radian(Degree(90.f)), Vector3::UNIT_X);

        m_rigidbody_shape.m_local_transform =
            Transform(Vector3(0, 0, capsule.m_half_height + capsule.m_radius), orientation, Vector3::UNIT_SCALE);
    }

    Vector3 CharacterController::move(const Vector3& current_position, const Vector3& displacement)
    {
        std::shared_ptr<PhysicsScene> physics_scene =
            g_runtime_global_context.m_world_manager->getCurrentActivePhysicsScene().lock();
        ASSERT(physics_scene);

        Vector3 final_position = current_position + displacement;

        Transform final_transform = Transform(final_position, Quaternion::IDENTITY, Vector3::UNIT_SCALE);

        if (physics_scene->isOverlap(m_rigidbody_shape, final_transform.getMatrix()))
        {
            // try step up
            std::vector<PhysicsHitInfo> hits;
            bool                        first = true;
            float                       max_z = 0;
            float                       max_step_up = 0.5;
            final_transform.m_position.z += max_step_up;
            if (physics_scene->sweep(
                    m_rigidbody_shape, final_transform.getMatrix(), Vector3::NEGATIVE_UNIT_Z, max_step_up, hits))
            {
                for (auto& hit : hits)
                {
                    if (first || hit.hit_position.z > max_z)
                    {
                        max_z = hit.hit_position.z;
                        first = false;
                    }
                }
            }

            // can step up
            if (!first && max_z < max_step_up + final_position.z)
            {
                final_position.z = max_z;
            }
            // cannot
            else
            {
                final_position = current_position;
            }
        }
        return final_position;
    }

    bool CharacterController::onGround(const Matrix4x4& transform)
{
        std::shared_ptr<PhysicsScene> physics_scene =
            g_runtime_global_context.m_world_manager->getCurrentActivePhysicsScene().lock();
        ASSERT(physics_scene);
        std::vector<PhysicsHitInfo> hits;
        physics_scene->sweep(m_rigidbody_shape, transform, Vector3::NEGATIVE_UNIT_Z, 0.01, hits);
        for (auto& hit : hits)
        {
            if (abs(hit.hit_normal.dotProduct(Vector3::UNIT_Z)) > 0.3)
                return true;
        }
        return false;
    }
} // namespace Piccolo
