#pragma once
#include <SFML/Graphics.hpp>

class Level
{
public:
	Level()
	{
		Level_1();
	}

	void Level_1()
	{
		BackGround = "Level 1/Level1_background";
		Static = "Level 1/Level1_static";
		Dynamic = "Level 1/Level1_dynamic";
		ForeGround = "Level 1/Level1_foreground";

		gridSize = 6;//size of each tile(not the texture)
		amountOfTilesX = 33;
		tileSize = { 16, 16 };
		objectiveTileCoords = 736;
		whichLevel = 1;

		spawnPoint = { 30, 100 };
	}

	void Level_2()
	{
		BackGround = "Level 1/Level1_background";
		Static = "Level 1/Level1_static";
		Dynamic = "Level 1/Level1_dynamic";
		ForeGround = "Level 1/Level1_foreground";

		gridSize = 6;
		amountOfTilesX = 9;
		tileSize = { 32, 32 };
		objectiveTileCoords = 256;
		whichLevel = 2;

		spawnPoint = { 30, 100 };
	}

	void Level_3()
	{

	}

	std::string BackGround, BackGroundMain, Static, Dynamic, ForeGround, Interactable;
	int gridSize, amountOfTilesX;
	sf::Vector2i tileSize;
	int objectiveTileCoords;
	int whichLevel = 0;
	sf::Vector2f spawnPoint;
};