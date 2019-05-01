#include "pch.h"
#include "ReactionCollision.h"
#include "Collision.h"
#include "Event.h"
#include "Sheep.h"
#include "Dog.h"
#include "Pusher.h"
#include "ScoreVolume.h"
#include "GameObject.h"



namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionCollision)

	Vector<Signature> ReactionCollision::Signatures()
	{
		return Vector<Signature>();
	}

	ReactionCollision::ReactionCollision(const std::string& name) : Reaction(TypeIdClass(), name)
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollision::ReactionCollision(const ReactionCollision& other) : Reaction(other)
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollision::ReactionCollision(ReactionCollision&& other) : Reaction(std::move(other))
	{
		Event<Collision>::Subscribe(*this);
	}


	ReactionCollision::~ReactionCollision()
	{
		Event<Collision>::Unsubscribe(*this);
	}

	gsl::owner<ReactionCollision*> ReactionCollision::Clone() const
	{
		return new ReactionCollision(*this);
	}

	void ReactionCollision::Notify(const EventPublisher& /*event*/)
	{
		//Event<Collision>* eventCollision = event.As <Event<Collision>>();
		//assert(eventCollision != nullptr);
		//const Collision& collisionData = eventCollision->Message();
		//if (collisionData.mObject1.Is(Sheep::TypeName()) || collisionData.mObject2.Is(Sheep::TypeName()))
		//{
		//	//hit wall
		//	if (collisionData.mObject1.Is(Wall::TypeName()) || collisionData.mObject2.Is(Wall::TypeName()))
		//	{
		//		//block
		//	}	
		//}
	}

	ReactionCollision::ReactionCollision(const std::string& name, IdType id) : Reaction(id, name)
	{
	}

	std::pair<bool, const GameObject*> ReactionCollision::isAnyOfTheseObjectsInvolvedInCollision(const GameObject& objectOne, const GameObject& objectTwo)
	{
		std::pair<bool, const GameObject*> resultPair;
		if (&objectOne == this->GetParent())
		{
			resultPair =  std::make_pair(true, &objectOne);
		}
		else if(&objectTwo == this->GetParent())
		{
			resultPair = std::make_pair(true, &objectTwo);
		}
		else
		{
			resultPair = std::make_pair(false, &objectOne);
		}
		return resultPair;
	}
}