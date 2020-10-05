#ifndef HTEST_STATE_HPP
#define HTEST_STATE_HPP

#include "../../Gamestate.hpp"
#include "../../../tilemap/Tilemap.hpp"
#include "../../../audio/Audiohandler.hpp"
#include "../../../entity/Platformer_Controller.hpp"

#include "../../../communal/LDUtil.hpp"
#include "../../../entity/Player/Player.hpp"

class Horus_Test_State:public Gamestate{
private:

	Layer test_layer;

    World_Data world;
    Player p_test;

public:
	Horus_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Horus_Test_State(){}
	void load_sprites(Imagehandler& imagehandler)override;
	void update_layer_resolutions()override;
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);
};


#endif