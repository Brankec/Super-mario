
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../Entities/Player.h"
#include "../Util/Camera.h"
#include "../World/Level.h"
#include "Tiles/DynamicTiles.h"
#include "Tiles/StaticTiles.h"
#include "Tiles/BackgroundTiles.h"

#pragma once

class Map
{
public:
	Map();

public:
	void loadMap(Level& levelsPass);

	void loadTilesForeground();//for deocrations
	void drawForeGround(sf::RenderTarget& renderer);

	void loadTilesStatic();//main player layer with all 4 collisions
	void drawStatic(sf::RenderTarget& renderer);
	void loadTilesDynamic();
	void drawDynamic(sf::RenderTarget& renderer);
	void Collision(Player & player);

	void loadTilesBackground();//for decorations
	void drawBackGround(sf::RenderTarget& renderer);

	sf::Vector2f Sprite_sheet_coordinates(int tileIndex);

public:
	Level* levels;
	int powOfN;
	int tileIndex = 0;
	int objectiveTileCoords = 0;
	sf::Texture tileTexture;
	sf::Vector2i tileSize;

	std::vector<std::vector<sf::Vector2f>> mapForeGround, mapBackGround, mapDynamic, mapStatic;
	std::vector<sf::Vector2f> tempMap;
	sf::Vector2i loadCounter;
	int amountOfTiles;

	//open the file containing the tile name and tile positions
	std::ifstream openfileForeground;
	std::ifstream openfileDynamic;
	std::ifstream openfileStatic;
	std::ifstream openfileBackground;



	std::vector<BackgroundTiles> FTiles; //foreground layer
	std::vector<DynamicTiles> DTiles; //static tiles
	std::vector<StaticTiles> STiles; //dynamic tiles
	std::vector<BackgroundTiles> BTiles; //background layer
};

