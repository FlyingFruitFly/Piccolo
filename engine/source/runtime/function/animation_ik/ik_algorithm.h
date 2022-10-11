#pragma once
#include "runtime/resource/res_type/data/ik_config.h"
#include "runtime/function/animation_ik/ss_skeleton.h"

namespace Piccolo
{
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
}