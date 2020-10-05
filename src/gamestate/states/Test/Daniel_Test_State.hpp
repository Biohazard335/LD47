#ifndef DTEST_STATE_HPP
#define DTEST_STATE_HPP

#include "../../Gamestate.hpp"
#include "../../../audio/Audiohandler.hpp"
#include "../../../entity/Bullet/Bullet_Manager.hpp"
#include "../../../wave/Wave_Manager.hpp"
#include "../../../communal/Tick_Timer.hpp"
#include "UIHandler.hpp"


class Daniel_Test_State:public Gamestate{
private:

	Layer test_layer;

	Enemy_Straight dummy_enemy;

	Bullet_Manager bullet_manager;
	Wave_Manager wave_manager;

    UIHandler ui_handler = UIHandler(world);

    sf::Sprite panel;
    sf::Sprite panelx;

	Player player = Player(&bullet_manager);

    World_Data world;

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

	void create_waves();
	void update_player(Mousey&,Keyblade&,Gamepad&);
    void render_bounds(sf::RenderWindow& window);

	void add_bullets();
};


#endif