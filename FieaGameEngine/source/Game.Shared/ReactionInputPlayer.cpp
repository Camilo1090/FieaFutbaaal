#include "pch.h"
#include "ReactionInputPlayer.h"
#include "Event.h"
#include "Dog.h"
#include "CircleCollider.h"
#include "World.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionInputPlayer)

	const std::string ReactionInputPlayer::PlayerIndexKey = "PlayerIndex";
	const std::string ReactionInputPlayer::SpeedKey = "Speed";

	Vector<Signature> ReactionInputPlayer::Signatures()
	{
		return {
			{ PlayerIndexKey, Datum::DatumType::INTEGER, 1, offsetof(ReactionInputPlayer, mPlayerIndex) },
			{ SpeedKey, Datum::DatumType::FLOAT, 1, offsetof(ReactionInputPlayer, mSpeed) }
		};
	}

	ReactionInputPlayer::ReactionInputPlayer() : ReactionInput(TypeIdClass())
	{
	}

	void ReactionInputPlayer::Notify(const EventPublisher& event)
	{
		assert(event.Is(Event<InputManager*>::TypeIdClass()));
		const auto& actualEvent = static_cast<const Event<InputManager*>&>(event);

		if (mDog == nullptr)
		{
			mDog = GetParent<Dog>();
		}

		auto message = actualEvent.Message();
		
		if (mPlayerIndex == 0)
		{
			if (message->IsKeyPressed(InputManager::Inputs::W_KEY) || message->IsKeyHeld(InputManager::Inputs::W_KEY))
			{
				MovePlayer(glm::vec2(0, -1) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(0, -1), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::A_KEY) || message->IsKeyHeld(InputManager::Inputs::A_KEY))
			{
				MovePlayer(glm::vec2(-1, 0) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(-1, 0), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::S_KEY) || message->IsKeyHeld(InputManager::Inputs::S_KEY))
			{
				MovePlayer(glm::vec2(0, 1) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(0, 1), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::D_KEY) || message->IsKeyHeld(InputManager::Inputs::D_KEY))
			{
				MovePlayer(glm::vec2(1, 0) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(1, 0), glm::vec2(1, 0)));
			}
		}
		else
		{
			if (message->IsKeyPressed(InputManager::Inputs::UP_ARROW_KEY) || message->IsKeyHeld(InputManager::Inputs::UP_ARROW_KEY))
			{
				MovePlayer(glm::vec2(0, -1) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(0, -1), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::LEFT_ARROW_KEY) || message->IsKeyHeld(InputManager::Inputs::LEFT_ARROW_KEY))
			{
				MovePlayer(glm::vec2(-1, 0) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(-1, 0), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::DOWN_ARROW_KEY) || message->IsKeyHeld(InputManager::Inputs::DOWN_ARROW_KEY))
			{
				MovePlayer(glm::vec2(0, 1) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(0, 1), glm::vec2(1, 0)));
			}

			if (message->IsKeyPressed(InputManager::Inputs::RIGHT_ARROW_KEY) || message->IsKeyHeld(InputManager::Inputs::RIGHT_ARROW_KEY))
			{
				MovePlayer(glm::vec2(1, 0) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
				TurnPlayer(glm::orientedAngle(glm::vec2(1, 0), glm::vec2(1, 0)));
			}
		}

		if (message->IsAnalogMoved(mPlayerIndex))
		{
			float x = message->GetHorizontalAxis(mPlayerIndex);
			float y = message->GetVerticalAxis(mPlayerIndex);
			MovePlayer(glm::vec2(x, -y) * mSpeed * message->GetWorld().GetWorldState().GameTime->ElapsedGameTimeSeconds().count());
			TurnPlayer(glm::orientedAngle(glm::vec2(x, -y), glm::vec2(1, 0)));
		}

		if (message->IsButtonPressed(InputManager::Inputs::A_BUTTON, mPlayerIndex))
		{
			// bark
			if (mDog->Bark())
			{
				ActionList::Update(message->GetWorld().GetWorldState());
			}
		}
	}

	void ReactionInputPlayer::MovePlayer(const glm::vec2& displacement)
	{
		auto position = mDog->Transform().GetPosition();
		position += displacement;
		mDog->Transform().SetPosition(position);
	}

	void ReactionInputPlayer::TurnPlayer(float angle)
	{
		mDog->Transform().SetRotation(-angle * 180.0f / static_cast<float>(M_PI));
	}
}
