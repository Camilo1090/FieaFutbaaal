#include "pch.h"
#include "ActionUpdateTargetRotation.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionUpdateTargetRotation);

	const std::string ActionUpdateTargetRotation::TargetKey = "Target";
	const size_t ActionUpdateTargetRotation::TargetIndex = 2;
	const std::string ActionUpdateTargetRotation::TargetRotationKey = "Rotation";
	const size_t ActionUpdateTargetRotation::TargetRotationIndex = 3;
	const std::string ActionUpdateTargetRotation::RotationRateKey = "Rate";
	const size_t ActionUpdateTargetRotation::RotationRateIndex = 4;

	Vector<Signature> ActionUpdateTargetRotation::Signatures()
	{
		return {
			{TargetKey, Datum::DatumType::STRING, 1, offsetof(ActionUpdateTargetRotation, mTarget)},
			{TargetRotationKey, Datum::DatumType::FLOAT, 1, offsetof(ActionUpdateTargetRotation, mTargetRotation)},
			{RotationRateKey, Datum::DatumType::FLOAT, 1, offsetof(ActionUpdateTargetRotation, mRotationRate)}
		};
	}

	ActionUpdateTargetRotation::ActionUpdateTargetRotation() : Action(TypeIdClass())
	{
	}


	ActionUpdateTargetRotation::~ActionUpdateTargetRotation()
	{
	}

	void ActionUpdateTargetRotation::Update(WorldState &)
	{
		//ask about scope name
		Scope* actionTurn = NameSearch(mTarget, "ActionTurn");
		if (actionTurn != nullptr)
		{
			//update rotate action that is in sheep that holds targetRot and rotationrate with theses new values
			actionTurn->Find("TargetRotation")->Set(mTargetRotation);
			actionTurn->Find("RotationRate")->Set(mRotationRate);
		}
	}
}