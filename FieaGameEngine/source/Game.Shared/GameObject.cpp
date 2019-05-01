#include "pch.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject)

	const std::string GameObject::TransformKey = "Transform";
	const std::size_t GameObject::TransformIndex = 3;
	const std::string GameObject::ColliderKey = "Collider";
	const std::size_t GameObject::ColliderIndex = 4;
	const std::string GameObject::VelocityKey = "Velocity";
	const std::size_t GameObject::VelocityIndex = 5;
	const std::string GameObject::AccelerationKey = "Acceleration";
	const std::size_t GameObject::AccelerationIndex = 6;
	const std::string GameObject::SpriteNameKey = "SpriteName";
	const std::size_t GameObject::SpriteNameIndex = 7;

	Vector<Signature> GameObject::Signatures()
	{
		return {
			{ TransformKey, Datum::DatumType::TABLE, 0, 0 },
			{ ColliderKey, Datum::DatumType::TABLE, 0, 0 },
			{ VelocityKey, Datum::DatumType::VECTOR, 1, offsetof(GameObject, mVelocity) },
			{ AccelerationKey, Datum::DatumType::VECTOR, 1, offsetof(GameObject, mAcceleration) },
			{ SpriteNameKey, Datum::DatumType::STRING, 1, offsetof(GameObject, mSpriteName) }
		};
	}

	GameObject::GameObject(const std::string& sprite, const std::string& name) :
		Entity(TypeIdClass(), name), mSpriteName(sprite)
	{
		assert(mList[TransformIndex]->first == TransformKey);
		assert(mList[ColliderIndex]->first == ColliderKey);
	}

	gsl::owner<GameObject*> GameObject::Clone() const
	{
		return new GameObject(*this);
	}

	Transform& GameObject::Transform()
	{
		Datum& datum = At(TransformIndex);
		assert(datum.Size() > 0);
		Scope& scope = datum[0];
		assert(scope.Is(Transform::TypeIdClass()));

		return static_cast<FieaGameEngine::Transform&>(scope);
	}

	const FieaGameEngine::Transform& GameObject::Transform() const
	{
		return const_cast<GameObject*>(this)->Transform();
	}

	Collider& GameObject::Collider()
	{
		Datum& datum = At(ColliderIndex);
		assert(datum.Size() > 0);
		Scope& scope = datum[0];
		assert(scope.Is(Collider::TypeIdClass()));

		return static_cast<FieaGameEngine::Collider&>(scope);
	}

	const FieaGameEngine::Collider& GameObject::Collider() const
	{
		return const_cast<GameObject*>(this)->Collider();
	}

	glm::vec2 GameObject::GetVelocity() const
	{
		return glm::vec2(mVelocity.x, mVelocity.y);
	}

	void GameObject::SetVelocity(glm::vec2 const & velocity)
	{
		mVelocity = glm::vec4(velocity.x, velocity.y, 0, 0);
	}

	glm::vec2 GameObject::GetAcceleration() const
	{
		return glm::vec2(mAcceleration.x, mAcceleration.y);
	}

	void GameObject::SetAcceleration(glm::vec2 const & acceleration)
	{
		mAcceleration = glm::vec4(acceleration.x, acceleration.y, 0, 0);
	}

	const std::string& GameObject::GetSpriteName() const
	{
		return mSpriteName;
	}

	SpriteType GameObject::GetSpriteType() const
	{
		return SpriteTypes.At(mSpriteName);
	}

	GameObject::GameObject(RTTI::IdType type, const std::string& name) : Entity(type, name)
	{
	}
}
