#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Collider)

	const std::string Collider::CollisionChannelKey = "CollisionChannel";
	const std::size_t Collider::CollisionChannelIndex = 1;
	const std::string Collider::ColliderTypeKey = "ColliderType";
	const std::size_t Collider::ColliderTypeIndex = 2;
	const std::string Collider::IsTriggerKey = "IsTrigger";
	const std::size_t Collider::IsTriggerIndex = 3;

	Vector<Signature> Collider::Signatures()
	{
		return {
			{ CollisionChannelKey, Datum::DatumType::INTEGER, 1, offsetof(Collider, mCollisionChannel)},
			{ ColliderTypeKey, Datum::DatumType::INTEGER, 1, offsetof(Collider, mColliderType)},
			{ IsTriggerKey, Datum::DatumType::INTEGER, 1, offsetof(Collider, mIsTrigger)}
		};
	}

	std::int32_t Collider::GetCollisionChannel()
	{
		return mCollisionChannel;
	}

	void Collider::SetCollisionChannel(int const & newChannel)
	{
		mCollisionChannel = newChannel;
	}

	std::int32_t Collider::GetColliderType()
	{
		return mColliderType;
	}

	void Collider::SetColliderType(int const & colliderType)
	{
		mColliderType = colliderType;
		colliderType;
	}

	bool Collider::IsStatic() const
	{
		return !mColliderType;
	}

	bool Collider::IsDynamic() const
	{
		return mColliderType;
	}

	bool Collider::GetIsTrigger()
	{
		return mIsTrigger;
	}

	void Collider::SetIsTrigger(bool const & isTrigger)
	{
		mIsTrigger = isTrigger;
	}

	Collider::Collider(RTTI::IdType type) : Attributed(type)
	{
		CollisionManager::getInstance()->RegisterCollider(*this);
		assert(mList[CollisionChannelIndex]->first == CollisionChannelKey);
		assert(mList[ColliderTypeIndex]->first == ColliderTypeKey);
		assert(mList[IsTriggerIndex]->first == IsTriggerKey);
	}

	

	Collider::Collider(const Collider & other) : Attributed(other)
	{
		other;
		mCollisionChannel = other.mCollisionChannel;
		mColliderType = other.mColliderType;
		mIsTrigger = other.mIsTrigger;
		CollisionManager::getInstance()->RegisterCollider(*this);
	}

	Collider::Collider(Collider && other) : Attributed(std::move(other))
	{
		mCollisionChannel = std::move(other.mCollisionChannel);
		mColliderType = std::move(other.mColliderType);
		mIsTrigger = std::move(other.mIsTrigger);
		CollisionManager::getInstance()->RegisterCollider(*this);
		other;
	}

	Collider::~Collider()
	{
		CollisionManager::getInstance()->UnregisterCollider(*this);
	}

	GameObject & Collider::GetGameObject()
	{
		assert(mParent->Is(GameObject::TypeIdClass()));
		return static_cast<GameObject &>(*mParent);
	}

	GameObject const & Collider::GetGameObject() const
	{
		assert(mParent->Is(GameObject::TypeIdClass()));
		return static_cast<GameObject &>(*mParent);
	}
}