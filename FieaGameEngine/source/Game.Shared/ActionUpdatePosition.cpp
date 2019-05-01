#include "pch.h"
#include "ActionUpdatePosition.h"
#include "Entity.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Transform.h"
#include "Sheep.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionUpdatePosition)

	Vector<Signature> ActionUpdatePosition::Signatures()
	{
		return Vector<Signature>();
	}

	ActionUpdatePosition::ActionUpdatePosition(const std::string& name) : Action(TypeIdClass(), name)
	{
	}

	gsl::owner<ActionUpdatePosition*> ActionUpdatePosition::Clone() const
	{
		return new ActionUpdatePosition(*this);
	}

	void ActionUpdatePosition::Update(WorldState& worldState)
	{
		assert(worldState.Entity != nullptr);
		auto entity = worldState.Entity;
		assert(entity->Is(GameObject::TypeIdClass()));
		auto gameObject = static_cast<GameObject*>(entity);

		float deltaTime = worldState.GameTime->ElapsedGameTimeSeconds().count();

		glm::vec2 newVelocity = gameObject->GetVelocity() + gameObject->GetAcceleration() * deltaTime;
		if (entity->Is(Sheep::TypeIdClass()))
		{
			auto sheep = static_cast<Sheep*>(entity);
			float maxSpeed = sheep->GetMaxSpeed();
			if (glm::length(newVelocity) > maxSpeed)
			{
				newVelocity = glm::normalize(newVelocity) * maxSpeed;
			}
		}
		gameObject->SetVelocity(newVelocity);

		glm::vec2 newPosition = gameObject->Transform().GetPosition() + gameObject->GetVelocity() * deltaTime;
		gameObject->Transform().SetPosition(newPosition);

		gameObject->SetAcceleration(glm::vec2(0,0));
	}
}
