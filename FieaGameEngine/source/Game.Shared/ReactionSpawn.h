#pragma once

#include "Reaction.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class SheepSpawner;
	class World;

	class ReactionSpawn : public Reaction
	{
		RTTI_DECLARATIONS(ReactionSpawn, Reaction)

	public:
		explicit ReactionSpawn(const std::string& name = std::string());
		ReactionSpawn(const ReactionSpawn& other);
		ReactionSpawn(ReactionSpawn&& other);
		ReactionSpawn& operator=(const ReactionSpawn&) = default;
		ReactionSpawn& operator=(ReactionSpawn&&) = default;
		virtual ~ReactionSpawn();

		virtual gsl::owner<ReactionSpawn*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;
		SheepSpawner* GetSheepSpawner();
		World* GetWorld();
		static Vector<Signature> Signatures();

	private:
		World* mWorld;
		SheepSpawner* mSheepSpawner;
	};

	CONCRETE_FACTORY(ReactionSpawn, Scope)
}
