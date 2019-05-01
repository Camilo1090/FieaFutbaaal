#include "pch.h"
#include "Transform.h"
#include <cmath>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Transform)

	const std::string Transform::PositionKey = "Position";
	const std::string Transform::RotationKey = "Rotation";
	const std::string Transform::ScaleKey = "Scale";

	Vector<Signature> Transform::Signatures()
	{
		return {
			{ PositionKey, Datum::DatumType::VECTOR, 1, offsetof(Transform, mPosition) },
			{ RotationKey, Datum::DatumType::FLOAT, 1, offsetof(Transform, mRotation) },
			{ ScaleKey, Datum::DatumType::VECTOR, 1, offsetof(Transform, mScale) }
		};
	}

	Transform::Transform(const glm::vec4& position, float rotation, const glm::vec4& scale) 
		: Attributed(TypeIdClass()), mPosition(position), mRotation(rotation), mScale(scale)
	{
	}

	gsl::owner<Transform*> Transform::Clone() const
	{
		return new Transform(*this);
	}

	glm::vec2 Transform::GetPosition() const
	{
		return glm::vec2(mPosition.x, mPosition.y);
	}

	void Transform::SetPosition(glm::vec2 const & position)
	{
		mPosition.x = position.x;
		mPosition.y = position.y;
	}

	float Transform::GetRotation() const
	{
		return mRotation;
	}

	void Transform::SetRotation(float const & rotation)
	{
		mRotation = rotation;
	}

	glm::vec2 Transform::GetScale() const
	{
		return glm::vec2(mScale.x, mScale.y);
	}

	void Transform::SetScale(glm::vec2 const & scale)
	{
		mScale.x = scale.x;
		mScale.y = scale.y;
	}
	
	glm::vec2 Transform::Forward() const
	{
		return glm::vec2(cosf(mRotation), sinf(mRotation));
	}

	glm::vec2 Transform::Right() const
	{
		return glm::vec2(cosf(mRotation + 90), sinf(mRotation + 90));
	}
}
