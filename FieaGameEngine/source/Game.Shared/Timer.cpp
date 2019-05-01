#include "pch.h"
#include "Timer.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Timer);

	const std::string Timer::GameLengthKey = "GameLength";
	const std::size_t Timer::GameLengthIndex = 8;

	Timer::Timer() : GameObject(TypeIdClass())
	{
	}


	Timer::~Timer()
	{
	}

	gsl::owner<Timer*> Timer::Clone() const
	{
		return new Timer(*this);
	}

	Vector<Signature> Timer::Signatures()
	{
		return {
			{GameLengthKey, Datum::DatumType::INTEGER, 1, offsetof(Timer, mLengthOfGame)}
		};
	}

}