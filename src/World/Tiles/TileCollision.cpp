#include "TileCollision.h"
#include <string>

TileCollision::TileCollision()
{
}

void TileCollision::CheckForGround(sf::RectangleShape & tile, Player & entity)
{
	sf::FloatRect entityBounds = entity.getAABB();

	entityBounds.height = entity.getAABB().height + 5;

	if (entityBounds.intersects(tile.getGlobalBounds()))
	{//since I couldnt get it to get false when we arent touching anything, I made it turn false in player class in player update function
		entity.isOnGround = true;
	}
}

void TileCollision::Collide(sf::RectangleShape& tile, Player &entity)
{
	if (entity.getAABB().intersects(tile.getGlobalBounds()))
	{
		float entityLeft = entity.entityRec.getPosition().x - entity.getAABB().width / 2;
		float entityRight = entity.entityRec.getPosition().x + entity.getAABB().width / 2;
		float entityTop = entity.entityRec.getPosition().y - entity.getAABB().height / 2;
		float entityBottom = entity.entityRec.getPosition().y + entity.getAABB().height / 2;

		float BlockLeft = tile.getPosition().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (entityRight > BlockLeft - 10 && //these acked values should be tweaked for better collision detection
			entityLeft < BlockRight + 10 &&
			entityBottom > BlockTop + 20 &&
			entityTop < BlockBottom - 20)
		{
			if (entityRight >= BlockLeft && entityLeft <= BlockLeft && entity.velocity.x >= 0)  //Left side of the Block
			{
				entity.entityRec.move(-abs(entity.velocity.x), 0);
				entity.velocity.x = 0;
			}

			if (entityLeft <= BlockRight && entityRight >= BlockRight && entity.velocity.x <= 0)   //Right side of the block
			{
				entity.entityRec.move(abs(entity.velocity.x), 0);
				entity.velocity.x = 0;
			}

		}
		if (entityRight > BlockLeft + 20 &&
			entityLeft < BlockRight - 20 &&
			entityBottom > BlockTop - 10 &&
			entityTop < BlockBottom + 10)
		{
			if (entityTop < BlockBottom && entityBottom > BlockBottom && entity.velocity.y <= 0)    //Bottom side of the block
			{
				entity.entityRec.move(0, -entity.velocity.y);
				entity.velocity.y = 0.1; //because when its 0 it can jump again. Fix it later
			}

			if (entityBottom > BlockTop && entityTop < BlockTop && entity.velocity.y >= 0)    //Top side of the block
			{
				entity.isJumping = false;
				entity.entityRec.setPosition(entity.getPos().x, tile.getGlobalBounds().top - tile.getSize().y / 2);
				entity.velocity.y = 0;
			}
		}
	}
}