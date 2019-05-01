#pragma once
#include "vector.h"
#include "SpriteTypeEnum.h"
#include "Sector.h"
#include "GameObject.h"
#include "MenuManager.h"

class OpenGLRenderEngine
{
public:
	/// <summary>
	/// Called BEFORE INITRENDERER. Displays a load screen.
	/// </summary>
	static void RenderLoadScreen();
	
	/// <summary>
	/// Set up the renderer.
	/// </summary>
	static void InitRenderer();
	
	/// <summary>
	/// Draw all background objects.
	/// </summary>
	static void RenderGameFieldBackground();

	/// <summary>
	/// Draw all Foreground objects.
	/// </summary>
	static void RenderGameFieldObjects();

	/// <summary>
	/// Draws all the objects in a Sector with only GameObjects in it.
	/// </summary>
	/// <param name="SectorOfDrawableThings">Sector full of drawable GameObjects</param>
	static void RenderGameObjects(const FieaGameEngine::Sector& SectorOfDrawableThings);

	/// <summary>
	/// Prints a number.
	/// </summary>
	/// <param name="Value">Number to render</param>
	/// <param name="Position">Starting position of first digit.</param>
	/// <param name="Size">Size per digit</param>
	static void RenderNumber(size_t Value, glm::vec2 Position, glm::vec2 Size);

	/// <summary>
	/// Prints a time in seconds
	/// </summary>
	/// <param name="Value">Number of seconds to render</param>
	/// <param name="Position">Starting position of the minutes digit.</param>
	/// <param name="Size">Size per digit</param>
	static void RenderTime(size_t Seconds, glm::vec2 Position, glm::vec2 Size, float SpaceBetweenNumbers);
private:

	static const size_t FieldHeight = 900;
	static const size_t FieldWidth = 1800;

	/// <summary>
/// Renders an image with stream draw, which is used for things that move a lot.
/// </summary>
/// <param name="Sprite">Enum of the Sprite to draw.</param>
/// <param name="Position">Vec2 of location to draw the sprite.</param>
/// <param name="Size">Vec2 of X and Y width of thing to draw.</param>
/// <param name="Rotation">Rotation of object. Clockwise, 0 is right.</param>
	static void RenderStream(FieaGameEngine::SpriteType Sprite, glm::vec2 Position, glm::vec2 Size, float Rotation);

	/// <summary>
	/// Renders an image with stream draw, which is used for things that move a lot.
	/// </summary>
	/// <param name="Sprite">Enum of the Sprite to draw.</param>
	/// <param name="Position">Vec2 of location to draw the sprite.</param>
	/// <param name="Size">Vec2 of X and Y width of thing to draw.</param>
	/// <param name="Rotation">Rotation of object. Clockwise, 0 is left.</param>
	static void RenderStatic(FieaGameEngine::SpriteType Sprite, glm::vec2 Position, glm::vec2 Size, float Rotation);

	static void LoadImageIntoSprite(FieaGameEngine::SpriteType SpriteLocation, const std::string& FilePath);

	//Ids of various things.
	static GLuint StationaryVertexBuffer;
	static GLuint ElementBuffer;
	static GLuint VertexArrayObject;
	static GLuint ShaderProgramId;
	static GLuint ExampleTextureId;

	//Array of SpriteIds.
	static FieaGameEngine::Vector<GLuint> TextureIndices;

	//Projection matrix
	static glm::mat4 Projection;

	//Sources for shaders and vertices.
	static const char * VertexShaderSource;
	static const char * FragmentShaderSource;

	//Prevent double initialization.
	static bool InitRan;
};

