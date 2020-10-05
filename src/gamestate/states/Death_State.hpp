#ifndef DEATHSTATE_HPP
#define DEATHSTATE_HPP

#include "../Gamestate.hpp"

class Death_State :public Gamestate{
public:
	void update(Mousey&,Keyblade&,Gamepad&);
	void render(sf::RenderWindow& window);
	void load_sprites(Imagehandler& imagehandler);
	void execute_data(Data_Packet);
	Death_State(Imagehandler& imagehandler);
	~Death_State()=default;
};

#endif