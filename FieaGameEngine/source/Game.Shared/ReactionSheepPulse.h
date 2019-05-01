#pragma once
#include "Reaction.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ReactionSheepPulse :	public Reaction
	{
		RTTI_DECLARATIONS(ReactionSheepPulse, Reaction)

	public:
		static const std::string RotationRange;
		static const std::string MinForceX;
		static const std::string MaxForceX;
		static const std::string MinForceY;
		static const std::string MaxForceY;
		static Vector<Signature> Signatures();

	public:
		explicit ReactionSheepPulse(const std::string& name = std::string());
		virtual ~ReactionSheepPulse();
		ReactionSheepPulse(const ReactionSheepPulse& other);
		ReactionSheepPulse(ReactionSheepPulse&& other);

		virtual gsl::owner<ReactionSheepPulse*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;

	private:
		std::int32_t mRotationRange = 1;
		std::int32_t mMinForceX = 0;
		std::int32_t mMaxForceX = 1;
		std::int32_t mMinForceY = 0;
		std::int32_t mMaxForceY = 1;
	};

	CONCRETE_FACTORY(ReactionSheepPulse, Scope)
}