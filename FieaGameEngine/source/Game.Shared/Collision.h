#pragma once
#include "GameObject.h"

namespace FieaGameEngine
{
	class Collision
	{
	public:
		explicit Collision(GameObject & objectOne, GameObject & objectTwo);
		~Collision() = default;


		/// <summary>
		/// Reference to one of the game objects involved in a collision.
		/// </summary>
		GameObject& mObject1;

		/// <summary>
		/// Reference to the other game object involved in a collision.
		/// </summary>
		GameObject& mObject2;


	};

}