#pragma once
#include "pch.h"
#include "OpenGLRenderEngine.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if defined(DEBUG) || defined(_DEBUG)
//We only need exception in debug mode.
#include <exception>
#include <iostream>
#endif

const char * OpenGLRenderEngine::VertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 mPos;\n"
"layout (location = 1) in vec2 mTexCoor;\n"
"out vec2 TexCoor;\n"
"uniform mat4 Projection;\n"
"uniform mat4 Model;\n"
"void main()\n"
"{\n"
"   gl_Position = Projection * Model * vec4(mPos.x, mPos.y, 0.0, 1.0);\n"
"	TexCoor = mTexCoor;\n"
"}\0";

const char * OpenGLRenderEngine::FragmentShaderSource = "#version 330 core\n"
"in vec2 TexCoor;\n"
"out vec4 FragmentColor;\n"
"uniform sampler2D CurrentTexture;\n"
"void main()\n"
"{\n"
"   FragmentColor = texture(CurrentTexture, TexCoor);\n"
"}\n\0";

const float SpaceBetweenDigits = 0.0f;

//If the coordinate system is whack, change this thing V
glm::mat4 OpenGLRenderEngine::Projection = glm::ortho(0.0f, float(OpenGLRenderEngine::FieldWidth), float(OpenGLRenderEngine::FieldHeight), 0.0f, -1.0f, 1.0f);

FieaGameEngine::Vector<GLuint> OpenGLRenderEngine::TextureIndices;

GLuint OpenGLRenderEngine::ShaderProgramId = 0;
GLuint OpenGLRenderEngine::StationaryVertexBuffer = 0;
GLuint OpenGLRenderEngine::ElementBuffer = 0;
GLuint OpenGLRenderEngine::VertexArrayObject = 0;
GLuint OpenGLRenderEngine::ExampleTextureId = 0;
bool OpenGLRenderEngine::InitRan = false;


void OpenGLRenderEngine::RenderLoadScreen()
{
	if (!InitRan)
	{
		//Enable the alpha channel.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glGenBuffers(1, &StationaryVertexBuffer);
		glGenBuffers(1, &ElementBuffer);

		GLuint VertexShaderId;
		VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderId, 1, &VertexShaderSource, NULL);
		glCompileShader(VertexShaderId);

		GLuint FragmentShaderId;
		FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderId, 1, &FragmentShaderSource, NULL);
		glCompileShader(FragmentShaderId);

#if defined(DEBUG) || defined(_DEBUG)

		int success;
		char InfoLog[512];
		glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(VertexShaderId, 512, NULL, InfoLog);
			throw std::exception(InfoLog);
		}

		glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(FragmentShaderId, 512, NULL, InfoLog);
			throw std::exception(InfoLog);
		}

#endif

		//Create the Shader program.
		ShaderProgramId = glCreateProgram();
		glAttachShader(ShaderProgramId, VertexShaderId);
		glAttachShader(ShaderProgramId, FragmentShaderId);
		glLinkProgram(ShaderProgramId);

#if defined(DEBUG) || defined(_DEBUG)

		glGetShaderiv(ShaderProgramId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(ShaderProgramId, 512, NULL, InfoLog);
			throw std::exception(InfoLog);
		}

#endif

		glGenVertexArrays(1, &VertexArrayObject);
		glBindVertexArray(VertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, StationaryVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glUseProgram(ShaderProgramId);
		glDeleteShader(VertexShaderId);
		glDeleteShader(FragmentShaderId);
		
		//Load loadscreen image.

		TextureIndices.Resize(1);
		GLuint& LoadScreenLocation = TextureIndices.At(0);
		//Load a texture.
		glGenTextures(1, &LoadScreenLocation);
		glBindTexture(GL_TEXTURE_2D, LoadScreenLocation);

		//Set filter parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		int width;
		int height;
		int nrChannels;
		unsigned char *data = stbi_load("content/Images/UI/LoadScreen/LoadScreen.png", &width, &height, &nrChannels, 0);
		data;
		
#if defined(DEBUG) || defined(_DEBUG)
		if (!data)
		{
			throw std::exception();
		}
#endif
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glUniform1i(glGetUniformLocation(ShaderProgramId, "CurrentTexture"), 0);
		glUniformMatrix4fv(glGetUniformLocation(ShaderProgramId, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));
		
		RenderStatic(FieaGameEngine::SpriteType(0), glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
	}
}

void OpenGLRenderEngine::InitRenderer()
{
	if (!InitRan)
	{
		FieaGameEngine::Vector<std::string> FileNames = 
		{"content/Images/Animals/Border_Collier_Blue.png",
			"content/Images/Animals/Border_Collier_Red.png", 
			"content/Images/Animals/Sheep_topdown_430p_x_430p.png",
			"content/Images/Animals/GOLD_SheepFINAL_419x299.png",
			"content/Images/Animals/Wolf_Undercover_419x299.png",
			"content/Images/Field/FIELD.png",
			"content/Images/Field/Environment.png",
			"content/Images/Field/GoalLeft.png",
			"content/Images/Field/GoalRight.png",
			"content/Images/Field/FieldBuildings/BuildingLEFT.png",
			"content/Images/Field/FieldBuildings/BuildingRight.png",
			"content/Images/Field/FieldBuildings/BuildingLeftShort.png",
			"content/Images/Field/FieldBuildings/BuildingRightShort.png",
			"content/Images/Field/FieldBuildings/FCBAAH.png",
			"content/Images/Field/FieldBuildings/WoolUnited.png",
			"content/Images/Field/BottomStands/BottomStand.png",
			"content/Images/Field/BottomStands/BottomCrowd.png",
			"content/Images/Field/BottomStands/BottomSigns.png",
			"content/Images/Field/BottomStands/BottomPaddock.png",
			"content/Images/Field/BottomStands/BottomPaddockLogo.png",
			"content/Images/Field/TopStands/TopStand.png",
			"content/Images/Field/TopStands/TopCrowd.png",
			"content/Images/Field/TopStands/TopSigns.png",
			"content/Images/Field/TopStands/TopPaddock.png",
			"content/Images/Field/TopStands/TopPaddockLogo.png",
			"content/Images/UI/StartScreen/BackPlate.png",
			"content/Images/UI/StartScreen/BlurredBG_StartScreen.png",
			"content/Images/UI/StartScreen/Frame_001.png",
			"content/Images/UI/StartScreen/MiddleScene.png",
			"content/Images/UI/StartScreen/Start_StartScreen.png",
			"content/Images/UI/StartScreen/StartScreenTitle.png",
			"content/Images/UI/InstructionScreen/BackPlate_Instruction.png",
			"content/Images/UI/InstructionScreen/BlurredBG.png",
			"content/Images/UI/InstructionScreen/OuterFrame.png",
			"content/Images/UI/InstructionScreen/Controller.png",
			"content/Images/UI/InstructionScreen/GetAsManySheep.png",
			"content/Images/UI/InstructionScreen/PressA.png",
			"content/Images/UI/InstructionScreen/MoveWithLeftStick.png",
			"content/Images/UI/InstructionScreen/Objective.png",
			"content/Images/UI/InstructionScreen/PressStartTOContinue.png",
			"content/Images/UI/EndScreen/BackPlate.png",
			"content/Images/UI/EndScreen/Quit_startScreen.png",
			"content/Images/UI/EndScreen/ItsATie.png",
			"content/Images/UI/EndScreen/BlueWins.png",
			"content/Images/UI/EndScreen/RedWins.png",
			"content/Images/UI/Numbers/0.png",
			"content/Images/UI/Numbers/1.png",
			"content/Images/UI/Numbers/2.png",
			"content/Images/UI/Numbers/3.png",
			"content/Images/UI/Numbers/4.png",
			"content/Images/UI/Numbers/5.png",
			"content/Images/UI/Numbers/6.png",
			"content/Images/UI/Numbers/7.png",
			"content/Images/UI/Numbers/8.png",
			"content/Images/UI/Numbers/9.png",
		};

		TextureIndices.Resize(FileNames.Size());

		for (size_t i = 0; i < FileNames.Size(); ++i)
		{
			LoadImageIntoSprite(FieaGameEngine::SpriteType(i), FileNames.At(i));
		}

		InitRan = true;
	}
}

//RenderBackground
void OpenGLRenderEngine::RenderGameFieldBackground()
{
	switch (FieaGameEngine::MenuManager::GetGameState())
	{
	case (FieaGameEngine::MenuManager::GameState::InGame):
		RenderStatic(FieaGameEngine::SpriteType::Field, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::Environment, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		break;

	case (FieaGameEngine::MenuManager::GameState::SplashScreen):
		RenderStatic(FieaGameEngine::SpriteType::StartBlurredBG, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartFrame, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartBackplate, glm::vec2(FieldWidth / 2, FieldHeight * 0.9f), glm::vec2(FieldWidth / 2.2f, FieldHeight / 8), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartScene, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartTitle, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartStart, glm::vec2(FieldWidth / 2, FieldHeight * 0.9f), glm::vec2(FieldWidth / 2.2f, FieldHeight/8), 0.0f);
		break;

	case (FieaGameEngine::MenuManager::GameState::EndScreen):
		RenderStatic(FieaGameEngine::SpriteType::StartBlurredBG, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::EndScreenBackPlate, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth / 3.1f, FieldHeight / 3.5f), 0.0f);
		break;

	case (FieaGameEngine::MenuManager::GameState::InstructionScreen):
		RenderStatic(FieaGameEngine::SpriteType::InstructionBlurredBG, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::InstructionFrame, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::Controller, glm::vec2(FieldWidth / 2, FieldHeight /2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::StartBackplate, glm::vec2(FieldWidth / 2, FieldHeight * 0.9f), glm::vec2(FieldWidth / 1.3f, FieldHeight / 7.5f), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::GetSheepText, glm::vec2(FieldWidth * 0.6f, FieldHeight * 0.9f), glm::vec2(FieldWidth / 2.2f, FieldHeight / 8), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::BarkText, glm::vec2(FieldWidth * 0.85f, FieldHeight * 0.5f), glm::vec2(FieldWidth / 3.5f, FieldHeight / 4), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::MoveText, glm::vec2(FieldWidth * 0.15f, FieldHeight * 0.5f), glm::vec2(FieldWidth / 3.5f, FieldHeight / 4), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::ObjectiveText, glm::vec2(FieldWidth * 0.28f, FieldHeight * 0.9f), glm::vec2(FieldWidth / 4.4f, FieldHeight / 8), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::PressStartText, glm::vec2(FieldWidth / 2, FieldHeight * 0.65f), glm::vec2(FieldWidth / 2.2f, FieldHeight / 8), 0.0f);
		break;
	default:
		break;
	}
}

void OpenGLRenderEngine::RenderGameFieldObjects()
{
	switch (FieaGameEngine::MenuManager::GetGameState())
	{
	case (FieaGameEngine::MenuManager::GameState::InGame):
		//goals
		RenderStatic(FieaGameEngine::SpriteType::LeftGoal, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::RightGoal, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);

		//buildings
		RenderStatic(FieaGameEngine::SpriteType::LeftBuilding, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::RightBuilding, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::ShortLeftBuilding, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::ShortRightBuilding, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::LeftText, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::RightText, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);

		//bottom stands
		RenderStatic(FieaGameEngine::SpriteType::BottomStands, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::BottomSigns, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::BottomCrowd, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::BottomPaddock, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::BottomPaddockSigns, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);

		//top stands
		RenderStatic(FieaGameEngine::SpriteType::TopStands, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::TopSigns, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::TopCrowd, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::TopPaddock, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		RenderStatic(FieaGameEngine::SpriteType::TopPaddockSigns, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth, FieldHeight), 0.0f);
		
		//Scores and timer
		RenderNumber(FieaGameEngine::MenuManager::RedPlayerScore, glm::vec2(FieldWidth / 24, FieldHeight / 6), glm::vec2(FieldWidth * 0.03f, FieldHeight * 0.05f)); 
		RenderNumber(FieaGameEngine::MenuManager::BluePlayerScore, glm::vec2(FieldWidth * 0.925f, FieldHeight / 6), glm::vec2(FieldWidth * 0.03f, FieldHeight * 0.05f));
		RenderTime(FieaGameEngine::MenuManager::RemainingSeconds, glm::vec2(FieldWidth * 0.4f, FieldHeight / 9), glm::vec2(FieldWidth * 0.06f, FieldHeight * 0.1f), 0.2f);
		break;

	case (FieaGameEngine::MenuManager::GameState::EndScreen):
		//Compare which score is higher and correctly display who won.
		if (FieaGameEngine::MenuManager::RedPlayerScore > FieaGameEngine::MenuManager::BluePlayerScore)
		{
			RenderStatic(FieaGameEngine::SpriteType::RedWins, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth / 3.5f, FieldHeight / 4), 0.0f);
		}
		else if (FieaGameEngine::MenuManager::RedPlayerScore < FieaGameEngine::MenuManager::BluePlayerScore)
		{
			RenderStatic(FieaGameEngine::SpriteType::BlueWins, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth / 3.5f, FieldHeight / 4), 0.0f);
		}
		else
		{
			RenderStatic(FieaGameEngine::SpriteType::Tie, glm::vec2(FieldWidth / 2, FieldHeight / 2), glm::vec2(FieldWidth / 3.5f, FieldHeight / 4), 0.0f);
		}
		break;

	case (FieaGameEngine::MenuManager::GameState::InstructionScreen):
		//Show dogs when player is ready.
		if (FieaGameEngine::MenuManager::Player1Ready)
		{
			RenderStatic(FieaGameEngine::SpriteType::RedDog, glm::vec2(FieldWidth * 0.2f, FieldHeight * 0.65f), glm::vec2(FieldWidth / 8, FieldHeight / 8), 180.0f);
		}

		if (FieaGameEngine::MenuManager::Player2Ready)
		{
			RenderStatic(FieaGameEngine::SpriteType::BlueDog, glm::vec2(FieldWidth * 0.8f, FieldHeight * 0.65f), glm::vec2(FieldWidth / 8, FieldHeight / 8), 0.0f);
		}
		break;
	case (FieaGameEngine::MenuManager::GameState::SplashScreen):
	default:
		break;
	}
}

void OpenGLRenderEngine::RenderGameObjects(const FieaGameEngine::Sector & SectorOfDrawableThings)
{
	if (FieaGameEngine::MenuManager::GetGameState() == FieaGameEngine::MenuManager::GameState::InGame)
	{
		const FieaGameEngine::Datum& Entities = SectorOfDrawableThings.Entities();

		//Loop through the Datum, ensuring that they're all GameObjects.
		for (int i = static_cast<int>(Entities.Size()) - 1; i >= 0; --i)
		{
			assert(Entities.Get<FieaGameEngine::Scope*>(static_cast<size_t>(i))->Is(FieaGameEngine::GameObject::TypeIdClass()));
			FieaGameEngine::GameObject* ObjectToDraw = static_cast<FieaGameEngine::GameObject*>(Entities.Get<FieaGameEngine::Scope*>(static_cast<size_t>(i)));
			//Get the enum from Object to draw.
			FieaGameEngine::SpriteType SpriteToDraw = ObjectToDraw->GetSpriteType();

			if (SpriteToDraw != FieaGameEngine::SpriteType::None)
			{
				//Get the position, size, and rotation.
				FieaGameEngine::Transform& ObjectsTransform = ObjectToDraw->Transform();
				RenderStream(SpriteToDraw, ObjectsTransform.GetPosition(), ObjectsTransform.GetScale(), ObjectsTransform.GetRotation());
			}
		}
	}
}

void OpenGLRenderEngine::RenderNumber(size_t Value, glm::vec2 Position, glm::vec2 Size)
{
	std::string NumberString = std::to_string(Value);
	if (NumberString.length() < 2)
	{
		NumberString.insert(0, "0");
	}

	glm::vec2 Pos = Position;

	for (auto& Character : NumberString)
	{
		FieaGameEngine::SpriteType SpriteToDraw = FieaGameEngine::SpriteType(int(FieaGameEngine::SpriteType::Num0) + (Character - '0'));
		RenderStatic(SpriteToDraw, Pos, Size, 0.0f);
		Pos.x += (Size.x * (1 + SpaceBetweenDigits));
	}
}

void OpenGLRenderEngine::RenderTime(size_t Seconds, glm::vec2 Position, glm::vec2 Size, float SpaceBetweenNumbers)
{
	RenderNumber(Seconds / 60, Position, Size);
	RenderNumber(Seconds % 60, glm::vec2(Position.x + SpaceBetweenNumbers + (Size.x * 2), Position.y), Size);
}

void OpenGLRenderEngine::RenderStream(FieaGameEngine::SpriteType Sprite, glm::vec2 Position, glm::vec2 Size, float Rotation)
{
	//Use x and y, height and width to create vertices and indices of rect.
	float Vertices[] = {
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f
	};

	unsigned int Elements[] = {
		0,1,3,
		1,2,3
	};

	//I need to handle rotation and scale, but not skew.
	glm::mat4 Model(1.0f);

	//Translate.
	Model = glm::translate(Model, glm::vec3(Position, 0.0f));

	//Rotate.
	Model = glm::rotate(Model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	//Scale.
	Model = glm::scale(Model, glm::vec3(Size, 0.0f));
	
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramId, "Model"), 1, GL_FALSE, glm::value_ptr(Model));

	//Put data into buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STREAM_DRAW);
	
	//Set proper texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIndices.At(size_t(Sprite)));

	//draw thing.
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRenderEngine::RenderStatic(FieaGameEngine::SpriteType Sprite, glm::vec2 Position, glm::vec2 Size, float Rotation)
{
	//Use x and y, height and width to create vertices and indices of rect.
	float Vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f
	};

	unsigned int Elements[] = {
		0,1,3,
		1,2,3
	};

	//I need to handle rotation and scale, but not skew.
	glm::mat4 Model(1.0f);

	//Translate.
	Model = glm::translate(Model, glm::vec3(Position, 0.0f));

	//Rotate.
	Model = glm::rotate(Model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	//Scale.
	Model = glm::scale(Model, glm::vec3(Size, 0.0f));

	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramId, "Model"), 1, GL_FALSE, glm::value_ptr(Model));

	//Put data into buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW);

	//Set proper texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIndices.At(size_t(Sprite)));

	//draw thing.
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRenderEngine::LoadImageIntoSprite(FieaGameEngine::SpriteType SpriteType, const std::string & FilePath)
{
	GLuint& SpriteLocation = TextureIndices.At(size_t(SpriteType));
	//Load a texture.
	glGenTextures(1, &SpriteLocation);
	glBindTexture(GL_TEXTURE_2D, SpriteLocation);

	//Set filter parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width;
	int height;
	int nrChannels;
	unsigned char *data = stbi_load(FilePath.c_str(), &width, &height, &nrChannels, 0);

#if defined(DEBUG) || defined(_DEBUG)
	if (!data)
	{
		throw std::exception();
	}
#endif

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
