#include "pch.h"
#include "ReactionCollisionForce.h"
#include <math.h>
#include "ActionTurn.h"
#include "ActionAddForce.h"
#include "World.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "Event.h"
#include "Sheep.h"
#include "Dog.h"
#include "Pusher.h"
#include "ScoreVolume.h"
#include "GameObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionCollisionForce)

	Vector<Signature> ReactionCollisionForce::Signatures()
	{
		return Vector<Signature>();
	}

	ReactionCollisionForce::ReactionCollisionForce(const std::string& name) : ReactionCollision(name, TypeIdClass())
	{
	}

	ReactionCollisionForce::ReactionCollisionForce(const ReactionCollisionForce & other)
		: ReactionCollision(other)
	{
		Event<Collision>::Subscribe(*this);
	}

	ReactionCollisionForce::ReactionCollisionForce(ReactionCollisionForce && other)
		: ReactionCollision(std::move(other))
	{
		Event<Collision>::Subscribe(*this);
	}


	ReactionCollisionForce::~ReactionCollisionForce()
	{
		Event<Collision>::Unsubscribe(*this);
	}

	gsl::owner<ReactionCollisionForce*> ReactionCollisionForce::Clone() const
	{
		return new ReactionCollisionForce(*this);
	}

	void ReactionCollisionForce::Notify(const EventPublisher & event)
	{
		Event<Collision>* eventCollision = event.As <Event<Collision>>();
		assert(eventCollision != nullptr);
		const Collision& collisionData = eventCollision->Message();
		Sheep* sheep = nullptr;

		auto result = isAnyOfTheseObjectsInvolvedInCollision(collisionData.mObject1, collisionData.mObject2);
		if (result.first == true && result.second == &collisionData.mObject1 ||
			result.first == true && result.second == &collisionData.mObject2)
		{
			if (collisionData.mObject1.Is(Sheep::TypeIdClass()) || collisionData.mObject2.Is(Sheep::TypeIdClass()))
			{
				if (collisionData.mObject1.Is(Sheep::TypeIdClass()))
				{
					sheep = static_cast<Sheep*>(&collisionData.mObject1);
				}
				else
				{
					sheep = static_cast<Sheep*>(&collisionData.mObject2);
				}

				//hit by bark/fear radius
				if (collisionData.mObject1.Is(Dog::TypeIdClass()) || collisionData.mObject2.Is(Dog::TypeIdClass()))
				{
					Dog* dog = nullptr;
					if (collisionData.mObject1.Is(Dog::TypeIdClass()))
					{
						dog = static_cast<Dog*>(&collisionData.mObject1);
					}
					else
					{
						dog = static_cast<Dog*>(&collisionData.mObject2);
					}
					//calculate rotation sheep needs to move towards
					glm::vec2 vector = sheep->Transform().GetPosition() - dog->Transform().GetPosition();
					//float targetRotation = atan2f(vector.y, vector.x);

					//calculate acceleration
					//CircleCollider* barkCollider = &dog->GetBarkCollider();
					//float barkScale = barkCollider->GetScale();
					glm::vec2 newVelocity = vector * sheep->GetMaxSpeed();
					//dog->At(Dog::BarkScaleKey).Get<float>() - barkScale);
					sheep->SetVelocity(newVelocity);
					float angle = glm::orientedAngle(glm::normalize(newVelocity), glm::vec2(1, 0));
					sheep->Transform().SetRotation(-angle * 180.0f / static_cast<float>(M_PI));

					//update sheeps ActionUpdateTargetRotation
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
							actions[i]["Target"] = ActionTurn::TargetKey;
							actions[i]["TargetRotation"] = targetRotation;

						}*/
						action.Update(world->GetWorldState());
					}

				}
				//hit invisible boxes (to keep from getting stuck)
				else if (collisionData.mObject1.Is(Pusher::TypeName()) || collisionData.mObject2.Is(Pusher::TypeName()))
				{
					//update sheeps ActionUpdateTargetRotation
					Pusher* pusher;
					if (collisionData.mObject1.Is(Pusher::TypeIdClass()))
					{
						pusher = static_cast<Pusher*>(&collisionData.mObject1);
					}
					else
					{
						pusher = static_cast<Pusher*>(&collisionData.mObject2);
					}

					//calculate acceleration
					//update sheeps ActionUpdateTargetRotation
					Scope* temp = nullptr;
					Search(World::SectorsKey, &temp);
					World* world = temp->As<World>();
					assert(world->Is(World::TypeIdClass()));
					Datum& actions = Actions();
					for (size_t i = 0; i < actions.Size(); ++i)
					{
						//update accel
						assert(actions[i].Is(Action::TypeIdClass()));
						auto& action = static_cast<Action&>(actions[i]);
						if (nullptr != action.As<ActionAddForce>())
						{
							actions[i]["Target"] = GameObject::TransformKey;
							auto force = pusher->GetForce();
							actions[i]["Force"] = glm::vec4(force.x, force.y, 0, 0);
							float angle = glm::orientedAngle(glm::normalize(glm::vec2(force.x, force.y)), glm::vec2(1, 0));
							sheep->Transform().SetRotation(-angle * 180.0f / static_cast<float>(M_PI));
						}
						action.Update(world->GetWorldState());
					}
				}
			}
		}
		
	}
}