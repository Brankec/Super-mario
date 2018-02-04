#include "SpawnTiles.h"
#include <string>

SpawnTiles::SpawnTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex)
{
	tileRec.setSize({ 64,64 });
	tileRec.setPosition(TilePositionX, TilePositionY);

	tileTextureSize.x = 16;
	tileTextureSize.y = 16;

	tileRec.setTexture(&tileTexture);
	setTileTexture(tileIndex);

	ToggleCollision(true);

	playAnimation = true;
	firstPositionY = tileRec.getPosition().y;//for determing how far should it go up nefore going down when hit
}

void SpawnTiles::setTileTexture(sf::Vector2f tileIndex) //the index is the actual tile texture position.
{
	tileRec.setTextureRect(sf::IntRect(tileIndex.x, tileIndex.y, tileTextureSize.x, tileTextureSize.y));
}

void SpawnTiles::setTilePosition(sf::Vector2f tPosition)
{
	tileRec.setPosition(tPosition);
}

void SpawnTiles::ToggleCollision(bool set)
{
	doesCollide = set;
}

void SpawnTiles::CollisionPlayer(Player & entity)
{
	if (doesCollide)
	{
		CheckForGround(tileRec, entity.playerRec.getGlobalBounds(), entity.isOnGround);
		HitBrickUnderPlayer(tileRec, entity, isTileHit);
	}
}

void SpawnTiles::CollisionGoomba(Goomba & goomba)
{
	CheckForGround(tileRec, goomba.entityRec.getGlobalBounds(), goomba.isOnGround);
	CollideGoomba(tileRec, goomba);
}

void SpawnTiles::drawTile(sf::RenderTarget & renderer)
{
	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && //draws only within our view on X axis
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		renderer.draw(tileRec);
	}
}

void SpawnTiles::jumpTile()
{
	animationPositionY = tileRec.getPosition().y;

	if (playAnimation)
	{
		if (animationPositionY < firstPositionY - 20)
		{
			playAnimation = false;
		}
		animationPositionY--;
	}
	else
	{
		if (animationPositionY > firstPositionY - 1)
		{
			isTileHit = false;
			playAnimation = true;
		}

		if (isTileHit)
			animationPositionY++;
	}

	tileRec.setPosition(tileRec.getPosition().x, animationPositionY);
}

sf::RectangleShape SpawnTiles::getTile()
{
	return tileRec;
}


