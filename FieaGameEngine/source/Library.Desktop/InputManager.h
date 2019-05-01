#pragma once

#include <Windows.h>
#include <Xinput.h>

#include "HashMap.h"

//w,s,a,d, leftctr, arrow keys, right ctr, eneter
//left stick, a bark, start button,

namespace FieaGameEngine
{
	class InputManager
	{
	public:
		enum class Inputs { ANALOG_MOVEMENT, W_KEY = 87, A_KEY = 65, S_KEY = 83, D_KEY = 68, CTRL_KEY = 17, SPACE_KEY = 32, LEFT_ARROW_KEY = 37, UP_ARROW_KEY, RIGHT_ARROW_KEY, DOWN_ARROW_KEY };

		InputManager();
		~InputManager();

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
		InputManager* CreateInstance();

		/// <summary>
		/// Returns true if the key value was pressed
		/// </summary>
		/// <param name="key">
		/// Int value that represets a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was pressed
		/// </returns>
		bool IsKeyPressed(int key);

		/// <summary>
		/// Returns true if the key value was held
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was held
		/// </returns>
		bool IsKeyHeld(int key);

		/// <summary>
		/// Returns true if the key was realeased
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the key value was held
		/// </returns>
		bool IsKeyReleased(int key);

		/// <summary>
		/// Using xinput calls checks if the key value was pressed
		/// and initialize the map variable correctly
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value 
		/// </param>
		void CheckKeyPressed(int key);

		/// <summary>
		/// Iterates through the map variable and if a key is pressed then
		/// makes it turn to held
		/// </summary>
		void CheckKeyHeld();

		/// <summary>
		/// Returns true if the button value was pressed
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the button value was pressed
		/// </returns>
		bool IsButtonPressed(int key);

		/// <summary>
		/// Returns true if the button value was pressed
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the button was held
		/// </returns>
		bool IsButtonHeld(int key);

		/// <summary>
		/// Returns true if the button value was released
		/// </summary>
		/// <param name="key">
		/// Int value that represents a key value
		/// </param>
		/// <returns>
		/// Returns true if the button value was released
		/// </returns>
		bool IsButtonReleased(int key);

		/// <summary>
		/// Using xinput checks to see if the button was pressed
		/// and update the maping variable to it
		/// </summary>
		/// <param name="key">
		/// Int value that represents a button pressed
		/// </param>
		void CheckButtonPressed(int key);

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
		bool IsAnalogMoved();

		/// <summary>
		/// Using the xinput it checks to see what is being pressed and 
		/// passes that through to button pressed
		/// </summary>
		void ProcessKeys();

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

	private:

		static InputManager* sInstance;

		HashMap<int, bool> mKeyPressed;
		HashMap<int, bool> mKeyHeld;
		HashMap<int, bool> mKeyReleased;
		HashMap<int, bool> mButtonPressed;
		HashMap<int, bool> mButtonHeld;
		HashMap<int, bool> mButtoneReleased;
	};


}

