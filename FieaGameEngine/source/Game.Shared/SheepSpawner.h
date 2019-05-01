#pragma once

#include "GameObject.h"
#include "Factory.h"

namespace FieaGameEngine 
{

	class SheepSpawner : public GameObject
	{
		RTTI_DECLARATIONS(SheepSpawner, GameObject)

	public:
		static const std::string TypesKey;
		static const std::size_t TypesIndex;
		static const std::string WeightsKey;
		static const std::string MinDelayKey;
		static const std::string MaxDelayKey;
		static Vector<Signature> Signatures();

	public:
		SheepSpawner();
		virtual ~SheepSpawner() = default;
		SheepSpawner(const SheepSpawner&) = default;
		SheepSpawner(SheepSpawner&&) = default;
		SheepSpawner& operator=(const SheepSpawner&) = default;
		SheepSpawner& operator=(SheepSpawner&&) = default;

		virtual gsl::owner<SheepSpawner*> Clone() const override;
		virtual void Start(WorldState& worldState) override;

		Datum& GetTypes();
		Datum* TryGetWeights();
		std::int32_t GetMinSpawnDelay();
		std::int32_t GetMaxSpawnDelay();

	private:
		std::int32_t mMinSpawnDelay;
		std::int32_t mMaxSpawnDelay;
	};

	CONCRETE_FACTORY(SheepSpawner, Scope)

}

