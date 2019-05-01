#pragma once
#include "Collider.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class CircleCollider : public Collider
	{
		RTTI_DECLARATIONS(CircleCollider, Collider)

	public:
		static const std::string RadiusKey;
		static const std::size_t RadiusIndex;
		static const std::string ScaleKey;
		static const std::size_t ScaleIndex;

		static Vector<Signature> Signatures();

	public:
		CircleCollider();
		virtual ~CircleCollider();

		/// <summary>
		/// Returns the radius of the collider.
		/// </summary>
		/// <returns>The radius of the collider</returns>
		float GetRadius() const;

		/// <summary>
		/// Sets the collider's radius given a float.
		/// </summary>
		/// <param name="radius">The new radius of the collider</param>
		void SetRadius(float const & radius);


		/// <summary>
		/// Returns scale of the collider.
		/// </summary>
		/// <returns>The scale of the collider.</returns>
		float GetScale() const;

		/// <summary>
		/// Sets the collider's scale.
		/// </summary>
		/// <param name="radiusScale">The new scale of the collider</param>
		void SetScale(float const & scale);

		/// <summary>
		/// Returns the radius multiplied by the scale.
		/// </summary>
		/// <returns>The radius multiplied by the scale.</returns>
		float GetScaledRadius() const;

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
		/// Creates a copy of this circle collider.
		/// </summary>
		/// <returns>A pointer to the copied circle collider.</returns>
		virtual gsl::owner<CircleCollider*> Clone() const override;

	private:

		

		/// <summary>
		/// The radius of the collider.
		/// </summary>
		float mRadius;

		/// <summary>
		/// The scale of the radius of the collider.
		/// </summary>
		float mScale;
	};

	CONCRETE_FACTORY(CircleCollider, FieaGameEngine::Scope)
}