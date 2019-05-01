#include "pch.h"
#include "CollisionManager.h"
#include "World.h"

namespace FieaGameEngine
{
	std::unique_ptr<CollisionManager> CollisionManager::mInstance = nullptr;
	World* CollisionManager::mWorld = nullptr;

	void CollisionManager::Update()
	{
		for (size_t i = 0; i < mColliders.Size() - 1; ++i)
		{
			for (size_t j = i+1; j < mColliders.Size(); ++j)
			{
				if (mColliders[i]->GetCollisionChannel() != mColliders[j]->GetCollisionChannel())
				{
					if (mColliders[i]->IsCollidingWith(*mColliders[j]))
					{
						ResolveCollision(*mColliders[i], *mColliders[j]);
						Collision collision = Collision(mColliders[i]->GetGameObject(), mColliders[j]->GetGameObject());
						mWorld->GetEventQueue()->EnqueueEvent(std::make_shared<Event<Collision>>(collision), *mWorld->GetWorldState().GameTime);
					}
				}
			}
		}
	}

	void CollisionManager::ResolveCollision(Collider & collider1, Collider & collider2)
	{
		if (!collider1.GetIsTrigger() && !collider2.GetIsTrigger())
		{
			if (collider1.IsDynamic() && collider2.IsDynamic())
			{
				if (rand() % 2)
				{
					collider1.MoveOutOfCollider(collider2);
				}
				else
				{
					collider2.MoveOutOfCollider(collider1);
				}
			}
			else if (collider1.IsDynamic() && collider2.IsStatic())
			{
				collider1.MoveOutOfCollider(collider2);
			}
			else if (collider1.IsStatic() && collider2.IsDynamic())
			{
				collider2.MoveOutOfCollider(collider1);
			}
			
		}
	}

	CollisionManager* CollisionManager::getInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = std::unique_ptr<CollisionManager>(new CollisionManager());
		}
		return mInstance.get();
	}

	void CollisionManager::SetWorld(World & world)
	{
		getInstance();
		mWorld = &world;
	}

	void CollisionManager::RegisterCollider(Collider & collider)
	{
		mColliders.PushBack(&collider);
	}
	void CollisionManager::UnregisterCollider(Collider & collider)
	{
		mColliders.Remove(&collider);
	}
}