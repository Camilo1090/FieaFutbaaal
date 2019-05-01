#include "pch.h"
#include "ActionStopSound.h"
#include "AudioManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionStopSound)

		const std::string ActionStopSound::FilePath = "FilePath";
	const std::string ActionStopSound::IsSoundEffect = "IsSoundEffect";

	Vector<Signature> ActionStopSound::Signatures()
	{
		return
		{
			{FilePath, Datum::DatumType::STRING, 1, offsetof(ActionStopSound, mFilePath) },
			{IsSoundEffect, Datum::DatumType::INTEGER, 1, offsetof(ActionStopSound, mIsSoundEffect) }
		};
	}

	ActionStopSound::ActionStopSound(const std::string& name) :
		Action(TypeIdClass(), name)
	{
	}

	gsl::owner<ActionStopSound*> ActionStopSound::Clone() const
	{
		return new ActionStopSound(*this);
	}

	void ActionStopSound::Update(WorldState& /*worldState*/)
	{
		if (mSample == nullptr)
		{
			mSample = &AudioManager::GetSample(mFilePath);
		}

		AudioManager::PlayAduio(*mSample, mIsSoundEffect);
	}
}