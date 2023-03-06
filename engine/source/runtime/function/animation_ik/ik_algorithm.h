#pragma once
#include "runtime/resource/res_type/data/ik_config.h"
#include "runtime/function/animation_ik/ss_skeleton.h"

namespace Piccolo
{
    class PBDIKSolver;

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

    class Constraint
    {
    public:
        float             m_k {0.f};              // ����ϵ��
        float             m_lambda {0.f};         // ������������
        float             m_default_length {0.f};    //Ĭ�ϳ���
        int               i {0};
        int               j {0}; // ��صĹ���

        ss::math::Vector3 m_dx {0,0,0};             // Position(i)-Position(j)
        float             m_constraint_result {0.f}; // Cj(x)��ֵ, ����|dx|-m_default_length

        Constraint(float k, float default_length, int i, int j);
        void resetLambda();
        void updateData(PBDIKSolver& solver);
    };

    // ���ƽڵ����ķ���
	class PBDIKSolver : public IKAlgorithmBase
    {
    public:
        int                            m_moment_step = 10;
        int                            m_iter_times  = 10;
        int                            m_bone_count;
        ssSkeleton*                    m_skeleton;
        float                          m_persudo_time_sqr = 1.0f;
        std::vector<Constraint>        m_constraints;
        std::vector<float>             m_invmass;
        std::vector<ss::math::Vector3> m_position;
        std::vector<ss::math::Vector3> m_last_position;
        std::vector<ss::math::Vector3> m_velocity;

        void calculateIKResult(const IKConfig& ik_config, ssSkeleton& skeleton, float root_displacement);
        void processMoment();
        void processIter();
        void reachByRotation();
	};
}