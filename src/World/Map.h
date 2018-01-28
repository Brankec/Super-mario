
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../Entities/Player.h"
#include "../Util/Camera.h"
#include "../World/Level.h"
#include "Tiles/BasicTiles.h"

#pragma once

class Map
{
public:
	Map();

public:
	void loadMap(Level& levelsPass);

	void loadTilesForeground();//for deocrations
	void drawForeGround(sf::RenderTarget& renderer);

	void loadTilesMain();//main player layer with all 4 collisions
	void drawMain(sf::RenderTarget& renderer);
	void CollisionMain(Player & player);

	void loadTilesBackground();//for decorations
	void drawBackGround(sf::RenderTarget& renderer);


	void setOriginCenter();
	sf::Vector2f Sprite_sheet_coordinates(int tileIndex);


public:
	Level* levels;
	int powOfN;
	int tileIndex = 0;
	int objectiveTileCoords = 0;
	sf::Texture tileTexture;
	sf::RectangleShape tile[5];  // 0) background, 1) background-main(only top has collision), 2) main(playerbase), 3) foreground 4) interactables
	sf::Vector2i tileSize;

	std::vector<std::vector<sf::Vector2f>> mapForeGround, mapBackGround, mapMain;
	std::vector<sf::Vector2f> tempMap;
	sf::Vector2i loadCounter;
	int amountOfTiles;

	//open the file containing the tile name and tile positions
	std::ifstream openfileForeground;
	std::ifstream openfileMain;
	std::ifstream openfileBackground;




	std::vector<BasicTiles> MTiles; //main layer
	std::vector<BasicTiles> BTiles; //background layer
};

