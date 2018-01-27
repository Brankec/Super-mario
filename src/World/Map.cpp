#include "Map.h"
#include <string>

Map::Map()
{
	setOriginCenter();
}

void Map::loadMap(Level& levelsPass)
{
	if (openfileForeground.is_open())
		openfileForeground.close();

	if (openfileMain.is_open())
		openfileMain.close();

	if (openfileBackground.is_open())
		openfileBackground.close();

	this->levels = &levelsPass;

	openfileForeground.open("res/Maps/" + levels->ForeGround + ".txt");
	openfileMain.open("res/Maps/" + levels->Main + ".txt");
	openfileBackground.open("res/Maps/" + levels->BackGround + ".txt");

	this->powOfN = pow(2, levels->gridSize);
	this->amountOfTiles = levels->amountOfTilesX;
	this->tileSize = levels->tileSize;
	this->objectiveTileCoords = levels->objectiveTileCoords;

	loadTilesForeground();
	loadTilesMain();
	loadTilesBackground();
}

void Map::setOriginCenter()
{
	tile[0].setOrigin(sf::Vector2f(tile[0].getSize().x / 2, tile[0].getSize().y / 2));
}

void Map::loadTilesForeground()
{
	mapForeGround.clear();

	if (openfileForeground.is_open())
	{
		std::string tileLocation;
		openfileForeground >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))
			tile[3].setTexture(&tileTexture);

		tile[3].setSize(sf::Vector2f((float)powOfN, (float)powOfN));

		while (openfileForeground.good())
		{
			openfileForeground >> tileIndex;
			if (tileIndex != ',')
			tempMap.push_back(Sprite_sheet_coordinates(tileIndex-1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

			if (openfileForeground.peek() == '\n')
			{
				mapForeGround.push_back(tempMap);
				tempMap.clear();
			}
			
		}
	}
}
void Map::drawForeGround(sf::RenderTarget& renderer)
{
	if (mapForeGround.size() != 0)
	{
		float cam_x = Camera::getView().getCenter().x;
		int cam_x_tile = cam_x / tile[3].getSize().x;
		int Tile_row_width = (renderer.getView().getSize().x + 2000) / mapForeGround[1].size();
		float cam_y = Camera::getView().getCenter().y;
		int cam_y_tile = cam_y / tile[3].getSize().y;
		int Tile_column_height = (renderer.getView().getSize().y) / mapForeGround.size();

		int X_border_right = std::min((int)mapForeGround[1].size(), cam_x_tile + Tile_row_width / 2);
		int Y_border_right = std::min((int)mapForeGround.size(), cam_y_tile + Tile_column_height / 2);

		for (int x = std::max(cam_x_tile - Tile_row_width / 2, 0); x < X_border_right; x++)
			for (int y = std::max(cam_y_tile - Tile_column_height / 2, 0); y < Y_border_right; y++)
			{
				if (mapForeGround[y][x].x != -1 && mapForeGround[y][x].y != -1)
				{
					tile[3].setPosition(x * (float)powOfN, y * (float)powOfN);
					tile[3].setTextureRect(sf::IntRect(mapForeGround[y][x].x + 1, mapForeGround[y][x].y + 1, tileSize.x - 2, tileSize.y - 2));

					renderer.draw(tile[3]);
				}
			}
	}
}

void Map::loadTilesMain()
{
	mapMain.clear();

	if (openfileMain.is_open())
	{
		std::string tileLocation;
		openfileMain >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))
			tile[2].setTexture(&tileTexture);

		tile[2].setSize(sf::Vector2f((float)powOfN, (float)powOfN));
		while (openfileMain.good())
		{

			openfileMain >> tileIndex;
			if (tileIndex != ',')
			{
				tempMap.push_back(Sprite_sheet_coordinates(tileIndex - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

				if (openfileMain.peek() == '\n')
				{
					mapMain.push_back(tempMap);
					tempMap.clear();
				}
			}
		}
	}
}
void Map::drawMain(sf::RenderTarget & renderer, Player & player)
{
	if (mapMain.size() != 0)
	{
		float cam_x = Camera::getView().getCenter().x;
		int cam_x_tile = cam_x / tile[2].getSize().x;
		int Tile_row_width = (renderer.getView().getSize().x + 2000) / mapMain[1].size();
		float cam_y = Camera::getView().getCenter().y;
		int cam_y_tile = cam_y / tile[2].getSize().y;
		int Tile_column_height = (renderer.getView().getSize().y) + 100 / mapMain.size();

		int X_border_right = std::min((int)mapMain[1].size(), cam_x_tile + Tile_row_width / 2);
		int Y_border_right = std::min((int)mapMain.size(), cam_y_tile + Tile_column_height / 2);

		for (int x = std::max(cam_x_tile - Tile_row_width / 2, 0); x < X_border_right; x++)
			for (int y = std::max(cam_y_tile - Tile_column_height / 2, 0); y < Y_border_right; y++)
			{
				if (mapMain[y][x].x != -1 && mapMain[y][x].y != -1)
				{
					tile[2].setPosition(x * (float)powOfN, y * (float)powOfN);
					tile[2].setTextureRect(sf::IntRect(mapMain[y][x].x + 1, mapMain[y][x].y + 1, tileSize.x - 2, tileSize.y - 2));

					Collision(player);

					renderer.draw(tile[2]);
				}
			}
	}
}

void Map::loadTilesBackground()
{
	mapBackGround.clear();

	if (openfileBackground.is_open())
	{
		std::string tileLocation;
		openfileBackground >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))
			tile[0].setTexture(&tileTexture);

		tile[0].setSize(sf::Vector2f((float)powOfN, (float)powOfN));
		while (openfileBackground.good())
		{
			openfileBackground >> tileIndex;
			if (tileIndex != ',')
				tempMap.push_back(Sprite_sheet_coordinates(tileIndex - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

			if (openfileBackground.peek() == '\n')
			{
				mapBackGround.push_back(tempMap);
				tempMap.clear();
			}

		}
	}
}
void Map::drawBackGround(sf::RenderTarget & renderer)
{
	if (mapBackGround.size() != 0)
	{
		float cam_x = Camera::getView().getCenter().x;
		int cam_x_tile = cam_x / tile[0].getSize().x;
		int Tile_row_width = (renderer.getView().getSize().x + 2000) / mapBackGround[1].size();
		float cam_y = Camera::getView().getCenter().y;
		int cam_y_tile = cam_y / tile[0].getSize().y;
		int Tile_column_height = (renderer.getView().getSize().y) / mapBackGround.size();

		int X_border_right = std::min((int)mapBackGround[1].size(), cam_x_tile + Tile_row_width / 2);
		int Y_border_right = std::min((int)mapBackGround.size(), cam_y_tile + Tile_column_height / 2);

		for (int x = std::max(cam_x_tile - Tile_row_width / 2, 0); x < X_border_right; x++)
			for (int y = std::max(cam_y_tile - Tile_column_height / 2, 0); y < Y_border_right; y++)
			{
				if (mapBackGround[y][x].x != -1 && mapBackGround[y][x].y != -1)
				{					
					tile[0].setPosition(x * (float)powOfN, y * (float)powOfN);
					tile[0].setTextureRect(sf::IntRect(mapBackGround[y][x].x + 1, mapBackGround[y][x].y + 1, tileSize.x - 2, tileSize.y - 2));

					renderer.draw(tile[0]);
				}
			}
	}
}


sf::Vector2i Map::Sprite_sheet_coordinates(int tileIndex)
{
	if (tileIndex == -1)
		return sf::Vector2i(-1, -1);//for empty cells in game
	else
	{
		sf::Vector2i coords;
		coords.x = (tileIndex % amountOfTiles) * tileSize.x;   //amount of tiles ONLY in 1 row (on the X axis)
		coords.y = (tileIndex / amountOfTiles) * tileSize.y;  //leave it like this for now


		return coords;
	}
}


void Map::Collision(Player &player)
{
	float PlayerLeft = player.entityRec.getPosition().x - player.getAABB().width / 2;
	float PlayerRight = player.entityRec.getPosition().x + player.getAABB().width / 2;
	float PlayerTop = player.entityRec.getPosition().y - player.getAABB().height / 2;
	float PlayerBottom = player.entityRec.getPosition().y + player.getAABB().height / 2;

	float BlockLeft = tile[2].getPosition().x;
	float BlockRight = tile[2].getPosition().x + tile[2].getSize().x;
	float BlockTop = tile[2].getPosition().y;
	float BlockBottom = tile[2].getPosition().y + tile[2].getSize().y;

	if (PlayerRight > BlockLeft - 10 && 
		PlayerLeft < BlockRight + 10 && 
		PlayerBottom > BlockTop + 5 && 
		PlayerTop < BlockBottom - 5)
	{
		if (PlayerRight >= BlockLeft && PlayerLeft <= BlockLeft)  //Left side of the Block
		{
			player.entityRec.move(-0.5, 0);
			player.velocity.x = 0;
		}

		if (PlayerLeft <= BlockRight && PlayerRight >= BlockRight)   //Right side of the block
		{
			player.entityRec.move(-player.velocity.x, 0);
			player.entityRec.move(0.5, 0);
			player.velocity.x = 0;
		}

	}
	if (PlayerRight > BlockLeft + 5 && 
		PlayerLeft < BlockRight - 5 && 
		PlayerBottom > BlockTop - 10 && 
		PlayerTop < BlockBottom + 10)
	{
		if (PlayerTop < BlockBottom && PlayerBottom > BlockBottom)    //Bottom side of the block
		{
			player.entityRec.move(0, -player.velocity.y);
			player.velocity.y = 0;
		}

		if (PlayerBottom > BlockTop && PlayerTop < BlockTop)    //Top side of the block
		{
			player.isJumping = false;
			player.isOnGround = true;
			player.entityRec.move(0, -player.velocity.y);
			player.velocity.y = 0;
		}
	}
}