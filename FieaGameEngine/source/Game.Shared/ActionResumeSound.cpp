#include "pch.h"
#include "ActionResumeSound.h"
#include "AudioManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionResumeSound)

		const std::string ActionResumeSound::FilePath = "FilePath";
	const std::string ActionResumeSound::IsSoundEffect = "IsSoundEffect";

	Vector<Signature> ActionResumeSound::Signatures()
	{
		return
		{
			{FilePath, Datum::DatumType::STRING, 1, offsetof(ActionResumeSound, mFilePath) },
			{IsSoundEffect, Datum::DatumType::INTEGER, 1, offsetof(ActionResumeSound, mIsSoundEffect) }
		};
	}

	ActionResumeSound::ActionResumeSound(const std::string& name) :
		Action(TypeIdClass(), name)
	{

	}

	gsl::owner<ActionResumeSound*> ActionResumeSound::Clone() const
	{
		return new ActionResumeSound(*this);
	}

	void ActionResumeSound::Update(WorldState& /*worldState*/)
	{
		if (mSample == nullptr)
		{
			mSample = &AudioManager::GetSample(mFilePath);
		}

		AudioManager::UnPauseAudio(*mSample);
	}


}
