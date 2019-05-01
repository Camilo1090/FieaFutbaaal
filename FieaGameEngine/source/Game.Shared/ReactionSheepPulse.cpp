#include "pch.h"
#include "ReactionSheepPulse.h"
#include "Event.h"
#include "Sheep.h"
#include "ActionAddForce.h"
#include "ActionTurn.h"
#include "World.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionSheepPulse)

	const std::string ReactionSheepPulse::RotationRange = "RotationRange";
	const std::string ReactionSheepPulse::MinForceX = "MinForceX";
	const std::string ReactionSheepPulse::MaxForceX = "MaxForceX";
	const std::string ReactionSheepPulse::MinForceY = "MinForceY";
	const std::string ReactionSheepPulse::MaxForceY = "MaxForceY";

	Vector<Signature> ReactionSheepPulse::Signatures()
	{
		return {
			{ RotationRange, Datum::DatumType::INTEGER, 1, offsetof(ReactionSheepPulse, mRotationRange) },
			{ MinForceX, Datum::DatumType::INTEGER, 1, offsetof(ReactionSheepPulse, mMinForceX) },
			{ MaxForceX, Datum::DatumType::INTEGER, 1, offsetof(ReactionSheepPulse, mMaxForceX) },
			{ MinForceY, Datum::DatumType::INTEGER, 1, offsetof(ReactionSheepPulse, mMinForceY) },
			{ MaxForceY, Datum::DatumType::INTEGER, 1, offsetof(ReactionSheepPulse, mMaxForceY) }
		};
	}

	ReactionSheepPulse::ReactionSheepPulse(const std::string& name) : Reaction(TypeIdClass(), name)
	{
		Event<Sheep*>::Subscribe(*this);
	}

	ReactionSheepPulse::~ReactionSheepPulse()
	{
		Event<Sheep*>::Unsubscribe(*this);
	}

	ReactionSheepPulse::ReactionSheepPulse(const ReactionSheepPulse& other) : 
		Reaction(other), mRotationRange(other.mRotationRange), mMinForceX(other.mMinForceX), mMaxForceX(other.mMaxForceX),
		mMinForceY(other.mMinForceY), mMaxForceY(other.mMaxForceY)
	{
		Event<Sheep*>::Subscribe(*this);
	}

	ReactionSheepPulse::ReactionSheepPulse(ReactionSheepPulse&& other) : Reaction(std::move(other))
	{
		Event<Sheep*>::Subscribe(*this);
	}

	gsl::owner<ReactionSheepPulse*> ReactionSheepPulse::Clone() const
	{
		return new ReactionSheepPulse(*this);
	}

	void ReactionSheepPulse::Notify(const EventPublisher & event)
	{
		Event<Sheep*>* eventSheep = event.As<Event<Sheep*>>();
		assert(eventSheep != nullptr);
		Sheep* const sheep = eventSheep->Message();
		if (sheep == GetParent())
		{
			Datum& actions = Actions();
			Scope* temp = nullptr;
			Search(World::SectorsKey, &temp);
			World* world = temp->As<World>();
			assert(world->Is(World::TypeIdClass()));
			for (size_t i = 0; i < actions.Size(); ++i)
			{
				assert(actions[i].Is(Action::TypeIdClass()));
				auto& action = static_cast<Action&>(actions[i]);
				//update rotation
				/*if (nullptr != actions[i].As<ActionTurn>())
				{
					actions[i]["Target"] = GameObject::TransformKey;
					int angleValue = rand() % static_cast<int>(mRotationRange);
					if (rand() % 2 == 0)
					{
						angleValue = -angleValue;
						angleValue = 360 + angleValue;
					}
					actions[i]["TargetRotation"] = static_cast<float>(angleValue);

				}*/
				//update accel
				if (nullptr != actions[i].As<ActionAddForce>())
				{
					actions[i]["Target"] = GameObject::TransformKey;
					int accelX = mMinForceX + (rand() % static_cast<int>(mMaxForceX - mMinForceX));
					if (rand() % 2 == 0)
					{
						accelX *= -1;
					}
					int accelY = mMinForceY + (rand() % static_cast<int>(mMaxForceY - mMinForceY));
					if (rand() % 2 == 0)
					{
						accelY *= -1;
					}
					actions[i]["Force"] = glm::vec4(accelX, accelY, 0, 0);
					float angle = glm::orientedAngle(glm::normalize(glm::vec2(accelX, accelY)), glm::vec2(1, 0));
					sheep->Transform().SetRotation(-angle * 180.0f / static_cast<float>(M_PI));
				}
				
				action.Update(world->GetWorldState());
			}
			std::shared_ptr<Event<Sheep*>> newSheepEvent = std::make_shared<Event<Sheep*>>(sheep);
			world->GetEventQueue()->EnqueueEvent(newSheepEvent, *world->GetWorldState().GameTime, sheep->GetRandomPulseDelay());
		}
	}
}