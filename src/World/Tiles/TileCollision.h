#include <iostream>
#include "../../Entities/Player.h"
#include "../../Entities/Goomba.h"

#pragma once

class TileCollision
{
public:
	TileCollision();



protected:
	void CheckForGround(sf::RectangleShape& tile, sf::FloatRect position, bool &isOnGround);
	void CollidePlayer(sf::RectangleShape& tile, Player &player);
	void HitBrickUnderPlayer(sf::RectangleShape& tile, Player &player, bool& isHitUnder);
	void CollideGoomba(sf::RectangleShape& tile, Goomba &goomba);
};

