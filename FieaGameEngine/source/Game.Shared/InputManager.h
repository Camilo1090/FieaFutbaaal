#pragma once

#include <Windows.h>
#include <Xinput.h>

#include "HashMap.h"

#include "GLFW/glfw3.h"

//w,s,a,d, leftctr, arrow keys, right ctr, eneter
//left stick, a bark, start button,

namespace FieaGameEngine
{

	class World;
	class EventQueue;

	class InputManager
	{
	public:
		enum class Inputs {
			ANALOG_MOVEMENT, W_KEY = 87, A_KEY = 65, S_KEY = 83, D_KEY = 68, CTRL_KEY = 17, SPACE_KEY = 32, LEFT_ARROW_KEY = GLFW_KEY_LEFT,
			UP_ARROW_KEY = GLFW_KEY_UP, RIGHT_ARROW_KEY = GLFW_KEY_RIGHT, DOWN_ARROW_KEY = GLFW_KEY_DOWN, A_BUTTON = XINPUT_GAMEPAD_A, B_BUTTON = XINPUT_GAMEPAD_B, START_BUTTON = XINPUT_GAMEPAD_START,
			SELECT_BUTTON = XINPUT_GAMEPAD_BACK, X_BUTTON = XINPUT_GAMEPAD_X, Y_BUTTON = XINPUT_GAMEPAD_Y

		};

		~InputManager();

		void SetWorld(World& world);

		World& GetWorld();

		void SetEventQueue(EventQueue& eventQeueue);

		EventQueue& GetEventQueue();

		/// <summary>
		/// Initilize the mapping variables for controller and keypad inputs
		/// </summary>
		void Init();

		/// <summary>
		/// Creates a single instance of the class
		/// </summary>
		/// <returns>
		/// returns a pointer of the single instance of the input manager;
		/// </returns>
		static InputManager* CreateInstance();

		/// <summary>
		/// Obtain the singleton class
		/// </summary>
		/// <returns>
		/// Returns the single instance of the class
		/// </returns>
		static InputManager* GetInstance();

		/// <summary>
		/// Deletes the single instance of the input manager
		/// </summary>
		static void DeleteInstance();

		/// <summary>
		/// Returns true if the key value was pressed
		/// </summary>
		/// <param name="key">
		/// Int value that represets a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was pressed
		/// </returns>
		bool IsKeyPressed(Inputs key);

		/// <summary>
		/// Returns true if the key value was held
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was held
		/// </returns>
		bool IsKeyHeld(Inputs key);

		/// <summary>
		/// Returns true if the key was realeased
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was held
		/// </returns>
		bool IsKeyReleased(Inputs key);

		/// <summary>
		/// Iterates through the map variable and if a key is pressed then
		/// makes it turn to held
		/// </summary>
		void CheckKeyHeld();

		/// <summary>
		/// Returns true if the key was pressed for that controller
		/// </summary>
		/// <param name="key">
		/// Int value that represents the key
		/// </param>
		/// <param name="controller">
		/// Int value that represents which controller was pressed
		/// </param>
		/// <returns>
		/// Returns true if the button was pressed from that controller
		/// </returns>
		bool IsButtonPressed(Inputs key, std::int32_t controller);

		/// <summary>
		/// Returns true if the key was held for that controller
		/// </summary>
		/// <param name="key">
		/// Int value that represents the key
		/// </param>
		/// <param name="controller">
		/// Int value that represents which controller was pressed
		/// </param>
		/// <returns>
		/// Returns true if the button was held from that controller
		/// </returns>
		bool IsButtonHeld(Inputs key, std::int32_t whichController);

		/// <summary>
		/// Returns true if the key was released for that controller
		/// </summary>
		/// <param name="key">
		/// Int value that represents the key
		/// </param>
		/// <param name="controller">
		/// Int value that represents which controller was pressed
		/// </param>
		/// <returns>
		/// Returns true if the button was released from that controller
		/// </returns>
		bool IsButtonReleased(Inputs key, std::int32_t whichController);

		/// <summary>
		/// Using xinput checks to see if the button was pressed
		/// and update the maping variable to it
		/// </summary>
		/// <param name="key">
		/// Int value that represents a button pressed
		/// </param>
		void CheckButtonPressed(std::int32_t key, std::int32_t  whichKey);

		/// <summary>
		/// Iterates through the entire hash map for pressed button
		/// to update the hashmap for button held if the button was
		/// already pressed
		/// </summary>
		void CheckButtonHeld();

		/// <summary>
		/// Returns true if the anolog from the controller is moved
		/// </summary>
		/// <returns></returns>
		bool IsAnalogMoved(std::int32_t whichKey);

		/// <summary>
		/// Using the xinput it checks to see what is being pressed and
		/// passes that through to button pressed
		/// </summary>
		void ProcessKeys(GLFWwindow* window);

		/// <summary>
		/// Using the xinput it checks to see what is being pressed and
		/// passes that through to button pressed
		/// </summary>
		void ProcessControllers();

		/// <summary>
		/// Clear the mapping variable of all the key checks
		/// </summary>
		void ClearKeyProcesses();

		/// <summary>
		/// Clear the mapping variable of all the button checks
		/// </summary>
		void ClearControllerProcesses();

		void EnqueueEvent();

		/// <summary>
		/// Returns the normalized x for the analog input
		/// </summary>
		/// <returns>
		/// Returns the normalized x for the analog input
		/// </returns>
		float GetHorizontalAxis(std::int32_t whichController);

		/// <summary>
		/// Returns the normalized y for the anlaog input
		/// </summary>
		/// <param name="whichController">
		/// Integer value that represents which controller 
		/// </param>
		/// <returns>
		/// Returns the normalized y for the analog input
		/// </returns>
		float GetVerticalAxis(std::int32_t whichController);

		void UpdateInputManager(GLFWwindow* window);

	private:

		/// <summary>
		/// Using xinput calls checks if the key value was pressed
		/// and initialize the map variable correctly
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		void CheckKeyPressed(std::int32_t key, GLFWwindow* window);

		InputManager() = default;

		static InputManager* sInstance;

		static HashMap<std::int32_t, bool> mKeyPressed;
		static HashMap<std::int32_t, bool> mKeyHeld;
		static HashMap<std::int32_t, bool> mKeyReleased;

		struct ControllerInput final
		{
			HashMap<std::int32_t, bool> mButtonPressed;
			HashMap<std::int32_t, bool> mButtonHeld;
			HashMap<std::int32_t, bool> mButtoneReleased;
		};

		ControllerInput mControllerInput[std::int32_t(2)];

		bool mIsMakingAnEvent = false; 

		World* mWorld = nullptr;

		EventQueue* mEventQueue = nullptr;

		XINPUT_STATE controllerState;

		//determine the direction the controller is pushed
		float mNormalizedLX[std::int32_t(2)];
		float mNormalizedLY[std::int32_t(2)];

	};


}

