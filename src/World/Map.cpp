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
	tile[2].setOrigin(sf::Vector2f(tile[0].getSize().x / 2, tile[0].getSize().y / 2));
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
					tile[3].setTextureRect(sf::IntRect(mapForeGround[y][x].x, mapForeGround[y][x].y, tileSize.x, tileSize.y));

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
	if (mapMain.size() != 0)
	{
		for (int x = 0; x < mapMain[1].size(); x++)
		{
			for (int y = 0; y < mapMain.size(); y++)
			{
				if (mapMain[y][x].x != -1 && mapMain[y][x].y != -1)
				{
					MTiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapMain[y][x]);
				}
			}
		}
	}

	for (auto& mTile : MTiles) //setup
	{
		mTile.ToggleCollision(true);
	}
}
void Map::drawMain(sf::RenderTarget & renderer)
{
	if (mapMain.size() != 0)
	{
		for (auto& mTile : MTiles)
		{
			renderer.draw(mTile.getTile());
		}
	}
}
void Map::CollisionMain(Player & player)
{
	if (mapMain.size() != 0)
	{
		for (auto& mTile : MTiles)
		{
			mTile.Collision(player);
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

	if (mapBackGround.size() != 0)
	{
		for (int x = 0; x < mapBackGround[1].size(); x++)
		{
			for (int y = 0; y < mapBackGround.size(); y++)
			{
				if (mapBackGround[y][x].x != -1 && mapBackGround[y][x].y != -1)
				{
					BTiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapBackGround[y][x]);
				}
			}
		}
	}
}
void Map::drawBackGround(sf::RenderTarget & renderer)
{
	if (mapBackGround.size() != 0)
	{
		for (auto& bTile : BTiles)
		{
			bTile.drawTile(renderer);
		}
	}
}


sf::Vector2f Map::Sprite_sheet_coordinates(int tileIndex)
{
	if (tileIndex == -1)
		return sf::Vector2f(-1, -1);//for empty cells in game
	else
	{
		sf::Vector2f coords;
		coords.x = std::round((tileIndex % amountOfTiles) * tileSize.x);   //amount of tiles ONLY in 1 row (on the X axis)
		coords.y = std::round((tileIndex / amountOfTiles) * tileSize.y);  //leave it like this for now


		return coords;
	}
}
