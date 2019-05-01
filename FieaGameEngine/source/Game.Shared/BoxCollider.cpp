#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include <cmath>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(BoxCollider)

	const std::string BoxCollider::ExtentsKey = "Extents";
	const std::size_t BoxCollider::ExtentsIndex = 4;
	const std::string BoxCollider::ScaleKey = "Scale";
	const std::size_t BoxCollider::ScaleIndex = 5;

	Vector<Signature> BoxCollider::Signatures()
	{
		return {
			{ ExtentsKey, Datum::DatumType::VECTOR, 1, offsetof(BoxCollider, mExtents)},
			{ ScaleKey, Datum::DatumType::VECTOR, 1, offsetof(BoxCollider, mScale)}
		};
	}

	BoxCollider::BoxCollider() : Collider(BoxCollider::TypeIdClass())
	{
	}

	BoxCollider::BoxCollider(RTTI::IdType type) : Collider(type)
	{
	}


	BoxCollider::~BoxCollider()
	{
	}

	glm::vec2 BoxCollider::GetExtents() const
	{
		return glm::vec2(mExtents.x, mExtents.y);
	}

	void BoxCollider::SetExtents(glm::vec2 const & extents)
	{
		mExtents = glm::vec4(extents.x, extents.y, 0, 0);
	}

	void BoxCollider::SetExtents(glm::vec4 const & extents)
	{
		mExtents = extents;
	}

	glm::vec2 BoxCollider::GetScale() const
	{
		return glm::vec2(mScale.x, mScale.y);
	}

	void BoxCollider::SetScale(glm::vec2 const & colliderScale)
	{
		mScale = glm::vec4(colliderScale.x, colliderScale.y, 0, 0);
	}

	void BoxCollider::SetScale(glm::vec4 const & colliderScale)
	{
		mScale = colliderScale;
	}

	glm::vec2 BoxCollider::GetScaledExtents() const
	{
		return glm::vec2(GetExtents().x * GetScale().x, GetExtents().y * GetScale().y);
	}

	float BoxCollider::DistanceToEdgeOfBox(glm::vec2 directionVector) const
	{
		float result = 0;

		glm::vec2 normalizedDirectionVector = glm::normalize(directionVector);

		glm::vec2 scaledExtents = GetScaledExtents();

		float distanceIfXIsShorter = static_cast<float>(glm::length(normalizedDirectionVector * GetScaledExtents().x / normalizedDirectionVector.x));
		float distanceIfYIsShorter = static_cast<float>(glm::length(normalizedDirectionVector * GetScaledExtents().y / normalizedDirectionVector.y));

		if (distanceIfXIsShorter < distanceIfYIsShorter)
		{
			result = distanceIfXIsShorter;
		}
		else
		{
			result = distanceIfYIsShorter;
		}

		return result;
	}

	float BoxCollider::DistanceToEdgeOfBox(float angle) const
	{
		float result = 0;

		glm::vec2 normalizedDirectionVector = glm::vec2(cos(angle), sin(angle));

		float distanceIfXIsShorter = glm::length(normalizedDirectionVector * GetScaledExtents().x / normalizedDirectionVector.x);
		float distanceIfYIsShorter = glm::length(normalizedDirectionVector * GetScaledExtents().y / normalizedDirectionVector.y);

		if (distanceIfXIsShorter < distanceIfYIsShorter)
		{
			result = distanceIfXIsShorter;
		}
		else
		{
			result = distanceIfYIsShorter;
		}

		return result;
	}

	bool BoxCollider::IsCollidingWith(const Collider & otherCollider) const
	{
		bool result = false;
		glm::vec2 position = GetGameObject().Transform().GetPosition();
		glm::vec2 otherPosition = otherCollider.GetGameObject().Transform().GetPosition();
		float distanceBetweenPositions = glm::length(otherPosition - position);

		if (otherCollider.Is(CircleCollider::TypeIdClass()))
		{
			result = distanceBetweenPositions <= DistanceToEdgeOfBox(otherPosition - position) + static_cast<CircleCollider const *>(&otherCollider)->GetScaledRadius();
		}
		else if (otherCollider.Is(BoxCollider::TypeIdClass()))
		{
			result = distanceBetweenPositions <= DistanceToEdgeOfBox(otherPosition - position) + static_cast<BoxCollider const *>(&otherCollider)->DistanceToEdgeOfBox(position - otherPosition);
		}
		return result;
	}

	void BoxCollider::MoveOutOfCollider(Collider const & otherCollider)
	{
		glm::vec2 position = GetGameObject().Transform().GetPosition();
		glm::vec2 otherPosition = otherCollider.GetGameObject().Transform().GetPosition();
		glm::vec2 normalizedDifferenceVector = glm::normalize((otherPosition - position));

		if (otherCollider.Is(CircleCollider::TypeIdClass()))
		{
			CircleCollider const & otherCircleCollider = static_cast<CircleCollider const &>(otherCollider);
			GetGameObject().Transform().SetPosition(otherPosition - normalizedDifferenceVector * (DistanceToEdgeOfBox(otherPosition - position) + otherCircleCollider.GetScaledRadius()));
		}
		else if (otherCollider.Is(BoxCollider::TypeIdClass()))
		{
			BoxCollider const & otherBoxCollider = static_cast<BoxCollider const &>(otherCollider);
			GetGameObject().Transform().SetPosition(otherPosition - normalizedDifferenceVector * (DistanceToEdgeOfBox(otherPosition - position) + otherBoxCollider.DistanceToEdgeOfBox(position - otherPosition)));
		}
	}

	gsl::owner<BoxCollider*> BoxCollider::Clone() const
	{
		return new BoxCollider(*this);
	}
}