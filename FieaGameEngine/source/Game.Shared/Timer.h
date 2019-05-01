#pragma once
#include "GameObject.h"

namespace FieaGameEngine
{
	class Timer : public GameObject
	{
		RTTI_DECLARATIONS(Timer, GameObject)

	public:
		static const std::string GameLengthKey;
		static const std::size_t GameLengthIndex;

	public:
		Timer();
		~Timer();
		Timer(const Timer&) = default;
		Timer(Timer&&) = default;
		Timer& operator=(const Timer&) = default;
		Timer& operator=(Timer&&) = default;

		virtual gsl::owner<Timer*> Clone() const override;
		static Vector<Signature> Signatures();

	private:
		std::int32_t mLengthOfGame;
	};

	CONCRETE_FACTORY(Timer, Scope)
}