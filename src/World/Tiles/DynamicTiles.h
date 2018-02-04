
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
#include "../TileSound/BrickNudge.h"
#include "../TileSound/BrickDestroy.h"

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

	void CollisionPlayer(Player &entity);
	void CollisionGoomba(Goomba & goomba);

	void drawTile(sf::RenderTarget& renderer);

	void jumpTile();

	sf::RectangleShape getTile();

	bool playAnimation;
	float firstPositionY;
	float animationPositionY;

	BrickNudge brickNudge;
	BrickDestroy brickDestroy;
};

