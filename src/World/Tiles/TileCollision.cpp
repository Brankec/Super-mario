#include "TileCollision.h"
#include <string>

TileCollision::TileCollision()
{
}

void TileCollision::CheckForGround(sf::RectangleShape & tile, sf::FloatRect entity, bool* isCollide)
{
	sf::FloatRect entityBounds = entity;

	entityBounds.height = entity.height + 5;

	if (entityBounds.intersects(tile.getGlobalBounds()))
	{//since I couldnt get it to get false when we arent touching anything, I made it turn false in player class in player update function
		//entity.isOnGround = true;
		//isCollide[1] = true;
	}
}

void TileCollision::Collide(sf::RectangleShape& tile, sf::FloatRect entity, bool* isCollide)
{
	if (entity.intersects(tile.getGlobalBounds()))
	{
		float entityLeft = entity.left - entity.width / 2;
		float entityRight = entity.left + entity.width / 2;
		float entityTop = entity.top - entity.height / 2;
		float entityBottom = entity.top + entity.height / 2;

		float BlockLeft = tile.getPosition().x - tile.getSize().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y - tile.getSize().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (entityRight > BlockLeft - 10 && //these acked values should be tweaked for better collision detection
			entityLeft < BlockRight + 10 &&
			entityBottom > BlockTop + 20 &&
			entityTop < BlockBottom - 20)
		{
			if (entityRight >= BlockLeft && entityLeft <= BlockLeft)  //Left side of the Block
			{
				//entity.playerRec.move(-abs(entity.velocity.x), 0);
				//entity.velocity.x = 0;
				isCollide[0] = true;
				//std::cout << "Left!" << std::endl;
			}

			if (entityLeft <= BlockRight && entityRight >= BlockRight)   //Right side of the block
			{
				//entity.playerRec.move(abs(entity.velocity.x), 0);
				//entity.velocity.x = 0;
				isCollide[2] = true;
				//std::cout << "Right!" << std::endl;
			}

		}
		if (entityRight > BlockLeft + 20 &&
			entityLeft < BlockRight - 20 &&
			entityBottom > BlockTop - 10 &&
			entityTop < BlockBottom + 10)
		{
			if (entityTop < BlockBottom && entityBottom > BlockBottom)    //Bottom side of the block
			{
				//entity.playerRec.move(0, -entity.velocity.y);
				//entity.velocity.y = 0.1; //because when its 0 it can jump again. Fix it later
			}

			if (entityBottom > BlockTop && entityTop < BlockTop)    //Top side of the block
			{
				//entity.isJumping = false;
				isCollide[1] = true;
				//entity.playerRec.setPosition(entity.playerRec.getPosition().x, tile.getGlobalBounds().top - tile.getSize().y / 2);
				//entity.velocity.y = 0;
			}
		}
	}
}