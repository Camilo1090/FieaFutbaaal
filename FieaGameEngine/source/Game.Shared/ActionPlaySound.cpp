#include "pch.h"
#include "ActionPlaySound.h"
#include "AudioManager.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionPlaySound)

	const std::string ActionPlaySound::FilePath = "FilePath";
	const std::string ActionPlaySound::IsSoundEffect = "IsSoundEffect";

	Vector<Signature> ActionPlaySound::Signatures()
	{
		return
		{
			{FilePath, Datum::DatumType::STRING, 1, offsetof(ActionPlaySound, mFilePath) },
			{IsSoundEffect, Datum::DatumType::INTEGER, 1, offsetof(ActionPlaySound, mIsSoundEffect) }
		};
	}

	ActionPlaySound::ActionPlaySound(const std::string& name) :
		Action(TypeIdClass(), name)
	{
	}

	gsl::owner<ActionPlaySound*> ActionPlaySound::Clone() const
	{
		return new ActionPlaySound(*this);
	}

	void ActionPlaySound::Update(WorldState& /*worldState*/)
	{
		AudioManager::PlayAduio(AudioManager::GetSample(mFilePath), mIsSoundEffect);
	}
}