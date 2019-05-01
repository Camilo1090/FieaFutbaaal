#pragma once

#include "ReactionInput.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Dog;

	class ReactionInputPlayer : public ReactionInput
	{
		RTTI_DECLARATIONS(ReactionInputPlayer, ReactionInput)

	public:
		static const std::string PlayerIndexKey;
		static const std::string SpeedKey;
		static Vector<Signature> Signatures();

	public:
		ReactionInputPlayer();
		virtual ~ReactionInputPlayer() = default;

		virtual void Notify(const EventPublisher& event) override;

	private:
		std::int32_t mPlayerIndex = 0;
		float mSpeed = 0.0f;

		Dog* mDog = nullptr;

		void MovePlayer(const glm::vec2& displacement);
		void TurnPlayer(float angle);
	};

	CONCRETE_FACTORY(ReactionInputPlayer, Scope)
}
