#include "pch.h"
#include "ScoreVolume.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ScoreVolume);
	const std::string ScoreVolume::IsPlayerOneScoreKey = "IsPlayerOneScore";
	const int ScoreVolume::IsPlayerOneScoreIndex = 8;

	ScoreVolume::ScoreVolume() : GameObject(TypeIdClass())
	{
		assert(mList[IsPlayerOneScoreIndex]->first == IsPlayerOneScoreKey);
	}

	gsl::owner<ScoreVolume*> ScoreVolume::Clone() const
	{
		return new ScoreVolume(*this);
	}

	Vector<Signature> ScoreVolume::Signatures()
	{
		return {
			{ IsPlayerOneScoreKey, Datum::DatumType::INTEGER, 1, offsetof(ScoreVolume, mIsPlayerOneScore) }
		};
	}
	bool ScoreVolume::GetIsPlayerOneScore() const
	{
		return mIsPlayerOneScore;
	}
}