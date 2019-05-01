#include "pch.h"
#include "InputManager.h"

namespace FieaGameEngine
{
	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::CreateInstance()
	{
		assert(sInstance == nullptr);
		sInstance = new InputManager();
		return sInstance;
	}

	InputManager::~InputManager()
	{
		if (sInstance != nullptr)
		{
			delete(sInstance);
		}
	}



}


