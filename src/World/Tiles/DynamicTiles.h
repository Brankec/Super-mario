
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../../Entities/Player.h"
#include "../../Util/Camera.h"
#include "../../World/Level.h"
#include "TileCollision.h"
#include "Tile.h"

#pragma once

class DynamicTiles 
	: public Tile
	, public TileCollision
{
public:
	DynamicTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex);

	void setTileTexture(sf::Vector2f tileIndex);
	
	void setTilePosition(sf::Vector2f tPosition);

	void ToggleCollision(bool set);
	void ToggleDestructable(bool set);

	void Collision(Player &entity);

	void drawTile(sf::RenderTarget& renderer);

	sf::RectangleShape getTile();

	bool destroy = false;
};
