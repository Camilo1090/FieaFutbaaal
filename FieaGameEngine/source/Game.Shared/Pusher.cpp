#include "pch.h"
#include "Pusher.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Pusher);

	const std::string Pusher::TargetRotationKey = "TargetRotation";
	//const size_t Pusher::TargetRotationIndex = 2;
	const std::string Pusher::ForceKey = "Force";
	//const size_t Pusher::AddAccelIndex = 3;

	Vector<Signature> Pusher::Signatures()
	{
		return {
			{ TargetRotationKey, Datum::DatumType::FLOAT, 1, offsetof(Pusher, mTargetRotation) },
			{ ForceKey, Datum::DatumType::VECTOR, 1, offsetof(Pusher, mForce) }
		};
	}

	Pusher::Pusher() : GameObject(TypeIdClass())
	{
	}

	gsl::owner<Pusher*> Pusher::Clone() const
	{
		return new Pusher(*this);
	}
	float Pusher::GetTargetRotation()
	{
		return mTargetRotation;
	}
	glm::vec4 Pusher::GetForce()
	{
		return mForce;
	}
}