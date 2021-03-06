#ifndef STATEPLAYING_H_INCLUDED
#define STATEPLAYING_H_INCLUDED

#include "StateBase.h"
#include "../Util/Camera.h"
#include "../World/Map.h"
#include "../GUI/inGameMenu.h"
#include "../World/Level.h"

//all entities
#include "../Entities/Player.h"
#include "../Entities/Goomba.h"

class StatePlaying
	: public StateBase
	, public inGameMenu
{
 public:
	 StatePlaying(Game& game);

     void handleEvent    (sf::Event e)                   override;
     void handleInput    ()                              override;
     void update         (sf::Time deltaTime)            override;
     void fixedUpdate    (sf::Time deltaTime)            override;
     void render         (sf::RenderTarget& renderer)    override;

	 void collisions();

	 void pushState(bool*m_shouldPush)          override;
	 void popState(bool & shouldPop)                 override;

private:
	int nextLevel = 1;
	Level levels;
	Player player;
	std::vector<Goomba> goombas;
	Map map;
	bool openMenu = false;
	bool* shouldPop;
};

#endif // STATEPLAYING_H_INCLUDED
