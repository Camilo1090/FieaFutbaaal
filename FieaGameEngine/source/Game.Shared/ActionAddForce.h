#pragma once

#include "Action.h"
#include "Factory.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	class ActionAddForce : public Action
	{
		RTTI_DECLARATIONS(ActionAddForce, Action)

	public:
		static const std::string TargetAccelerationKey;
		static const std::string ForceKey;
		static Vector<Signature> Signatures();

	public:
		explicit ActionAddForce(const std::string& name = std::string());
		explicit ActionAddForce(const glm::vec4& force, const std::string& name = std::string());
		ActionAddForce(const glm::vec4& direction, float magnitude, const std::string& name = std::string());
		virtual ~ActionAddForce() = default;

		virtual gsl::owner<ActionAddForce*> Clone() const override;
		virtual void Update(WorldState& worldState);

	private:
		glm::vec4 mForce;
		std::string mTargetAcceleration = GameObject::AccelerationKey;
	};

	CONCRETE_FACTORY(ActionAddForce, Scope)
}
