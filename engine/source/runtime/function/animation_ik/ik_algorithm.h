#pragma once
#include "runtime/resource/res_type/data/ik_config.h"
#include "runtime/function/animation_ik/ss_skeleton.h"

namespace Piccolo
{
    class XPBDIKSolver;

	class IKAlgorithmBase
	{
    protected:
    public:
        virtual void calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement) = 0;
	};

	class TwoBoneIKSolver : public IKAlgorithmBase
	{
    public:
        void calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement);
	};

    class LengthConstraint
    {
    public:
        float             m_k {0.f};              // 刚性系数
        float             m_lambda {0.f};         // 拉格朗日算子
        float             m_default_length {0.f};    //默认长度
        int               i {0};
        int               j {0}; // 相关的骨骼

        ss::math::Vector3 m_dx {0,0,0};             // Position(i)-Position(j)
        float             m_constraint_result {0.f}; // Cj(x)的值, 等于|dx|-m_default_length

        LengthConstraint(float k, float default_length, int i, int j);
        void resetLambda();
        void updateData(XPBDIKSolver& solver);
    };

    
    class DirectionForce
    {
    public:
        int   i {0};

        ss::math::Vector3 m_force {0, 0, 0};            // virtual force

        DirectionForce(ss::math::Vector3 force, int i);
    };

    // 控制节点距离的方案
	class XPBDIKSolver : public IKAlgorithmBase
    {
    public:
        int                            m_moment_step = 5;
        int                            m_iter_times  = 10;
        int                            m_bone_count;
        ssSkeleton*                    m_skeleton;
        float                          m_persudo_time     = 0.1f;
        float                          m_persudo_time_sqr = 0.01f;
        std::vector<LengthConstraint>  m_length_constraints;
        std::vector<float>             m_invmass;
        std::vector<ss::math::Vector3> m_position;
        std::vector<ss::math::Vector3> m_last_position;
        std::vector<ss::math::Vector3> m_velocity;
        std::vector<DirectionForce>    m_force;

        void calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement);
        void processMoment();
        void processIter();
        void reachByRotation();
	};
}