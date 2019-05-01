#include "pch.h"
#include "ActionMovementDrag.h"
#include "Entity.h"
#include "GameObject.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionMovementDrag)

	const std::string ActionMovementDrag::DragKey = "Drag";

	Vector<Signature> ActionMovementDrag::Signatures()
	{
		return {
			{ DragKey, Datum::DatumType::FLOAT, 1, offsetof(ActionMovementDrag, mDrag) }
		};
	}

	ActionMovementDrag::ActionMovementDrag(float drag, const std::string& name) : Action(TypeIdClass(), name), mDrag(drag)
	{
	}

	gsl::owner<ActionMovementDrag*> ActionMovementDrag::Clone() const
	{
		return new ActionMovementDrag(*this);
	}

	void ActionMovementDrag::Update(WorldState& worldState)
	{
		assert(worldState.Entity != nullptr);
		auto entity = worldState.Entity;
		assert(entity->Is(GameObject::TypeIdClass()));
		auto gameObject = static_cast<GameObject*>(entity);

		//float deltaTime = worldState.GameTime->ElapsedGameTimeSeconds().count();

		glm::vec2 newVelocity = gameObject->GetVelocity() * mDrag;

		gameObject->SetVelocity(newVelocity);
	}

	float& ActionMovementDrag::Drag()
	{
		return mDrag;
	}

	const float& ActionMovementDrag::Drag() const
	{
		return mDrag;
	}
}
