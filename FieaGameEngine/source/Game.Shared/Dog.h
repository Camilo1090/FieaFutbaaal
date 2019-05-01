#pragma once

#include "GameObject.h"

namespace FieaGameEngine
{
	class CircleCollider;

	class Dog : public GameObject
	{
		RTTI_DECLARATIONS(Dog, GameObject)

	public:
		static const std::string BarkColliderKey;
		static const std::size_t BarkColliderIndex;
		static const std::string BarkScaleKey;
		static const std::string BarkScaleDecreaseRateKey;
		static Vector<Signature> Signatures();

	public:
		Dog();
		virtual ~Dog() = default;
		Dog(const Dog&) = default;
		Dog(Dog&&) = default;
		Dog& operator=(const Dog&) = default;
		Dog& operator=(Dog&&) = default;

		virtual gsl::owner<Dog*> Clone() const override;
		virtual void Start(WorldState& worldState);
		virtual void Update(WorldState& worldState);

		bool Bark();

		CircleCollider& GetBarkCollider();

	private:
		float mBarkScale;
		float mBarkScaleDecreaseRate;

		bool mCanBark = false;
	};

	CONCRETE_FACTORY(Dog, Scope)
}