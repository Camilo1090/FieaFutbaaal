#pragma once

#include "Attributed.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Transform : public Attributed
	{
		RTTI_DECLARATIONS(Transform, Attributed)

	public:
		static const std::string PositionKey;
		static const std::string RotationKey;
		static const std::string ScaleKey;
		static Vector<Signature> Signatures();

	public:
		explicit Transform(const glm::vec4& position = glm::vec4(), float rotation = 0.0f, const glm::vec4& scale = glm::vec4());
		Transform(const Transform&) = default;
		Transform(Transform&&) = default;
		Transform& operator=(const Transform&) = default;
		Transform& operator=(Transform&&) = default;
		virtual ~Transform() = default;

		virtual gsl::owner<Transform*> Clone() const override;

		glm::vec2 GetPosition() const;
		void SetPosition(glm::vec2 const & position);

		float GetRotation() const;
		void SetRotation(float const & rotation);

		glm::vec2 GetScale() const;
		void SetScale(glm::vec2 const & scale);

		glm::vec2 Forward() const;

		glm::vec2 Right() const;

	private:
		glm::vec4 mPosition;
		float mRotation;
		glm::vec4 mScale;
	};

	CONCRETE_FACTORY(Transform, Scope)
}
