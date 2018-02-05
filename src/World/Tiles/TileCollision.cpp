#include "TileCollision.h"
#include <string>

TileCollision::TileCollision()
{
}

void TileCollision::CheckForGround(sf::RectangleShape & tile, sf::FloatRect position, bool &isOnGround)
{
	sf::FloatRect entityBounds = position;

	entityBounds.left   = position.left   + 5;
	entityBounds.width  = position.width  - 5;
	entityBounds.height += 5;

	if (entityBounds.intersects(tile.getGlobalBounds()))
	{//since I couldnt get it to get false when we arent touching anything, I made it turn false in player class in player update function
		isOnGround = true;
	}
}

void TileCollision::CollidePlayer(sf::RectangleShape& tile, Player &player)
{
	if (player.playerRec.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		float playerLeft = player.playerRec.getPosition().x - player.playerRec.getGlobalBounds().width / 2 + 5;
		float playerRight = player.playerRec.getPosition().x + player.playerRec.getGlobalBounds().width / 2 - 5;
		float playerTop = player.playerRec.getPosition().y - player.playerRec.getGlobalBounds().height;
		float playerBottom = player.playerRec.getPosition().y;

		float BlockLeft = tile.getPosition().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (playerRight > BlockLeft && //these acked values should be tweaked for better collision detection
			playerLeft < BlockRight &&
			playerBottom > BlockTop + 32 &&
			playerTop < BlockBottom - 32)
		{
			if (playerRight >= BlockLeft && playerLeft <= BlockLeft && player.velocity.x >= 0)  //Left side of the Block
			{
				player.playerRec.move(-abs(player.velocity.x), 0);
				player.velocity.x = 0;
			}

			if (playerLeft <= BlockRight && playerRight >= BlockRight && player.velocity.x <= 0)   //Right side of the block
			{
				player.playerRec.move(abs(player.velocity.x), 0);
				player.velocity.x = 0;
			}

		}
		if (playerRight > BlockLeft + 5 &&
			playerLeft < BlockRight - 5 &&
			playerBottom > BlockTop &&
			playerTop < BlockBottom)
		{
			if (playerTop < BlockBottom && playerBottom > BlockBottom && player.velocity.y <= 0)    //Bottom side of the block
			{
				player.playerRec.move(0, -player.velocity.y);
				player.velocity.y = 0.1; //because when its 0 it can jump again. Fix it later
			}

			if (playerBottom > BlockTop && playerTop < BlockTop && player.velocity.y >= 0)    //Top side of the block
			{
				player.isJumping = false;
				player.playerRec.setPosition(player.playerRec.getPosition().x, tile.getGlobalBounds().top);
				player.velocity.y = 0;
			}
		}
	}
}

void TileCollision::HitBrickUnderPlayer(sf::RectangleShape& tile, Player &player, bool& isHitUnder)
{
	if (player.playerRec.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		float playerLeft = player.playerRec.getPosition().x - player.playerRec.getGlobalBounds().width / 2 + 5;
		float playerRight = player.playerRec.getPosition().x + player.playerRec.getGlobalBounds().width / 2 - 5;
		float playerTop = player.playerRec.getPosition().y - player.playerRec.getGlobalBounds().height;
		float playerBottom = player.playerRec.getPosition().y;

		float BlockLeft = tile.getPosition().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (playerRight > BlockLeft && //these hacked values should be tweaked for better collision detection
			playerLeft < BlockRight &&
			playerBottom > BlockTop + 32 &&
			playerTop < BlockBottom - 32)
		{
			if (playerRight >= BlockLeft && playerLeft <= BlockLeft && player.velocity.x >= 0)  //Left side of the Block
			{
				player.playerRec.move(-abs(player.velocity.x), 0);
				player.velocity.x = 0;
			}

			if (playerLeft <= BlockRight && playerRight >= BlockRight && player.velocity.x <= 0)   //Right side of the block
			{
				player.playerRec.move(abs(player.velocity.x), 0);
				player.velocity.x = 0;
			}

		}
		if (playerRight > BlockLeft + 5 &&
			playerLeft < BlockRight - 5 &&
			playerBottom > BlockTop &&
			playerTop < BlockBottom)
		{
			if (playerTop < BlockBottom && playerBottom > BlockBottom && player.velocity.y <= 0)    //Bottom side of the block
			{
				player.playerRec.move(0, -player.velocity.y);
				player.velocity.y = 0.1; //because when its 0 it can jump again. Fix it later

				if(playerRight > BlockLeft + 15 && playerLeft < BlockRight - 15)
				isHitUnder = true;
			}

			if (playerBottom > BlockTop && playerTop < BlockTop && player.velocity.y >= 0)    //Top side of the block
			{
				player.isJumping = false;
				player.playerRec.setPosition(player.playerRec.getPosition().x, tile.getGlobalBounds().top);
				player.velocity.y = 0;
			}
		}
	}
}

void TileCollision::CollideGoomba(sf::RectangleShape & tile, Goomba &goomba)
{
	if (goomba.entityRec.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		float goombaLeft = goomba.entityRec.getPosition().x - goomba.entityRec.getGlobalBounds().width / 2 + 15;
		float goombaRight = goomba.entityRec.getPosition().x + goomba.entityRec.getGlobalBounds().width / 2 - 15;
		float goombaTop = goomba.entityRec.getPosition().y - goomba.entityRec.getGlobalBounds().height / 2;
		float goombaBottom = goomba.entityRec.getPosition().y + goomba.entityRec.getGlobalBounds().height / 2;

		float BlockLeft = tile.getPosition().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (goombaRight > BlockLeft && //these hacked values should be tweaked for better collision detection
			goombaLeft < BlockRight &&
			goombaBottom > BlockTop + 32 &&
			goombaTop < BlockBottom - 32)
		{
			if (goombaRight >= BlockLeft && goombaLeft <= BlockLeft && goomba.velocity.x >= 0)  //Left side of the Block
			{
				//goomba.entityRec.setPosition(BlockLeft, goomba.entityRec.getPosition().y);
				goomba.velocity.x = -abs(goomba.velocity.x);
			}

			if (goombaLeft <= BlockRight && goombaRight >= BlockRight && goomba.velocity.x <= 0)   //Right side of the block
			{
				//goomba.entityRec.move(abs(goomba.velocity.x), 0);
				goomba.velocity.x = abs(goomba.velocity.x);
			}

		}
		if (goombaRight > BlockLeft + 5 &&
			goombaLeft < BlockRight - 5 &&
			goombaBottom > BlockTop &&
			goombaTop < BlockBottom)
		{
			if (goombaTop < BlockBottom && goombaBottom > BlockBottom && goomba.velocity.y <= 0)    //Bottom side of the block
			{
				goomba.entityRec.move(0, -goomba.velocity.y);
				goomba.velocity.y = 0.1; //because when its 0 it can jump again. Fix it later
			}

			if (goombaBottom > BlockTop && goombaTop < BlockTop && goomba.velocity.y >= 0)    //Top side of the block
			{
				goomba.entityRec.setPosition(goomba.entityRec.getPosition().x, tile.getGlobalBounds().top - tile.getSize().y / 2);
				goomba.velocity.y = 0;
			}
		}
	}
}
