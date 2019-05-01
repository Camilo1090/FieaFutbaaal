#include "pch.h"
#include "InputManager.h"

#include <memory>

#include "EventMessageAttributed.h"
#include "EventQueue.h"
#include "Event.h"
#include "World.h"
#include "WorldState.h"

namespace FieaGameEngine
{
	InputManager* InputManager::sInstance = nullptr;

	HashMap<std::int32_t, bool> InputManager::mKeyPressed = {
		{ static_cast<std::int32_t>(Inputs::W_KEY), false},
		{ static_cast<std::int32_t>(Inputs::A_KEY), false},
		{ static_cast<std::int32_t>(Inputs::S_KEY), false},
		{ static_cast<std::int32_t>(Inputs::D_KEY), false},
		{ static_cast<std::int32_t>(Inputs::CTRL_KEY), false},
		{ static_cast<std::int32_t>(Inputs::SPACE_KEY), false},
		{ static_cast<std::int32_t>(Inputs::LEFT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::UP_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::RIGHT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::DOWN_ARROW_KEY), false},
	};

	HashMap<std::int32_t, bool> InputManager::mKeyHeld = {
		{ static_cast<std::int32_t>(Inputs::W_KEY), false},
		{ static_cast<std::int32_t>(Inputs::A_KEY), false},
		{ static_cast<std::int32_t>(Inputs::S_KEY), false},
		{ static_cast<std::int32_t>(Inputs::D_KEY), false},
		{ static_cast<std::int32_t>(Inputs::CTRL_KEY), false},
		{ static_cast<std::int32_t>(Inputs::SPACE_KEY), false},
		{ static_cast<std::int32_t>(Inputs::LEFT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::UP_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::RIGHT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::DOWN_ARROW_KEY), false},
	};

	HashMap<std::int32_t, bool> InputManager::mKeyReleased = {
		{ static_cast<std::int32_t>(Inputs::W_KEY), false},
		{ static_cast<std::int32_t>(Inputs::A_KEY), false},
		{ static_cast<std::int32_t>(Inputs::S_KEY), false},
		{ static_cast<std::int32_t>(Inputs::D_KEY), false},
		{ static_cast<std::int32_t>(Inputs::CTRL_KEY), false},
		{ static_cast<std::int32_t>(Inputs::SPACE_KEY), false},
		{ static_cast<std::int32_t>(Inputs::LEFT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::UP_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::RIGHT_ARROW_KEY), false},
		{ static_cast<std::int32_t>(Inputs::DOWN_ARROW_KEY), false},
	};

	InputManager* InputManager::CreateInstance()
	{
		assert(sInstance == nullptr);
		sInstance = new InputManager();
		return sInstance;
	}

	InputManager* InputManager::GetInstance()
	{
		return sInstance;
	}

	void InputManager::DeleteInstance()
	{
		if (sInstance != nullptr)
		{
			delete(sInstance);
		}
	}


	InputManager::~InputManager()
	{
		if (sInstance != nullptr)
		{
			delete(sInstance);
		}
	}

	void InputManager::Init()
	{

		
		mControllerInput[0].mButtonPressed.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[0].mButtonPressed.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));

		mControllerInput[0].mButtonHeld.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[0].mButtonHeld.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));

		mControllerInput[0].mButtonHeld.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[0].mButtonHeld.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));

		mControllerInput[1].mButtonPressed.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[1].mButtonPressed.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));

		mControllerInput[1].mButtonHeld.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[1].mButtonHeld.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));

		mControllerInput[1].mButtonHeld.Insert(std::make_pair(XINPUT_GAMEPAD_A, false));
		mControllerInput[1].mButtonHeld.Insert(std::make_pair(static_cast<int>(Inputs::ANALOG_MOVEMENT), false));
	}

	void InputManager::CheckKeyPressed(std::int32_t key, GLFWwindow* window)
	{
		if (glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS)
		{
			mKeyPressed[key] = true;
			mIsMakingAnEvent = true;
		}
		else
		{
			if (mKeyPressed[key])
			{
				mIsMakingAnEvent = true;
				mKeyReleased[key] = true;
			}
			else
			{
				mKeyReleased[key] = false;
			}

			mKeyPressed[key] = false;
			mKeyHeld[key] = false;

		}
	}

	void InputManager::CheckKeyHeld()
	{
		for (auto& keys : mKeyPressed)
		{
			if (keys.second)
			{
				mKeyHeld[keys.first] = true;
				mIsMakingAnEvent = true;
			}
		}
	}

	void InputManager::ProcessKeys(GLFWwindow* window)
	{
		CheckKeyPressed(static_cast<int>(Inputs::W_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::A_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::S_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::D_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::CTRL_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::SPACE_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::LEFT_ARROW_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::UP_ARROW_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::RIGHT_ARROW_KEY), window);
		CheckKeyPressed(static_cast<int>(Inputs::DOWN_ARROW_KEY), window);
	}

	bool InputManager::IsKeyPressed(Inputs key)
	{
		return mKeyPressed[static_cast<int>(key)];
	}

	bool InputManager::IsKeyHeld(Inputs key)
	{
		return mKeyHeld[static_cast<int>(key)];
	}

	bool InputManager::IsKeyReleased(Inputs key)
	{
		return mKeyReleased[static_cast<int>(key)];
	}

	void InputManager::ClearKeyProcesses()
	{
		for (auto& keys : mKeyPressed)
		{
			keys.second = false;
		}
		for (auto& keys : mKeyHeld)
		{
			keys.second = false;
		}
		for (auto& keys : mKeyReleased)
		{
			keys.second = false;
		}
	}

	bool InputManager::IsButtonPressed(Inputs key, std::int32_t whichController)
	{
		return mControllerInput[whichController].mButtonPressed[static_cast<std::int32_t>(key)];
	}

	bool InputManager::IsButtonHeld(Inputs key, std::int32_t whichController)
	{
		return  mControllerInput[whichController].mButtonHeld[static_cast<std::int32_t>(key)];
	}

	bool InputManager::IsButtonReleased(Inputs key, std::int32_t whichController)
	{
		return mControllerInput[whichController].mButtoneReleased[static_cast<std::int32_t>(key)];
	}

	void InputManager::CheckButtonPressed(std::int32_t key, std::int32_t whichController)
	{
		if ((controllerState.Gamepad.wButtons & key) != 0)
		{
			mControllerInput[whichController].mButtonPressed[key] = true;
			mIsMakingAnEvent = true;
		}
			
		else
		{
			if (mControllerInput[whichController].mButtonPressed[key])
			{
				mIsMakingAnEvent = true;
				mControllerInput[whichController].mButtoneReleased[key] = true;
			}
			else
			{
				mControllerInput[whichController].mButtoneReleased[key] = false;
			}
				
			mControllerInput[whichController].mButtonPressed[key] = false;
			mControllerInput[whichController].mButtonHeld[key] = false;
		}
	}

	void InputManager::CheckButtonHeld()
	{
		for (std::int32_t i = 0; i < 2; ++i)
		{
			for (auto& keys : mControllerInput[i].mButtonPressed)
			{
				if (keys.second)
				{
					mControllerInput[i].mButtonHeld[keys.first] = true;
					mIsMakingAnEvent = true;
				}
			}
		}
	}

	bool InputManager::IsAnalogMoved(std::int32_t whichController)
	{
		bool analogMoved = mControllerInput[whichController].mButtonPressed[static_cast<std::int32_t>(Inputs::ANALOG_MOVEMENT)];

		if (analogMoved)
			return analogMoved;

		return mControllerInput[whichController].mButtonHeld[static_cast<std::int32_t>(Inputs::ANALOG_MOVEMENT)];
	}




	void InputManager::ProcessControllers()
	{
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		for (std::int32_t i = 0; i < 2; ++i)
		{
			if (XInputGetState(i, &controllerState) == ERROR_SUCCESS)
			{
				CheckButtonPressed(XINPUT_GAMEPAD_A, i);
				CheckButtonPressed(XINPUT_GAMEPAD_B, i);
				CheckButtonPressed(XINPUT_GAMEPAD_BACK, i);
				CheckButtonPressed(XINPUT_GAMEPAD_START, i);
				CheckButtonPressed(XINPUT_GAMEPAD_Y, i);
				CheckButtonPressed(XINPUT_GAMEPAD_X, i);

				float LX = controllerState.Gamepad.sThumbLX;
				float LY = controllerState.Gamepad.sThumbLY;

				//determine how far the controller is pushed
				float magnitude = sqrt(LX*LX + LY * LY);

				//determine the direction the controller is pushed
				float normalizedLX = LX / magnitude;
				float normalizedLY = LY / magnitude;

				float normalizedMagnitude = 0;

				//check if the controller is outside a circular dead zone
				if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					//clip the magnitude at its expected maximum value
					if (magnitude > 32767) magnitude = 32767;

					//adjust magnitude relative to the end of the dead zone
					magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

					//optionally normalize the magnitude with respect to its expected range
					//giving a magnitude value of 0.0 to 1.0
					normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

					mNormalizedLX[i] = normalizedLX;
					mNormalizedLY[i] = normalizedLY;

					mIsMakingAnEvent = true;

					mControllerInput[i].mButtonPressed[static_cast<std::int32_t>(Inputs::ANALOG_MOVEMENT)] = true;
					mIsMakingAnEvent = true;
				}
				else //if the controller is in the deadzone zero out the magnitude
				{
					magnitude = 0.0;
					normalizedMagnitude = 0.0;
					mControllerInput[i].mButtonPressed[static_cast<std::int32_t>(Inputs::ANALOG_MOVEMENT)] = false;
					mControllerInput[i].mButtonHeld[static_cast<std::int32_t>(Inputs::ANALOG_MOVEMENT)] = false;
				}

			}
		}
	}

	void InputManager::ClearControllerProcesses()
	{
		for (std::int32_t i = 0; i < 2; ++i)
		{
			for (auto& keys : mControllerInput[i].mButtonPressed)
			{
				keys.second = false;
			}
			for (auto& keys : mControllerInput[i].mButtonHeld)
			{
				keys.second = false;
			}
			for (auto& keys : mControllerInput[i].mButtoneReleased)
			{
				keys.second = false;
			}
		}
		
	}

	void InputManager::EnqueueEvent()
	{
		if (mIsMakingAnEvent)
		{
			std::shared_ptr<Event<InputManager*>> eventMessage = std::make_shared<Event<InputManager*>>(std::move(this));
			mEventQueue->EnqueueEvent(eventMessage, *mWorld->GetWorldState().GameTime);

			mIsMakingAnEvent = false;
		}
	}

	void InputManager::SetWorld(World& world)
	{
		mWorld = &world;
	}

	World& InputManager::GetWorld()
	{
		assert(mWorld != nullptr);
		return *mWorld;
	}

	void InputManager::SetEventQueue(EventQueue& eventQueue)
	{
		mEventQueue = &eventQueue;
	}

	EventQueue& InputManager::GetEventQueue()
	{
		assert(mEventQueue != nullptr);
		return *mEventQueue;
	}

	float InputManager::GetHorizontalAxis(std::int32_t whichController)
	{
		return mNormalizedLX[whichController];
	}

	float InputManager::GetVerticalAxis(std::int32_t whichController)
	{
		return mNormalizedLY[whichController];
	}
}


