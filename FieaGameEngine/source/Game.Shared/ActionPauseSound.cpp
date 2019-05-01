#include "pch.h"
#include "ActionPauseSound.h"
#include "AudioManager.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionPauseSound)

	const std::string ActionPauseSound::FilePath = "FilePath";
	const std::string ActionPauseSound::IsSoundEffect = "IsSoundEffect";

	Vector<Signature> ActionPauseSound::Signatures()
	{
		return
		{
			{FilePath, Datum::DatumType::STRING, 1, offsetof(ActionPauseSound, mFilePath) },
			{IsSoundEffect, Datum::DatumType::INTEGER, 1, offsetof(ActionPauseSound, mIsSoundEffect) }
		};
	}

	ActionPauseSound::ActionPauseSound(const std::string& name) :
		Action(TypeIdClass(), name)
	{
	}

	gsl::owner<ActionPauseSound*> ActionPauseSound::Clone() const
	{
		return new ActionPauseSound(*this);
	}

	void ActionPauseSound::Update(WorldState& /*worldState*/)
	{
		if (mSample == nullptr)
		{
			mSample = &AudioManager::GetSample(mFilePath);
		}

		AudioManager::PlayAduio(*mSample, mIsSoundEffect);
	}
}