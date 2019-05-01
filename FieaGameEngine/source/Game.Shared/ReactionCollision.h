#pragma once
#include "Reaction.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class GameObject;

	class ReactionCollision : public Reaction
	{
		RTTI_DECLARATIONS(ReactionCollision, Reaction)

	public:
		static Vector<Signature> Signatures();

	public:
		explicit ReactionCollision(const std::string& name = std::string());
		ReactionCollision(const ReactionCollision& other);
		ReactionCollision(ReactionCollision&& other);
		virtual ~ReactionCollision();

		virtual gsl::owner<ReactionCollision*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;

	protected:
		ReactionCollision(const std::string& name, IdType id);
		std::pair<bool, const GameObject*> isAnyOfTheseObjectsInvolvedInCollision(const GameObject& objectOne, const GameObject& objectTwo);
	};

	CONCRETE_FACTORY(ReactionCollision, Scope)
}