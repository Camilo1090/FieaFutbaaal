#pragma once

#include "Entity.h"
#include "Factory.h"
#include "Transform.h"
#include "Collider.h"
#include "SpriteTypeEnum.h"

namespace FieaGameEngine
{
	class GameObject : public Entity
	{
		RTTI_DECLARATIONS(GameObject, Entity)

	public:
		static const std::string TransformKey;
		static const std::size_t TransformIndex;
		static const std::string ColliderKey;
		static const std::size_t ColliderIndex;
		static const std::string VelocityKey;
		static const std::size_t VelocityIndex;
		static const std::string AccelerationKey;
		static const std::size_t AccelerationIndex;
		static const std::string SpriteNameKey;
		static const std::size_t SpriteNameIndex;
		static Vector<Signature> Signatures();

	public:
		explicit GameObject(const std::string& sprite = std::string(), const std::string& name = std::string());
		GameObject(const GameObject&) = default;
		GameObject(GameObject&&) = default;
		GameObject& operator=(const GameObject&) = default;
		GameObject& operator=(GameObject&&) = default;
		virtual ~GameObject() = default;

		virtual gsl::owner<GameObject*> Clone() const override;
		//virtual void Update(WorldState& worldState) override;

		Transform& Transform();
		const FieaGameEngine::Transform& Transform() const;

		Collider& Collider();
		const FieaGameEngine::Collider& Collider() const;

		glm::vec2 GetVelocity() const;
		void SetVelocity(glm::vec2 const & velocity);

		glm::vec2 GetAcceleration() const;
		void SetAcceleration(glm::vec2 const & acceleration);

		const std::string& GetSpriteName() const;
		SpriteType GetSpriteType() const;

	protected:
		GameObject(RTTI::IdType type, const std::string& name = std::string());

	private:
		glm::vec4 mVelocity;
		glm::vec4 mAcceleration;
		std::string mSpriteName = "None";
	};

	CONCRETE_FACTORY(GameObject, Scope)
}
