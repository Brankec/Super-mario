#include "TileCollision.h"
#include <string>

TileCollision::TileCollision()
{
}

void TileCollision::CheckForGround(sf::RectangleShape & tile, Player & player)
{
	sf::FloatRect playerBounds = player.playerRec.getGlobalBounds();

	playerBounds.height = player.playerRec.getGlobalBounds().height + 5;

	if (playerBounds.intersects(tile.getGlobalBounds()))
	{//since I couldnt get it to get false when we arent touching anything, I made it turn false in player class in player update function
		player.isOnGround = true;
	}
}

void TileCollision::CollidePlayer(sf::RectangleShape& tile, Player &player)
{
	if (player.playerRec.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		float playerLeft = player.playerRec.getPosition().x - player.playerRec.getGlobalBounds().width / 2 + 15;
		float playerRight = player.playerRec.getPosition().x + player.playerRec.getGlobalBounds().width / 2 - 15;
		float playerTop = player.playerRec.getPosition().y - player.playerRec.getGlobalBounds().height / 2;
		float playerBottom = player.playerRec.getPosition().y + player.playerRec.getGlobalBounds().height / 2;

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
				player.playerRec.setPosition(player.playerRec.getPosition().x, tile.getGlobalBounds().top - tile.getSize().y / 2);
				player.velocity.y = 0;
			}
		}
	}
}

void TileCollision::HitBrickUnderPlayer(sf::RectangleShape& tile, Player &player, bool& isHitUnder)
{
	if (player.playerRec.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		float playerLeft = player.playerRec.getPosition().x - player.playerRec.getGlobalBounds().width / 2 + 15;
		float playerRight = player.playerRec.getPosition().x + player.playerRec.getGlobalBounds().width / 2 - 15;
		float playerTop = player.playerRec.getPosition().y - player.playerRec.getGlobalBounds().height / 2;
		float playerBottom = player.playerRec.getPosition().y + player.playerRec.getGlobalBounds().height / 2;

		float BlockLeft = tile.getPosition().x;
		float BlockRight = tile.getPosition().x + tile.getSize().x;
		float BlockTop = tile.getPosition().y;
		float BlockBottom = tile.getPosition().y + tile.getSize().y;

		if (playerRight > BlockLeft &&
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
				isHitUnder = true;
			}

			if (playerBottom > BlockTop && playerTop < BlockTop && player.velocity.y >= 0)    //Top side of the block
			{
				player.isJumping = false;
				player.playerRec.setPosition(player.playerRec.getPosition().x, tile.getGlobalBounds().top - tile.getSize().y / 2);
				player.velocity.y = 0;
			}
		}
	}
}
