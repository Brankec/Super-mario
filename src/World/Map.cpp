#include "Map.h"
#include <string>

Map::Map()
{
}

void Map::loadMap(Level& levelsPass)
{
	if (openfileForeground.is_open())
		openfileForeground.close();

	if (openfileStatic.is_open())
		openfileStatic.close();

	if (openfileDynamic.is_open())
		openfileDynamic.close();

	if (openfileSpawn.is_open())
		openfileSpawn.close();

	if (openfileBackground.is_open())
		openfileBackground.close();

	this->levels = &levelsPass;

	openfileForeground.open("res/Maps/" + levels->ForeGround + ".txt");
	openfileStatic.open("res/Maps/" + levels->Static + ".txt");
	openfileDynamic.open("res/Maps/" + levels->Dynamic + ".txt");
	openfileSpawn.open("res/Maps/" + levels->Spawn + ".txt");
	openfileBackground.open("res/Maps/" + levels->BackGround + ".txt");

	this->powOfN = pow(2, levels->gridSize);
	this->amountOfTiles = levels->amountOfTilesX;
	this->tileSize = levels->tileSize;
	this->objectiveTileCoords = levels->objectiveTileCoords;

	loadTilesForeground();
	loadTilesStatic();
	loadTilesDynamic();
	loadTilesSpawn();
	loadTilesBackground();
}

void Map::loadTilesForeground()
{
	mapForeGround.clear();

	if (openfileForeground.is_open())
	{
		std::string tileLocation;
		openfileForeground >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))
		while (openfileForeground.good())
		{
			openfileForeground >> tileIndex;
			tempMap.push_back(Sprite_sheet_coordinates(tileIndex-1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

			if (openfileForeground.peek() == '\n')
			{
				mapForeGround.push_back(tempMap);
				tempMap.clear();
			}
			
		}
	}

	if (mapForeGround.size() != 0)
	{
		for (int x = 0; x < mapForeGround[1].size(); x++)
		{
			for (int y = 0; y < mapForeGround.size(); y++)
			{
				if (mapForeGround[y][x].x != -1 && mapForeGround[y][x].y != -1)
				{
					FTiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapForeGround[y][x]);
				}
			}
		}
	}
}
void Map::drawForeGround(sf::RenderTarget& renderer)
{
	if (mapForeGround.size() != 0)
	{
		for (auto& fTile : FTiles)
		{
			fTile.drawTile(renderer);
		}
	}
}

void Map::loadTilesStatic()
{
	mapStatic.clear();

	if (openfileStatic.is_open())
	{
		std::string tileLocation;
		openfileStatic >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))

		while (openfileStatic.good())
		{
			openfileStatic >> tileIndex;
			if (tileIndex != ',')
			{
				tempMap.push_back(Sprite_sheet_coordinates(tileIndex - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

				if (openfileStatic.peek() == '\n')
				{
					mapStatic.push_back(tempMap);
					tempMap.clear();
				}
			}
		}
	}
	if (mapStatic.size() != 0)
	{
		for (int x = 0; x < mapStatic[1].size(); x++)
		{
			for (int y = 0; y < mapStatic.size(); y++)
			{
				if (mapStatic[y][x].x != -1 && mapStatic[y][x].y != -1)
				{
					STiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapStatic[y][x]);
				}
			}
		}
	}
}
void Map::drawStatic(sf::RenderTarget & renderer)
{
	if (mapStatic.size() != 0)
	{
		for (auto& sTile : STiles)
		{
			sTile.drawTile(renderer);
		}
	}
}
void Map::loadTilesDynamic()
{
	mapDynamic.clear();

	if (openfileDynamic.is_open())
	{
		std::string tileLocation;
		openfileDynamic >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))

			while (openfileDynamic.good())
			{
				openfileDynamic >> tileIndex;
				if (tileIndex != ',')
				{
					tempMap.push_back(Sprite_sheet_coordinates(tileIndex - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

					if (openfileDynamic.peek() == '\n')
					{
						mapDynamic.push_back(tempMap);
						tempMap.clear();
					}
				}
			}
	}
	if (mapDynamic.size() != 0)
	{
		for (int x = 0; x < mapDynamic[1].size(); x++)
		{
			for (int y = 0; y < mapDynamic.size(); y++)
			{
				if (mapDynamic[y][x].x != -1 && mapDynamic[y][x].y != -1)
				{
					DTiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapDynamic[y][x]);
				}
			}
		}
	}
}
void Map::drawDynamic(sf::RenderTarget & renderer)
{
	if (mapDynamic.size() != 0)
	{
		for (auto& dTile : DTiles)
		{
			dTile.drawTile(renderer);
		}
	}
}
void Map::updateDynamic(bool& isBig)
{
	for (int i = 0; i < DTiles.size(); i++)
	{
		if (DTiles[i].isTileHit == true)
		{
			if (isBig)
			{
				DTiles.erase(DTiles.begin() + i);
				DTiles[i].brickDestroy.playSound(60);
				DTiles[i].brickDestroy.isSoundOver();
			}
			else
			{
				DTiles[i].jumpTile();
				DTiles[i].brickDestroy.isSoundOver();
			}
		}
	}
}

void Map::loadTilesSpawn()
{
	mapSpawn.clear();

	if (openfileSpawn.is_open())
	{
		std::string tileLocation;
		openfileSpawn >> tileLocation;

		if (tileTexture.loadFromFile(tileLocation))

			while (openfileSpawn.good())
			{
				openfileSpawn >> tileIndex;
				if (tileIndex != ',')
				{
					tempMap.push_back(Sprite_sheet_coordinates(tileIndex - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

					if (openfileSpawn.peek() == '\n')
					{
						mapSpawn.push_back(tempMap);
						tempMap.clear();
					}
				}
			}
	}
	if (mapSpawn.size() != 0)
	{
		for (int x = 0; x < mapSpawn[1].size(); x++)
		{
			for (int y = 0; y < mapSpawn.size(); y++)
			{
				if (mapSpawn[y][x].x != -1 && mapSpawn[y][x].y != -1)
				{
					QTiles.emplace_back(x * (float)powOfN, y * (float)powOfN, tileTexture, mapSpawn[y][x]);
				}
			}
		}
	}
}
void Map::drawSpawn(sf::RenderTarget & renderer)
{
	if (mapSpawn.size() != 0)
	{
		for (auto& qTile : QTiles)
		{
			qTile.drawTile(renderer);
		}
	}
}
void Map::updateSpawn(bool& isBig)
{
	for (int i = 0; i < QTiles.size(); i++)
	{
		if (QTiles[i].isTileHit == true)
		{
		}
	}
}

void Map::Collision(Player & player)
{
	if (mapStatic.size() != 0)
	{
		for (auto& sTile : STiles)
		{
			sTile.Collision(player);
		}
	}

	if (mapDynamic.size() != 0)
	{
		for (auto& dTile : DTiles)
		{
			dTile.Collision(player);
		}
	}

	if (mapSpawn.size() != 0)
	{
		for (auto& qTile : QTiles)
		{
			qTile.Collision(player);
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
