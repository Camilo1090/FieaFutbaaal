#pragma once
#include "GameObject.h"
#include <chrono>

namespace FieaGameEngine
{
	class Sheep : public GameObject
	{
		RTTI_DECLARATIONS(Sheep, GameObject)

	public:
		static const std::string PointsKey;
		static const std::size_t PointsIndex;
		static const std::string MaxSpeedKey;
		static const std::size_t MaxSpeedIndex;
		static const std::string MinPulseDelayKey;
		static const std::size_t MinPulseDelayIndex;
		static const std::string MaxPulseDelayKey;
		static const std::size_t MaxPulseDelayIndex;
		static Vector<Signature> Signatures();

	public:
		Sheep();
		virtual ~Sheep() = default;
		Sheep(const Sheep&) = default;
		Sheep(Sheep&&) = default;
		Sheep& operator=(const Sheep&) = default;
		Sheep& operator=(Sheep&&) = default;

		virtual gsl::owner<Sheep*> Clone() const override;
		virtual void Start(WorldState& worldState) override;

		int const & GetPoints() const;
		void SetPoints(int const & points);

		float const & GetMaxSpeed() const;
		void SetMaxSpeed(float const & maxSpeed);

		std::chrono::milliseconds GetMinPulseDelay() const;
		void SetMinPulseDelay(int const & minPulseDelay);

		std::chrono::milliseconds GetMaxPulseDelay() const;
		void SetMaxPulseDelay(int const & minPulseDelay);

		std::chrono::milliseconds GetRandomPulseDelay() const;

	private:
		std::int32_t mPoints;
		float mMaxSpeed;
		std::int32_t mMinPulseDelay = 1000;
		std::int32_t mMaxPulseDelay = 2000;

	};

	CONCRETE_FACTORY(Sheep, Scope)
}