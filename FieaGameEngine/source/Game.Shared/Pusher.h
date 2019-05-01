#pragma once
#include "GameObject.h"
namespace FieaGameEngine
{
	class Pusher : public GameObject
	{
		RTTI_DECLARATIONS(Pusher, GameObject)

	public:
		static const std::string TargetRotationKey;
		//static const size_t TargetRotationIndex;
		static const std::string ForceKey;
		//static const size_t AddAccelIndex;
		static Vector<Signature> Signatures();

	public:
		Pusher();
		virtual ~Pusher() = default;
		Pusher(const Pusher&) = default;
		Pusher(Pusher&&) = default;
		Pusher& operator=(const Pusher&) = default;
		Pusher& operator=(Pusher&&) = default;

		virtual gsl::owner<Pusher*> Clone() const override;

		float GetTargetRotation();
		glm::vec4 GetForce();

	private:
		float mTargetRotation;
		glm::vec4 mForce;
	};
	CONCRETE_FACTORY(Pusher, Scope)
}