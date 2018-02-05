#include "StatePlaying.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
{
	map.loadMap(levels);
	//goomba.emplace_back(sf::Vector2f(570,808));
	//goomba.emplace_back(sf::Vector2f(540, 808));

	goomba.emplace_back(sf::Vector2f(390, 808));
	goomba.emplace_back(sf::Vector2f(1260, 808));
}

void StatePlaying::handleEvent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed) //for switching betwen the menu and the game
	{
		if (e.key.code == sf::Keyboard::Escape)
		{
			openMenu = !openMenu;
		}
	}


	if (openMenu == false)
	{
		Camera::cameraZoom(e);
	}
	else
	{
		buttonPress(e); //checks what button was pressed
	}
}

void StatePlaying::handleInput()
{
	if (openMenu == false)
	{
		player.playerControl(); //all player controls
	}
}

void StatePlaying::update(sf::Time deltaTime)
{
	if (openMenu == false)
	{
		if (player.isFinished) //for loading other maps
		{
			nextLevel++;
			switch (nextLevel)
			{
			case 2:
				levels.Level_2();
				nextLevel++;
				break;
			default:
				nextLevel = 1;
				levels.Level_1();
				break;
			}

			map.loadMap(levels);

			player.playerRec.setPosition(levels.spawnPoint);
			player.isFinished = false;
		}

		player.playerUpdate(deltaTime.asSeconds());
		for (auto& goombas : goomba)
		{
			goombas.GumboUpdate(deltaTime.asSeconds());
		}
		collisions();
		//player.playerRec.move(player.velocity.x, player.velocity.y);

		map.updateDynamic(player.isBig);
		map.updateSpawn(player.isBig);

		Camera::followPlayerSmooth(player.playerRec.getPosition(), deltaTime.asSeconds());
	}
	else
	{
		ButtonUpdate(player, *shouldPop); //updates the button function
	}
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{
}

void StatePlaying::render(sf::RenderTarget& renderer)
{
		renderer.setView(Camera::getView({ 10.f, 1.f })); //background scroll

		map.drawBackGround(renderer); //Background

		map.drawStatic(renderer); //Main (player base)
		map.drawDynamic(renderer); //Main (player base)
		map.drawSpawn(renderer);

		renderer.draw(player.playerRec); //player
		for (auto& goombas : goomba)
		{
			renderer.draw(goombas.entityRec);
		}

		map.drawForeGround(renderer); //Foreground

		renderer.setView(renderer.getDefaultView()); //resets the view to default state

		if (openMenu)
			renderMenu(renderer);
}

void StatePlaying::collisions()
{
	map.CollisionPlayer(player);

	for (auto& goombas : goomba)
	{
		map.CollisionGoomba(goombas);
	}
}

void StatePlaying::pushState(bool*m_shouldPush)
{
}

void StatePlaying::popState(bool & shouldPop)
{
	this->shouldPop = &shouldPop;
}
