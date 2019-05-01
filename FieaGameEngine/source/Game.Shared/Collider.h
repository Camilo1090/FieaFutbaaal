#pragma once
#include "Attributed.h"
#include "Factory.h"

namespace FieaGameEngine
{

	class Collider : public Attributed
	{
		RTTI_DECLARATIONS(Collider, Attributed)

	public:
		static const std::string CollisionChannelKey;
		static const std::size_t CollisionChannelIndex;
		static const std::string ColliderTypeKey;
		static const std::size_t ColliderTypeIndex;
		static const std::string IsTriggerKey;
		static const std::size_t IsTriggerIndex;

		static Vector<Signature> Signatures();

	public:
		Collider(const Collider& other);
		Collider(Collider&& other);
		Collider& operator=(const Collider&) = default;
		Collider& operator=(Collider&&) = default;
		virtual ~Collider();		

		/// <summary>
		/// Returns the game object that owns this collider.
		/// </summary>
		/// <returns>The game object that owns this collider</returns>
		class GameObject & GetGameObject();
		
		/// <summary>
		/// Returns the game object that owns this collider.
		/// </summary>
		/// <returns>The game object that owns this collider</returns>
		class GameObject const & GetGameObject() const;

		/// <summary>
		/// Checks if we are colliding with anothe collider.
		/// Can also take in a pointer to a vec4 to return what side the collision occured on. If a value in the vector is non zero it means a collision occured on that side.
		/// The format of the vec4 is vec4(top,right,bottom,left).
		/// </summary>
		/// <param name="otherCollider">Collider to check if we are colliding with</param>
		/// <param name="sidesOfCollision">Pointer to an out parameter which stores the side of the collision as a vec4.</param>
		/// <returns>Whether we are overlapping another collider.</returns>
		virtual bool IsCollidingWith(const Collider& otherCollider) const = 0;

		/// <summary>
		/// Returns the collider channel.
		/// </summary>
		/// <returns>The collider channel.</returns>
		std::int32_t GetCollisionChannel();

		/// <summary>
		/// Sets the collider channel.
		/// </summary>
		/// <param name="newChannel">The new collider channel.</param>
		void SetCollisionChannel (int const & newChannel);

		/// <summary>
		/// Returns the collider type.
		/// </summary>
		/// <returns>The collider type.</returns>
		std::int32_t GetColliderType();

		/// <summary>
		/// Sets the collider type. 0 is static non zero is dynamic.
		/// </summary>
		/// <param name="colliderType"></param>
		void SetColliderType(int const & colliderType);

		/// <summary>
		/// Returns whether the collider is static.
		/// </summary>
		/// <returns>Whether the collider is static.</returns>
		bool IsStatic() const;

		/// <summary>
		/// Returns whether the collider is dynamic.
		/// </summary>
		/// <returns>Whether the collider is dynamic</returns>
		bool IsDynamic() const;

		/// <summary>
		/// Gets whether the colliser is a trigger.
		/// </summary>
		/// <returns>whether the colliser is a trigger.</returns>
		bool GetIsTrigger();

		/// <summary>
		/// Sets whether the collider is a trigger
		/// </summary>
		/// <param name="isTrigger">The new trigger setting of the collider.</param>
		void SetIsTrigger(bool const & isTrigger);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="otherCollider"></param>
		virtual void MoveOutOfCollider(Collider const & otherCollider) = 0;

	protected:
		/// <summary>
		/// Constructor, needs to know which type is being instantiated
		/// </summary>
		/// <param name="type">type id</param>
		explicit Collider(RTTI::IdType type);

	private:

		/// <summary>
		/// Colliders on the same collision channel as one another will not trigger collisions with one another.
		/// </summary>
		std::int32_t mCollisionChannel = 0;

		/// <summary>
		/// Colliders can be either static (0 value) or dyanmic(non - 0 value).
		/// Dynamic - Static : Dynamic colliders will be moved out of static objects when they collide.
		/// Dynamic - Dynamic : Dynamic colliders have a 50% chance of either moving out of other dynamic objects they are colliding with, or moving the other dynamic object out of themselves.
		/// Static - Static : Static colliders will not move out of each other when they collider. 
		/// </summary>
		std::int32_t mColliderType = 0;

		/// <summary>
		/// Trigger colliders will not move as a result of a collision nor will they be moved as the result of a collision.
		/// </summary>
		std::int32_t mIsTrigger = 0;
	};
}