#pragma once
#include "ReactionCollision.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ReactionCollisionScore : public ReactionCollision
	{
		RTTI_DECLARATIONS(ReactionCollisionScore, ReactionCollision)

	public:
		static Vector<Signature> Signatures();

	public:
		explicit ReactionCollisionScore(const std::string& name = std::string());
		ReactionCollisionScore(const ReactionCollisionScore& other);
		ReactionCollisionScore(ReactionCollisionScore&& other);
		virtual ~ReactionCollisionScore();

		virtual gsl::owner<ReactionCollisionScore*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;
	};

	CONCRETE_FACTORY(ReactionCollisionScore, Scope)
}