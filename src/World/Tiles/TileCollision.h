#include <iostream>
#include "../../Entities/Player.h"

#pragma once

class TileCollision
{
public:
	TileCollision();



protected:
	void CheckForGround(sf::RectangleShape& tile, Player &player);
	void CollidePlayer(sf::RectangleShape& tile, Player &player);
	void HitBrickUnderPlayer(sf::RectangleShape& tile, Player &player, bool& isHitUnder);
};

