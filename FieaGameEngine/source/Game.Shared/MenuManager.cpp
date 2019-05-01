#include "pch.h"
#include "MenuManager.h"
#include "AudioManager.h"

namespace FieaGameEngine
{
	std::shared_ptr<MenuManager> MenuManager::MenuSingleton = nullptr;

	size_t MenuManager::RedPlayerScore = 0;
	size_t MenuManager::BluePlayerScore = 0;
	size_t MenuManager::RemainingSeconds = 0;
	World* MenuManager::AssociatedWorld = nullptr;
	bool MenuManager::Player1Ready = false;
	bool MenuManager::Player2Ready = false;

	MenuManager::GameState MenuManager::CurrentState;

	MenuManager::MenuManager()
	{
		Event<InputManager*>::Subscribe(*this);

		//Used to track score events.
		Event<std::pair<bool,int>>::Subscribe(*this);

		//Event of void is used to track time events.
		Event<char>::Subscribe(*this);
		CurrentState = GameState::SplashScreen;
	}

	MenuManager::~MenuManager()
	{
		Event<InputManager*>::Unsubscribe(*this);
		//Event<std::pair<bool, int>>::Unsubscribe(*this);
		//Event<char>::Unsubscribe(*this);
	}

	MenuManager* MenuManager::GetInstance()
	{
		if (MenuSingleton == nullptr)
		{
			MenuSingleton.reset(new MenuManager);
		}

		return MenuSingleton.get();
	}

	void MenuManager::SetWorld(World & World)
	{
		AssociatedWorld = &World;
	}

	MenuManager::GameState & MenuManager::GetGameState()
	{
		return CurrentState;
	}

	void MenuManager::Notify(const EventPublisher & eventPublisher)
	{
		if (eventPublisher.Is(Event<InputManager*>::TypeIdClass()))
		{
			Event<InputManager*> inputEvent = static_cast<Event<InputManager*> const &>(eventPublisher);

			switch (CurrentState)
			{
			case (GameState::SplashScreen):
				//AudioManager::StopAudio(false);
				//AudioManager::PlayAduio(AudioManager::GetSample(AudioManager::InstructionScreenMusic), false);
				CurrentState = GameState::InstructionScreen;
				break;
			case (GameState::InstructionScreen):
				if (inputEvent.Message()->IsButtonPressed(InputManager::Inputs::A_BUTTON, 0))
				{
					Player1Ready = true;
				}

				if(inputEvent.Message()->IsButtonPressed(InputManager::Inputs::A_BUTTON, 1))
				{
					Player2Ready = true;
				}

				//Once both have been pressed, call start on the world.
				if (Player1Ready && Player2Ready)
				{
					AudioManager::StopAudio(false);
					AudioManager::PlayAduio(AudioManager::GetSample(AudioManager::GameMusic), false);

					//Start timer.
					RemainingSeconds = DefaultGameLength;
					std::shared_ptr<Event<char>> Message = std::make_shared<Event<char>>();
					AssociatedWorld->GetEventQueue()->EnqueueEvent(Message, *AssociatedWorld->GetWorldState().GameTime, std::chrono::seconds(1));

					AssociatedWorld->Start();
					Player1Ready = false;
					Player2Ready = false;
					CurrentState = GameState::InGame;
				}
				break;
			case (GameState::InGame):
				//Don't do anything.
				break;
			case (GameState::EndScreen):
				break;
			}
		}
		else if (eventPublisher.Is(Event<char>::TypeIdClass()))
		{
			RemainingSeconds -= 1;
			if (RemainingSeconds > 0)
			{
				std::shared_ptr<Event<char>> Message = std::make_shared<Event<char>>();
				AssociatedWorld->GetEventQueue()->EnqueueEvent(Message, *AssociatedWorld->GetWorldState().GameTime, std::chrono::seconds(1));
			}
			else
			{
				AudioManager::StopAudio(false);
				AudioManager::PlayAduio(AudioManager::GetSample(AudioManager::EndScreenMusic), false);
				CurrentState = GameState::EndScreen;

				//Kill the event queue.
				AssociatedWorld->GetEventQueue()->Clear();
				//CHARLES, PLAY THE END MUSIC.
			}
		}
		else if (eventPublisher.Is(Event<std::pair<bool, int>>::TypeIdClass()))
		{
			Event<std::pair<bool, int>> scoreEvent = static_cast<Event<std::pair<bool, int>> const &>(eventPublisher);
			if (scoreEvent.Message().first)
			{
				if (static_cast<int>(BluePlayerScore) >= (-1 * scoreEvent.Message().second))
				{
					BluePlayerScore += scoreEvent.Message().second;
				}
				else
				{
					BluePlayerScore = 0;
				}
			}
			else
			{
				if (static_cast<int>(RedPlayerScore) >= (-1 * scoreEvent.Message().second))
				{
					RedPlayerScore += scoreEvent.Message().second;
				}
				else
				{
					RedPlayerScore = 0;
				}
			}
		}
	}
}