#include "pch.h"
#include "ActionSpawnSheep.h"
#include "Sector.h"
#include "GameObject.h"
#include "SheepSpawner.h"
#include "ReactionSpawn.h"
#include "World.h"
#include "BoxCollider.h"
#include "Sheep.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionSpawnSheep);

	Vector<Signature> ActionSpawnSheep::Signatures()
	{
		return Vector<Signature>();
	}

	ActionSpawnSheep::ActionSpawnSheep() : Action(TypeIdClass())
	{
	}

	gsl::owner<ActionSpawnSheep*> ActionSpawnSheep::Clone() const
	{
		return new ActionSpawnSheep(*this);
	}

	void ActionSpawnSheep::Update(WorldState& worldState)
	{
		if (mReactionParent == nullptr)
		{
			mReactionParent = GetParent<ReactionSpawn>();
		}

		SheepSpawner* spawner = mReactionParent->GetSheepSpawner();
		glm::vec2 position = spawner->Transform().GetPosition();

		const auto& collider = spawner->Collider(); 
		assert(collider.Is(BoxCollider::TypeIdClass()));
		const auto& boxCollider = static_cast<const BoxCollider&>(collider);

		//random coordinates
		glm::vec2 extents = boxCollider.GetExtents();
		float xPosition = (rand() % static_cast<int>(extents.x * 2)) + (position.x - extents.x);
		float yPosition = (rand() % static_cast<int>(extents.y * 2)) + (position.y - extents.y);

		//random weighted selection
		auto datum = spawner->TryGetWeights();
		assert(datum != nullptr);
		int32_t totalWeight = 0;
		for (size_t i = 0; i < datum->Size(); ++i) 
		{
			totalWeight += datum->Get<std::int32_t>(i);
		}

		std::int32_t randomWeight = rand() % totalWeight;
		size_t randIndex = 0;
		for (; randIndex < datum->Size(); ++randIndex)
		{
			randomWeight -= datum->Get<std::int32_t>(randIndex);
			if (randomWeight <= 0)
			{
				break;
			}
		}

		//clone
		assert(spawner->GetTypes()[randIndex].Is(Sheep::TypeIdClass()));
		auto clone = static_cast<Sheep&>(spawner->GetTypes()[randIndex]).Clone();
		clone->Start(worldState);

		//set position and adopt
		clone->Transform().SetPosition(glm::vec2(xPosition, yPosition));
		spawner->GetParent<Scope>()->Adopt(Sector::EntitiesKey, *clone);
	}
}