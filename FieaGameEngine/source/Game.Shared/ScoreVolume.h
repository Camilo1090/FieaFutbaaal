#pragma once
#include "GameObject.h"

namespace FieaGameEngine
{
	class ScoreVolume :
		public GameObject
	{
		RTTI_DECLARATIONS(ScoreVolume, GameObject)
	public:

		static const std::string IsPlayerOneScoreKey;
		static const int IsPlayerOneScoreIndex;

	public:
		ScoreVolume();
		virtual ~ScoreVolume() = default;

		ScoreVolume(const ScoreVolume&) = default;
		ScoreVolume(ScoreVolume&&) = default;
		ScoreVolume& operator=(const ScoreVolume&) = default;
		ScoreVolume& operator=(ScoreVolume&&) = default;

		virtual gsl::owner<ScoreVolume*> Clone() const override;
		static Vector<Signature> Signatures();

		bool GetIsPlayerOneScore() const;

	private:
		int mIsPlayerOneScore = 0;
	};
	CONCRETE_FACTORY(ScoreVolume, FieaGameEngine::Scope)
}