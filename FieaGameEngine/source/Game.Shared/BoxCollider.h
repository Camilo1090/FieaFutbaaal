#pragma once
#include "Collider.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class BoxCollider :	public Collider
	{
		RTTI_DECLARATIONS(BoxCollider, Collider)

	public:
		static const std::string ExtentsKey;
		static const std::size_t ExtentsIndex;
		static const std::string ScaleKey;
		static const std::size_t ScaleIndex;

		static Vector<Signature> Signatures();

	public:
		BoxCollider();
		virtual ~BoxCollider();

		/// <summary>
		/// Returns the x and y extents of the collider in a vec2.
		/// Should not be called on circles.
		/// </summary>
		/// <returns>The x and y extents of the collider in a vec2.</returns>
		glm::vec2 GetExtents() const;

		/// <summary>
		/// Sets the collider's extents given a vec2.
		/// Should not be called on circles.
		/// </summary>
		/// <param name="extents">Vec2 that will be the colliders extents</param>
		void SetExtents(glm::vec2 const & extents);

		/// <summary>
		/// Sets the collider's extents given a vec2.
		/// Should not be called on circles.
		/// </summary>
		/// <param name="extents">Vec4 that will be the colliders extents.</param>
		void SetExtents(glm::vec4 const & extents);

		/// <summary>
		/// Returns the x and y scale of the collider.
		/// Should not be called on a circle
		/// </summary>
		/// <returns>The x and y scale of the collider.</returns>
		glm::vec2 GetScale() const;

		/// <summary>
		/// Set's the colliders scale given a vec2.
		/// Should not be used on circles.
		/// </summary>
		/// <param name="colliderScale">The new extent scale of the box.</param>
		void SetScale(glm::vec2 const & colliderScale);

		/// <summary>
		/// Sets the colliders scale given a vec4.
		/// </summary>
		/// <param name="colliderScale">The new vec4 scale of the collider</param>
		void SetScale(glm::vec4 const & colliderScale);

		/// <summary>
		/// Returns the extents multiplied by their respective scales.
		/// </summary>
		/// <returns>The extents multiplied by their respective scales.</returns>
		glm::vec2 GetScaledExtents() const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		float DistanceToEdgeOfBox(glm::vec2 directionVector) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		float DistanceToEdgeOfBox(float angle) const;

		/// <summary>
		/// Checks if we are colliding with anothe collider.
		/// Can also take in a pointer to a vec4 to return what side the collision occured on. If a value in the vector is non zero it means a collision occured on that side.
		/// The format of the vec4 is vec4(top,right,bottom,left).
		/// </summary>
		/// <param name="otherCollider">Collider to check if we are colliding with</param>
		/// <param name="sidesOfCollision">Pointer to an out parameter which stores the side of the collision as a vec4.</param>
		/// <returns>Whether we are overlapping another collider.</returns>
		virtual bool IsCollidingWith(const Collider& otherCollider) const override;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="otherCollider"></param>
		virtual void MoveOutOfCollider(Collider const & otherCollider) override;

		/// <summary>
		/// Creates a copy of this box collider.
		/// </summary>
		/// <returns>A pointer to the copied box collider.</returns>
		virtual gsl::owner<BoxCollider*> Clone() const override;

	protected:
		explicit BoxCollider(RTTI::IdType type);

	private:

		

		/// <summary>
		/// The extents of the box collider.
		/// </summary>
		glm::vec4 mExtents;

		/// <summary>
		/// The scale of the extents of the collider.
		/// </summary>
		glm::vec4 mScale;
	};

	CONCRETE_FACTORY(BoxCollider, FieaGameEngine::Scope)
}