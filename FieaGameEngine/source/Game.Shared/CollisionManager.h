#pragma once
#include "Attributed.h"
#include "World.h"
#include "GameObject.h"
#include "vector.h"
#include "Event.h"
#include "Collision.h"

namespace FieaGameEngine
{
	/// <summary>Collision Manager is a Singleton Class.</summary>
	class CollisionManager
	{
	public:
		CollisionManager(const CollisionManager& t_rhs) = delete;
		CollisionManager(CollisionManager&& t_rhs) = delete;
		CollisionManager& operator=(const CollisionManager& t_rhs) = delete;
		CollisionManager& operator=(CollisionManager&& t_rhs) = delete;
		
		~CollisionManager() = default;

		void Update();
		void ResolveCollision(Collider & collider1, Collider & collider2);

		static CollisionManager* getInstance();
		static void SetWorld(World & world);
		void RegisterCollider(Collider & collider);
		void UnregisterCollider(Collider & collider);
	private:
		
		static World* mWorld;
		static std::unique_ptr<CollisionManager> mInstance;
		Vector<Collider*> mColliders;

		CollisionManager() = default;
	};

}
