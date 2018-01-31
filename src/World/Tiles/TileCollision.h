#include <iostream>
#include "../../Entities/Player.h"

#pragma once

class TileCollision
{
public:
	TileCollision();



protected:
	void CheckForGround(sf::RectangleShape& tile, Player &entity);
	void CollidePlayer(sf::RectangleShape& tile, Player &entity);
};

