
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../../Entities/Player.h"
#include "../../Util/Camera.h"
#include "../../World/Level.h"
#include "Tile.h"

#pragma once

class BasicTiles : public Tile
{
public:
	BasicTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex);

	void setTileTexture(sf::Vector2f tileIndex);
	
	void setTilePosition(sf::Vector2f tPosition);

	sf::RectangleShape getTile();
};

