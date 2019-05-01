#pragma once

#include "HashMap.h"

namespace FieaGameEngine
{
	enum class SpriteType
	{
#pragma region InGame
		BlueDog,
		RedDog,
		Sheep,
		GoldSheep,
		WolfSheep,
		Field,
		Environment,
		LeftGoal,
		RightGoal,
		LeftBuilding,
		RightBuilding,
		ShortLeftBuilding,
		ShortRightBuilding,
		LeftText,
		RightText,
		BottomStands,
		BottomCrowd,
		BottomSigns,
		BottomPaddock,
		BottomPaddockSigns,
		TopStands,
		TopCrowd,
		TopSigns,
		TopPaddock,
		TopPaddockSigns,
#pragma endregion
#pragma region StartScreen
		StartBackplate,
		StartBlurredBG,
		StartFrame,
		StartScene,
		StartStart,
		StartTitle,
#pragma endregion
#pragma region InstructionScreen
		InstructionBackplate,
		InstructionBlurredBG,
		InstructionFrame,
		Controller,
		GetSheepText,
		BarkText,
		MoveText,
		ObjectiveText,
		PressStartText,
#pragma endregion
#pragma region EndScreen
		EndScreenBackPlate,
		Quit,
		Tie,
		BlueWins,
		RedWins,
#pragma endregion
#pragma region
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
#pragma endregion
		None
	};

	static const HashMap<std::string, SpriteType> SpriteTypes = {
		{ "BlueDog", SpriteType::BlueDog },
		{ "RedDog", SpriteType::RedDog },
		{ "Sheep", SpriteType::Sheep },
		{ "GoldSheep", SpriteType::GoldSheep },
		{ "WolfSheep", SpriteType::WolfSheep },
		{"None", SpriteType::None}
	};
}