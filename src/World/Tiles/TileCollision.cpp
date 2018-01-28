#include "TileCollision.h"
#include <string>

TileCollision::TileCollision()
{
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

		if (entityRight > BlockLeft - 10 &&
			entityLeft < BlockRight + 10 &&
			entityBottom > BlockTop + 20 &&
			entityTop < BlockBottom - 20)
		{
			if (entityRight >= BlockLeft && entityLeft <= BlockLeft)  //Left side of the Block
			{
				entity.entityRec.move(-abs(entity.velocity.x), 0);
				entity.velocity.x = 0;
			}

			if (entityLeft <= BlockRight && entityRight >= BlockRight)   //Right side of the block
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
			if (entityTop < BlockBottom && entityBottom > BlockBottom)    //Bottom side of the block
			{
				entity.entityRec.move(0, -entity.velocity.y);
				entity.velocity.y = 0;
			}

			if (entityBottom > BlockTop && entityTop < BlockTop)    //Top side of the block
			{
				entity.isJumping = false;
				entity.isOnGround = true;
				//entity.entityRec.move(0, -abs(entity.velocity.y));//abs is here to make sure it always pushes you up
				entity.entityRec.setPosition(entity.getPos().x, tile.getGlobalBounds().top - tile.getSize().y/2);
				entity.velocity.y = 0;
			}
		}
	}
}