#pragma once

#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine 
{
	class ReactionSpawn;

	class ActionSpawnSheep final : public Action
	{
		RTTI_DECLARATIONS(ActionSpawnSheep, Action)

	public:
		/// <summary>
		/// signatures
		/// </summary>
		static Vector<Signature> Signatures();


	public:
		ActionSpawnSheep();
		virtual ~ActionSpawnSheep() = default;

		virtual gsl::owner<ActionSpawnSheep*> Clone() const override;
		virtual void Update(WorldState& worldState) override;

	private:
		ReactionSpawn* mReactionParent; 

	};

	CONCRETE_FACTORY(ActionSpawnSheep, Scope)
}