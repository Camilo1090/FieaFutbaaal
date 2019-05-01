#include "pch.h"
#include "ReactionSpawn.h"
#include "Event.h"
#include "SheepSpawner.h"
#include "World.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionSpawn)

	ReactionSpawn::ReactionSpawn(const std::string& name) : Reaction(TypeIdClass(), name)
	{
		Event<SheepSpawner*>::Subscribe(*this);
	}

	ReactionSpawn::ReactionSpawn(const ReactionSpawn& other) : Reaction(other)
	{
		Event<SheepSpawner*>::Subscribe(*this);
	}

	ReactionSpawn::ReactionSpawn(ReactionSpawn&& other) : Reaction(std::move(other))
	{
		Event<SheepSpawner*>::Subscribe(*this);
	}

	ReactionSpawn::~ReactionSpawn()
	{
		Event<SheepSpawner*>::Unsubscribe(*this);
	}

	gsl::owner<ReactionSpawn*> ReactionSpawn::Clone() const
	{
		return new ReactionSpawn(*this);
	}

	void ReactionSpawn::Notify(const EventPublisher & event)
	{
		Event<SheepSpawner*>* eventSpawn = event.As <Event<SheepSpawner*>>();
		assert(eventSpawn != nullptr);
		const auto& message = eventSpawn->Message();
		
		if (mParent == message) 
		{
			if (mWorld == nullptr)
			{
				Scope* scope = nullptr;
				Search(World::SectorsKey, &scope);

				if (scope != nullptr)
				{
					assert((scope)->Is(World::TypeIdClass()));
					mWorld = static_cast<World*>(scope);
				}
			}

			if (mSheepSpawner == nullptr)
			{
				mSheepSpawner = GetParent<SheepSpawner>();
			}

			auto& actions = Actions();
			for (size_t i = 0; i < actions.Size(); ++i)
			{
				assert(actions[i].Is(Action::TypeIdClass()));
				auto& action = static_cast<Action&>(actions[i]);
				action.Update(mWorld->GetWorldState());
			}

			auto newEvent = std::make_shared<Event<SheepSpawner*>>(mSheepSpawner);
			std::int32_t delay = mSheepSpawner->GetMinSpawnDelay() + std::rand() % mSheepSpawner->GetMaxSpawnDelay();
			mWorld->GetEventQueue()->EnqueueEvent(newEvent, *mWorld->GetWorldState().GameTime, std::chrono::milliseconds(delay));
		}
	}

	SheepSpawner * ReactionSpawn::GetSheepSpawner()
	{
		return mSheepSpawner;
	}

	World * ReactionSpawn::GetWorld()
	{
		return mWorld;
	}

	Vector<Signature> ReactionSpawn::Signatures()
	{
		return Vector<Signature>();
	}

}