#include "pch.h"
#include "Dog.h"
#include "CircleCollider.h"
#include "WorldState.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Dog);

	const std::string Dog::BarkColliderKey = "BarkCollider";
	const std::size_t Dog::BarkColliderIndex = 8;
	const std::string Dog::BarkScaleKey = "BarkScale";
	const std::string Dog::BarkScaleDecreaseRateKey = "BarkScaleDecreaseRate";

	Vector<Signature> Dog::Signatures()
	{
		return {
			{ BarkColliderKey, Datum::DatumType::TABLE, 0, 0 },
			{ BarkScaleKey, Datum::DatumType::FLOAT, 1, offsetof(Dog, mBarkScale) },
			{ BarkScaleDecreaseRateKey, Datum::DatumType::FLOAT, 1, offsetof(Dog, mBarkScaleDecreaseRate) }
		};
	}
	
	Dog::Dog() : GameObject(TypeIdClass())
	{
		assert(mList[BarkColliderIndex]->first == BarkColliderKey);
	}

	gsl::owner<Dog*> Dog::Clone() const
	{
		return new Dog(*this);
	}

	void Dog::Start(WorldState&)
	{
		mCanBark = true;
	}

	void Dog::Update(WorldState& worldState)
	{
		const auto& currentScale = GetBarkCollider().GetScale();
		if (currentScale > 1.0f)
		{
			float newScale = currentScale - (mBarkScaleDecreaseRate * worldState.GameTime->ElapsedGameTimeSeconds().count());

			if (newScale < 1.0f)
			{
				newScale = 1.0f;
			}

			GetBarkCollider().SetScale(newScale);
		}
	}

	bool Dog::Bark()
	{
		const auto& currentScale = GetBarkCollider().GetScale();
		if (currentScale <= 1.0f && mCanBark)
		{
			GetBarkCollider().SetScale(mBarkScale);
			auto& c = GetBarkCollider();
			c;
			return true;
		}

		return false;
	}

	CircleCollider& Dog::GetBarkCollider()
	{
		auto& datum = At(BarkColliderIndex);
		assert(datum.Size() > 0);
		auto& scope = datum[0];
		assert(scope.Is(CircleCollider::TypeIdClass()));
		return static_cast<CircleCollider&>(scope);
	}
}