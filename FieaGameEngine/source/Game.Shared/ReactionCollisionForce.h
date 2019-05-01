#pragma once
#include "ReactionCollision.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ReactionCollisionForce :
		public ReactionCollision
	{
		RTTI_DECLARATIONS(ReactionCollisionForce, ReactionCollision)

	public:
		static Vector<Signature> Signatures();

	public:
		explicit ReactionCollisionForce(const std::string& name = std::string());
		ReactionCollisionForce(const ReactionCollisionForce& other);
		ReactionCollisionForce(ReactionCollisionForce&& other);
		virtual ~ReactionCollisionForce();

		virtual gsl::owner<ReactionCollisionForce*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;
	};

	CONCRETE_FACTORY(ReactionCollisionForce, Scope)
}