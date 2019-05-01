#include "pch.h"
#include "Collision.h"

namespace FieaGameEngine
{
	Collision::Collision(GameObject & objectOne, GameObject & objectTwo) : mObject1(objectOne), mObject2(objectTwo)
	{
	}
}