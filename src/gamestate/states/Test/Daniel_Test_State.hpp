#ifndef DTEST_STATE_HPP
#define DTEST_STATE_HPP

#include "../../Gamestate.hpp"
#include "../../../tilemap/Tilemap.hpp"
#include "../../../audio/Audiohandler.hpp"
#include "../../../entity/Circle_Player.hpp"
#include "../../../entity/Bullet/Bullet_Manager.hpp"
#include "../../../entity/Bullet/Linear_Bullet.hpp"
#include "../../../communal/Tick_Timer.hpp"

class Daniel_Test_State:public Gamestate{
private:

	Layer test_layer;

	Circle_Player player;
	Circle_Player other;

	Bullet_Manager bullet_manager;
	Tick_Timer enemy_spawn_timer;


public:
	Daniel_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Daniel_Test_State(){}
	void load_sprites(Imagehandler& imagehandler)override;
	void update_layer_resolutions()override;
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);


};


#endif