#include "pch.h"
#include "World.h"
#include "OpenGLRenderEngine.h"
#include "MenuManager.h"

#include "GLFW/glfw3.h"

#include "EventQueue.h"
#include "InputManager.h"
#include "JsonTableParseHelper.h"
#include "TypeManager.h"
#include "ActionPlaySound.h"
#include "ActionAddForce.h"
#include "ActionMovementDrag.h"
#include "ActionPauseSound.h"
#include "ActionResumeSound.h"
#include "ActionStopSound.h"
#include "ActionTurn.h"
#include "ActionListIf.h"
#include "ActionIncrement.h"
#include "ActionCreateAction.h"
#include "ActionDeleteAction.h"
#include "ActionUpdatePosition.h"
#include "ActionAddForce.h"
#include "ActionEvent.h"
#include "ActionMovementDrag.h"
#include "ActionUpdateTargetRotation.h"
#include "ActionSpawnSheep.h"
#include "ActionTurn.h"
#include "ActionUpdatePosition.h"
#include "ActionUpdateTargetRotation.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Dog.h"
#include "GameObject.h"
#include "Pusher.h"
#include "ReactionCollision.h"
#include "ReactionCollisionForce.h"
#include "ReactionCollisionScore.h"
#include "ReactionInput.h"
#include "ReactionCollision.h"
#include "ReactionCollisionForce.h"
#include "ReactionCollisionScore.h"
#include "ReactionSheepPulse.h"
#include "ReactionSpawn.h"
#include "ScoreVolume.h"
#include "Sheep.h"
#include "Transform.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "ReactionCollisionForce.h"
#include "ReactionCollisionScore.h"
#include "ReactionInput.h"
#include "ReactionInputPlayer.h"
#include "SheepSpawner.h"
#include "ReactionSpawn.h"
#include "ActionSpawnSheep.h"
#include "AudioManager.h"
#include "CollisionManager.h"

using namespace FieaGameEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(instance);
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);
	UNREFERENCED_PARAMETER(showCommand);

	const glm::vec4 ForestGreen = glm::vec4(0.25f, 0.384f, 0.20f, 1.0f);

	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1800, 900, "Futbaaal", nullptr, nullptr);

	if (window == nullptr)
	{
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit() != 0)
	{
		return -1;
	}

	glViewport(0, 0, 1800, 900);

	OpenGLRenderEngine::RenderLoadScreen();
	glfwSwapBuffers(window);

	// seed rng
	std::srand(static_cast<unsigned int>(time(NULL)));

	REGISTER_TYPE(World);
	REGISTER_TYPE(Sector);
	REGISTER_TYPE(Entity);
	REGISTER_TYPE(Action);
	REGISTER_TYPE(ActionAddForce);
	REGISTER_TYPE(ActionMovementDrag);
	REGISTER_TYPE(ActionPauseSound);
	REGISTER_TYPE(ActionResumeSound);
	REGISTER_TYPE(ActionSpawnSheep);
	REGISTER_TYPE(ActionStopSound);
	REGISTER_TYPE(ActionTurn);
	REGISTER_TYPE(ActionUpdatePosition);
	REGISTER_TYPE(ActionList);
	REGISTER_TYPE(ActionListIf);
	REGISTER_TYPE(ActionIncrement);
	REGISTER_TYPE(ActionPlaySound);
	REGISTER_TYPE(ActionCreateAction);
	REGISTER_TYPE(ActionDeleteAction);
	REGISTER_TYPE(Reaction);
	REGISTER_TYPE(ActionUpdateTargetRotation);
	REGISTER_TYPE(BoxCollider);
	REGISTER_TYPE(CircleCollider);
	REGISTER_TYPE(Collider);
	REGISTER_TYPE(Dog);
	REGISTER_TYPE(GameObject);
	REGISTER_TYPE(Pusher);
	REGISTER_TYPE(ReactionCollision);
	REGISTER_TYPE(ReactionCollisionForce);
	REGISTER_TYPE(ReactionCollisionScore);
	REGISTER_TYPE(ReactionInput);
	REGISTER_TYPE(ReactionInputPlayer);
	REGISTER_TYPE(ReactionSheepPulse);
	REGISTER_TYPE(ReactionSpawn);
	REGISTER_TYPE(Sheep);
	REGISTER_TYPE(SheepSpawner);
	REGISTER_TYPE(Transform);
	REGISTER_TYPE(ScoreVolume);

	// Initilize the input here
	FieaGameEngine::InputManager* inputManager = FieaGameEngine::InputManager::CreateInstance();

	//build world and start timer
	std::shared_ptr<FieaGameEngine::GameTime> time = std::make_shared<FieaGameEngine::GameTime>();
	FieaGameEngine::World world(time);
	MenuManager::SetWorld(world);
	FieaGameEngine::CollisionManager::SetWorld(world);
	FieaGameEngine::GameClock clock;

	FieaGameEngine::EventQueue eventQueue;
	world.SetEventQueue(eventQueue);

	inputManager->SetEventQueue(eventQueue);
	inputManager->SetWorld(world);

	TableSharedData data(world);
	JsonParseMaster master(data);
	JsonTableParseHelper helper;
	master.AddHelper(helper);

	SectorFactory f1;
	EntityFactory EntityFactory;

	ActionAddForceFactory actionAddForceFactory;
	ActionMovementDragFactory actionMovementDragFactory;
	ActionPauseSoundFactory actionPauseMovementFactory;
	ActionPlaySoundFactory actionPlaySoundFactory;
	ActionResumeSoundFactory actionResumeSoundFactory;
	ActionSpawnSheepFactory actionSpawnSheepFactory;
	ActionStopSoundFactory actionStopSoundFactory;
	ActionTurnFactory actionTurnFactory;
	ActionUpdatePositionFactory actionUpdatePositionFactory;
	//ActionUpdateTargetRotationFactory actionUpdateTargetRotationFactory;
	BoxColliderFactory boxColliderFactory;
	CircleColliderFactory circleColliderFactory;
	//ColliderFactory colliderFactory;
	//CollisionFactory collisionFactory;
	//CollisionManagerFactory collisionManagerFactory;

	TransformFactory transFactory;
	SheepSpawnerFactory spawnFactory;
	SheepFactory sheepFactory;
	ScoreVolumeFactory scoreFactory;
	ReactionSpawnFactory reactSpawnFactory;
	ReactionSheepPulseFactory sheepPulseFactory;
	ReactionInputPlayerFactory inputPlayerFactory;
	ReactionInputFactory inputFactory;
	ReactionCollisionScoreFactory scoreCollisionFactory;
	ReactionCollisionForceFactory forceCollisionFactory;
	ReactionCollisionFactory collisionFactory;
	PusherFactory pusherFactory;
	GameObjectFactory gameObjectFactory;
	DogFactory dogFactory;
	
	master.Initialize();
	master.ParseFromFile("content/game.json");
	
	OpenGLRenderEngine::InitRenderer();
	FieaGameEngine::MenuManager::GetInstance();
	AudioManager::Init();;

	//world.Start();;

	AudioManager::PlayAduio(AudioManager::GetSample(AudioManager::TitleScreenMusic), false);

	while (!glfwWindowShouldClose(window))
	{
		inputManager->ProcessControllers();
		inputManager->ProcessKeys(window);
		inputManager->EnqueueEvent();
		//This is where you would push the event
		
		//update timer
		clock.UpdateGameTime(*time);
		
		//update world
		world.Update(world.GetWorldState());

		CollisionManager::getInstance()->Update();;
		//CollisionManager::getInstance()->Update();;
		//CollisionManager::getInstance()->Update();

		//Sheep hit with bark - accelerates sheep in vector opposite direction

		//Did sheep hit goal line

		//Update score

		//sheep pulse

		//input check

		//move/bark dog

		//update timer

		//Clear the field
		glClearBufferfv(GL_COLOR, 0, &ForestGreen[0]);
		
		//Render the background.
		OpenGLRenderEngine::RenderGameFieldBackground();
		
		//Render the gameobjects
		OpenGLRenderEngine::RenderGameObjects(static_cast<FieaGameEngine::Sector&>(world.Sectors()[0]));
		
		//Render the foreground.
		OpenGLRenderEngine::RenderGameFieldObjects();

		glfwSwapBuffers(window);
		glfwPollEvents();

		inputManager->CheckKeyHeld();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
