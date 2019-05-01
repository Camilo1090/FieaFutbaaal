#include "pch.h"
#include "ReactionCollisionScore.h"
#include "ActionIncrement.h"
#include "World.h"
#include "Sheep.h"
#include "Collision.h"
#include "Event.h"
#include "Dog.h"
#include "Pusher.h"
#include "ScoreVolume.h"
#include "GameObject.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionCollisionScore)

	Vector<Signature> ReactionCollisionScore::Signatures()
	{
		return Vector<Signature>();
	}


	ReactionCollisionScore::ReactionCollisionScore(const std::string& name) : ReactionCollision(name, TypeIdClass())
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollisionScore::ReactionCollisionScore(const ReactionCollisionScore & other) : ReactionCollision(other)
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollisionScore::ReactionCollisionScore(ReactionCollisionScore && other) : ReactionCollision(std::move(other))
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollisionScore::~ReactionCollisionScore()
	{
		Event<Collision>::Unsubscribe(*this);
	}

	gsl::owner<ReactionCollisionScore*> ReactionCollisionScore::Clone() const
	{
		return new ReactionCollisionScore(*this);
	}

	void ReactionCollisionScore::Notify(const EventPublisher& event)
	{
		Event<Collision>* eventCollision = event.As <Event<Collision>>();
		assert(eventCollision != nullptr);
		const Collision& collisionData = eventCollision->Message();
		Sheep * sheep = nullptr;
		ScoreVolume * score = nullptr;

		auto result = isAnyOfTheseObjectsInvolvedInCollision(collisionData.mObject1, collisionData.mObject2);

		if (result.first == true && result.second == &collisionData.mObject1 ||
			result.first == true && result.second == &collisionData.mObject2)
		{
			if ((collisionData.mObject1.Is(Sheep::TypeIdClass()) || collisionData.mObject2.Is(Sheep::TypeIdClass())) && (collisionData.mObject1.Is(ScoreVolume::TypeIdClass()) || collisionData.mObject2.Is(ScoreVolume::TypeIdClass())))
			{
				if (collisionData.mObject1.Is(Sheep::TypeIdClass()))
				{
					sheep = &static_cast<Sheep&>(collisionData.mObject1);
					score = &static_cast<ScoreVolume&>(collisionData.mObject2);
				}
				else
				{
					sheep = &static_cast<Sheep&>(collisionData.mObject2);
					score = &static_cast<ScoreVolume&>(collisionData.mObject1);
				}

				Scope * foundScope = nullptr;

				Search(World::SectorsKey, &foundScope);
				
				assert(foundScope != nullptr && foundScope->Is(World::TypeIdClass()));
				
				World * world = static_cast<World*>(foundScope);

				world->GetEventQueue()->EnqueueEvent(std::make_shared<Event<std::pair<bool, int>>>(Event<std::pair<bool, int>>(std::pair<bool, int>(score->GetIsPlayerOneScore(), sheep->GetPoints()))),*(world->GetWorldState().GameTime));

				//Sheep will no longer collide with score volume and will now collide blocking volume in front of goal
				sheep->Collider().SetCollisionChannel(score->Collider().GetCollisionChannel());
				
			}
		}
	}
}