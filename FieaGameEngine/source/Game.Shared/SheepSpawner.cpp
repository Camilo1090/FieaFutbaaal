#include "pch.h"
#include "SheepSpawner.h"
#include "WorldState.h"
#include "World.h"
#include "Event.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(SheepSpawner);

	const std::string SheepSpawner::TypesKey = "Types";
	const std::size_t SheepSpawner::TypesIndex = 8;
	const std::string SheepSpawner::WeightsKey = "Weights";
	const std::string SheepSpawner::MinDelayKey = "MinDelay";
	const std::string SheepSpawner::MaxDelayKey = "MaxDelay";

	Vector<Signature> SheepSpawner::Signatures()
	{
		return	{
			{ TypesKey, Datum::DatumType::TABLE, 0, 0 },
			{ MinDelayKey, Datum::DatumType::INTEGER, 1, offsetof(SheepSpawner, mMinSpawnDelay) },
			{ MaxDelayKey, Datum::DatumType::INTEGER, 1, offsetof(SheepSpawner, mMaxSpawnDelay) }
		};
	}

	SheepSpawner::SheepSpawner() : GameObject(TypeIdClass())
	{
	}

	void SheepSpawner::Start(WorldState& worldState)
	{
		auto event = std::make_shared<Event<SheepSpawner*>>(this);
		worldState.World->GetEventQueue()->EnqueueEvent(event, *worldState.GameTime);
	}

	gsl::owner<SheepSpawner*> SheepSpawner::Clone() const
	{
		return new SheepSpawner(*this);
	}

	Datum& SheepSpawner::GetTypes()
	{
		return operator[](TypesIndex);
	}

	Datum* SheepSpawner::TryGetWeights()
	{
		return Find(WeightsKey);
	}

	std::int32_t SheepSpawner::GetMinSpawnDelay()
	{
		return mMinSpawnDelay;
	}

	std::int32_t SheepSpawner::GetMaxSpawnDelay()
	{
		return mMaxSpawnDelay;
	}
}
