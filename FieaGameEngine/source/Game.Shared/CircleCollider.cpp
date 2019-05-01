#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include <cmath>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(CircleCollider)

	const std::string CircleCollider::RadiusKey = "Radius";
	const std::size_t CircleCollider::RadiusIndex = 4;
	const std::string CircleCollider::ScaleKey = "Scale";
	const std::size_t CircleCollider::ScaleIndex = 5;

	Vector<Signature> CircleCollider::Signatures()
	{
		return {
			{ RadiusKey, Datum::DatumType::FLOAT, 1, offsetof(CircleCollider, mRadius)},
			{ ScaleKey, Datum::DatumType::FLOAT, 1, offsetof(CircleCollider, mScale)}
		};
	}
	CircleCollider::CircleCollider() : Collider(CircleCollider::TypeIdClass())
	{
		assert(mList[RadiusIndex]->first == RadiusKey);
		assert(mList[ScaleIndex]->first == ScaleKey);
	}


	CircleCollider::~CircleCollider()
	{
	}

	float CircleCollider::GetRadius() const
	{
		return mRadius;
	}

	void CircleCollider::SetRadius(float const & radius)
	{
		mRadius = radius;
	}

	float CircleCollider::GetScale() const
	{
		return mScale;
	}

	void CircleCollider::SetScale(float const & radiusScale)
	{
		mScale = radiusScale;
	}

	float CircleCollider::GetScaledRadius() const
	{
		return mRadius * mScale;
	}

	bool CircleCollider::IsCollidingWith(const Collider & otherCollider) const
	{
		bool result = false;
		glm::vec2 myPosition = GetGameObject().Transform().GetPosition();
		glm::vec2 otherPosition = otherCollider.GetGameObject().Transform().GetPosition();
		float distanceBetweenPositions = glm::length(otherPosition - myPosition);

		if (otherCollider.Is(CircleCollider::TypeIdClass()))
		{
			CircleCollider const * otherCircleCollider = static_cast<CircleCollider const *>(&otherCollider);
			result = distanceBetweenPositions <= GetScaledRadius() + otherCircleCollider->GetScaledRadius();
		}
		else if (otherCollider.Is(BoxCollider::TypeIdClass()))
		{
			BoxCollider const * otherBoxCollider = static_cast<BoxCollider const *>(&otherCollider);
			result = distanceBetweenPositions <= GetScaledRadius() + otherBoxCollider->DistanceToEdgeOfBox((myPosition - otherPosition)) ;
		}
		return result;
	}

	void CircleCollider::MoveOutOfCollider(Collider const & otherCollider)
	{
		glm::vec2 position = GetGameObject().Transform().GetPosition();
		glm::vec2 otherPosition = otherCollider.GetGameObject().Transform().GetPosition();
		glm::vec2 normalizedDifferenceVector = glm::normalize((otherPosition - position));

		if (otherCollider.Is(CircleCollider::TypeIdClass()))
		{
			CircleCollider const & otherCircleCollider = static_cast<CircleCollider const &>(otherCollider);
			GetGameObject().Transform().SetPosition(otherPosition - normalizedDifferenceVector * (mRadius + otherCircleCollider.mRadius));
		}
		else if (otherCollider.Is(BoxCollider::TypeIdClass()))
		{
			BoxCollider const & otherBoxCollider = static_cast<BoxCollider const &>(otherCollider);
			GetGameObject().Transform().SetPosition(otherPosition - normalizedDifferenceVector * (mRadius + otherBoxCollider.DistanceToEdgeOfBox(normalizedDifferenceVector)));
		}
	}

	gsl::owner<CircleCollider*> CircleCollider::Clone() const
	{
		return new CircleCollider(*this);
	}

	

}