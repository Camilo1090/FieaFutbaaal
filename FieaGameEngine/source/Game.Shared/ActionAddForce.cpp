#include "pch.h"
#include "ActionAddForce.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionAddForce)

	const std::string ActionAddForce::TargetAccelerationKey = "TargetAcceleration";
	const std::string ActionAddForce::ForceKey = "Force";

	Vector<Signature> ActionAddForce::Signatures()
	{
		return {
			{ TargetAccelerationKey, Datum::DatumType::STRING, 1, offsetof(ActionAddForce, mTargetAcceleration) },
			{ ForceKey, Datum::DatumType::VECTOR, 1, offsetof(ActionAddForce, mForce) }
		};
	}

	ActionAddForce::ActionAddForce(const std::string& name) : Action(TypeIdClass(), name)
	{
	}

	ActionAddForce::ActionAddForce(const glm::vec4& force, const std::string& name) : Action(TypeIdClass(), name), mForce(force)
	{
	}

	ActionAddForce::ActionAddForce(const glm::vec4& direction, float magnitude, const std::string& name) : 
		Action(TypeIdClass(), name), mForce(direction * magnitude)
	{
	}

	gsl::owner<ActionAddForce*> ActionAddForce::Clone() const
	{
		return new ActionAddForce(*this);
	}

	void ActionAddForce::Update(WorldState& /*worldState*/)
	{
		auto datum = Search(mTargetAcceleration);

		if (datum != nullptr)
		{
			assert(datum->Size() > 0);
			auto& acceleration = datum->Get<glm::vec4>();
			acceleration = mForce;
		}
	}
}
