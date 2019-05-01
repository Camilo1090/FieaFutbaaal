#pragma once
#include "EventSubscriber.h"
#include "InputManager.h"
#include "Event.h"
#include "World.h"
#include <memory>

namespace FieaGameEngine
{

	class MenuManager :
		public EventSubscriber
	{
	public:
		static size_t RedPlayerScore;
		static size_t BluePlayerScore;
		static size_t RemainingSeconds;
		static bool Player1Ready;
		static bool Player2Ready;

		enum class GameState
		{
			SplashScreen,
			InstructionScreen,
			InGame,
			EndScreen
		};

		virtual ~MenuManager();

		static MenuManager* GetInstance();

		static void SetWorld(World& World);

		static GameState& GetGameState();

		virtual void Notify(const EventPublisher& eventPublisher) override;

	private:
		static GameState CurrentState;
		static World* AssociatedWorld;

		static const size_t DefaultGameLength = 120;

		static std::shared_ptr<MenuManager> MenuSingleton;
		MenuManager();
	};
}

