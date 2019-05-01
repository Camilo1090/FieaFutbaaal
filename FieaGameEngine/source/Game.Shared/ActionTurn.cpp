#include "pch.h"
#include "ActionTurn.h"
#include "World.h"
#include "GameObject.h"
#include <cmath>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionTurn)

	const std::string ActionTurn::TargetKey = "Target";
	const std::size_t ActionTurn::TargetIndex = 2;
	const std::string ActionTurn::TargetRotationKey = "TargetRotation";
	const std::size_t ActionTurn::TargetRotationIndex = 3;
	const std::string ActionTurn::RotationRateKey = "RotationRate";
	const std::size_t ActionTurn::RotationRateIndex = 4;

	Vector<Signature> ActionTurn::Signatures()
	{
		return {
			{ TargetKey, Datum::DatumType::STRING, 1, offsetof(ActionTurn, mTarget) },
			{ TargetRotationKey, Datum::DatumType::FLOAT, 1, offsetof(ActionTurn, mTargetRotation) },
			{ RotationRateKey, Datum::DatumType::FLOAT, 1, offsetof(ActionTurn, mRotationRate) },
		};
	}

	ActionTurn::ActionTurn() : Action(TypeIdClass())
	{
	}

	gsl::owner<ActionTurn*> ActionTurn::Clone() const
	{
		return new ActionTurn(*this);
	}

	void ActionTurn::Update(WorldState & worldState)
	{
		Scope * targetScope = nullptr;
		GameObject * gameObject = nullptr;

		Search(mTarget, &targetScope);

		assert((targetScope)->Is(GameObject::TypeIdClass()));
		gameObject= static_cast<GameObject*>(targetScope);
		
		float currentRotation = gameObject->Transform().GetRotation();

		if (currentRotation != mTargetRotation)
		{
			mRotationThisTick = mRotationRate * worldState.GameTime->ElapsedGameTimeSeconds().count();

			if (TargetRotationWithinRotationAmount(currentRotation))
			{
				currentRotation = mTargetRotation;
			}
			else if (ClockwiseRotationIsShortest(currentRotation))
			{
				currentRotation += mRotationThisTick;
			}
			else
			{
				currentRotation -= mRotationThisTick;
			}

			gameObject->Transform().SetRotation(static_cast<float>(fmod(currentRotation, 360)));
		}
	}

	bool ActionTurn::ClockwiseRotationIsShortest(float currentRotation) const
	{
		bool result = false;
		float angleDiff = mTargetRotation - currentRotation;
		if (angleDiff < 0)
		{
			angleDiff += 360;
		}
		if (angleDiff > 180)
		{
			result = true;
		}
		return result;
	}

	bool ActionTurn::TargetRotationWithinRotationAmount(float currentRotation) const
	{
		bool result = false;
		if (ClockwiseRotationIsShortest(currentRotation))
		{
			if (fmod(currentRotation + mRotationThisTick, 360) > mTargetRotation)
			{
				result = true;
			}
		}
		else
		{
			if (fmod(currentRotation - mRotationThisTick, 360) < mTargetRotation)
			{
				result = true;
			}
		}
		return result;
	}
}