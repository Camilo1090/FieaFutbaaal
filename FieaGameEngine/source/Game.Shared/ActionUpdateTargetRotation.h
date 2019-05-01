#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionUpdateTargetRotation : public Action
	{
		RTTI_DECLARATIONS(ActionUpdateTargetRotation, Action)

	public:
		static const std::string TargetKey;
		static const std::size_t TargetIndex;
		static const std::string TargetRotationKey;
		static const std::size_t TargetRotationIndex;
		static const std::string RotationRateKey;
		static const std::size_t RotationRateIndex;
		static Vector<Signature> Signatures();
	public:
		ActionUpdateTargetRotation();
		virtual ~ActionUpdateTargetRotation();
		virtual void Update(WorldState& worldState) override;

	private:
		std::string mTarget;
		float mTargetRotation;
		float mRotationRate;
	};
}
