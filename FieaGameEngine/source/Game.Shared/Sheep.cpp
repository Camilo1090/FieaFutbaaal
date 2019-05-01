#include "pch.h"
#include "Sheep.h"
#include "WorldState.h"
#include "World.h"
#include "Event.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Sheep);

	const std::string Sheep::PointsKey = "Points";
	const std::size_t Sheep::PointsIndex = 8;
	const std::string Sheep::MaxSpeedKey = "MaxSpeed";
	const std::size_t Sheep::MaxSpeedIndex = 9;
	const std::string Sheep::MinPulseDelayKey = "MinPulseDelay";
	const std::size_t Sheep::MinPulseDelayIndex = 10;
	const std::string Sheep::MaxPulseDelayKey = "MaxPulseDelay";
	const std::size_t Sheep::MaxPulseDelayIndex = 11;

	Vector<Signature> Sheep::Signatures()
	{
		return {
			{PointsKey, Datum::DatumType::INTEGER, 1, offsetof(Sheep, mPoints)},
			{MaxSpeedKey, Datum::DatumType::FLOAT, 1, offsetof(Sheep, mMaxSpeed)},
			{MinPulseDelayKey, Datum::DatumType::INTEGER, 1, offsetof(Sheep, mMinPulseDelay)},
			{MaxPulseDelayKey, Datum::DatumType::INTEGER, 1, offsetof(Sheep, mMaxPulseDelay)}
		};
	}

	Sheep::Sheep() : GameObject(TypeIdClass())
	{
	}

	void Sheep::Start(WorldState& worldState)
	{
		auto event = std::make_shared<Event<Sheep*>>(this);
		worldState.World->GetEventQueue()->EnqueueEvent(event, *worldState.GameTime, GetRandomPulseDelay());
	}

	gsl::owner<Sheep*> Sheep::Clone() const
	{
		return new Sheep(*this);
	}

	int const & Sheep::GetPoints() const
	{
		return mPoints;
	}

	void Sheep::SetPoints(int const & points)
	{
		mPoints = points;
	}

	float const & Sheep::GetMaxSpeed() const
	{
		return mMaxSpeed;
	}

	void Sheep::SetMaxSpeed(float const & maxSpeed)
	{
		mMaxSpeed = maxSpeed;
	}
	
	std::chrono::milliseconds Sheep::GetMinPulseDelay() const
	{
		return std::chrono::milliseconds(mMinPulseDelay);
	}
	
	void Sheep::SetMinPulseDelay(int const & minPulseDelay)
	{
		mMinPulseDelay = minPulseDelay;
	}

	std::chrono::milliseconds Sheep::GetMaxPulseDelay() const
	{
		return std::chrono::milliseconds(mMaxPulseDelay);
	}

	void Sheep::SetMaxPulseDelay(int const & maxPulseDelay)
	{
		mMaxPulseDelay = maxPulseDelay;
	}

	std::chrono::milliseconds Sheep::GetRandomPulseDelay() const
	{
		return std::chrono::milliseconds(mMinPulseDelay + (rand() % (mMaxPulseDelay - mMinPulseDelay)));
	}
}