#include "Daniel_Test_State.hpp"
#include "../../../communal/Communal.hpp"


Daniel_Test_State::Daniel_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
	seed();
	state_name="daniel_test_state";

    world.init(Point(0, 0), test_layer.get_original_size());

	enemy_spawn_timer.create(60);
	bullet_manager=Bullet_Manager();
	bullet_manager.create(Point(world.active_left,world.active_top),Point(world.active_right,world.active_bottom));

	create_waves();

	load_sprites(imagehandler);
	player.create(Point(world.width / 2, world.active_bottom - 100), 1);
    player.load_ring(imagehandler);
	bullet_manager.set_player(player);
	wave_manager.create();
	wave_manager.set_testing_wave(-1,-1);
}

void Daniel_Test_State::load_sprites(Imagehandler& imagehandler){
    ui_handler.load_animations(imagehandler);
	player.load_animations(imagehandler);
	bullet_manager.load_animations(imagehandler);
	imagehandler.load_sprite(panel,"panel");
	imagehandler.load_sprite(panelx,"panelx");

	//panel.setPosition(1100,260);
	//panelx.setPosition(1100,260);
	//panel.setScale(1.5f,1.5f);
	//panelx.setScale(1.5f,1.5f);

	wave_manager.load_animations(imagehandler);
}

void Daniel_Test_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Daniel_Test_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	mouse.set_layer(test_layer);

	bullet_manager.update();
	update_player(mouse,keyboard,gamepad);

	if(enemy_spawn_timer.do_timer_loop()){
		add_bullets();
	}
	wave_manager.update();
    ui_handler.update(player.get_HealthRatio(), player.get_LineRatio());


	check_gamepad(gamepad);
	check_keyboard(keyboard);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/
	
	mouse.set_layer(background_layer);
Duration_Check::stop("-Platformer update");}

void Daniel_Test_State::render(sf::RenderWindow& window){Duration_Check::start("-Platformer render");

	Gamestate::render_background_layer(window);
	window.setView(test_layer);
	window.draw(bullet_manager);
	window.draw(wave_manager);
	//window.draw(panel);
	//window.draw(panelx);
	player.draw(world,window);
    render_bounds(window);
 	ui_handler.draw(window);
	Gamestate::render_gui_layer(window);
Duration_Check::stop("-Platformer render");}


void Daniel_Test_State::execute_data(Data_Packet data_p){

}
void Daniel_Test_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
}
void Daniel_Test_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(gamepad.was_just_pressed(GAMEPAD_A)){

	}

	if(gamepad.get_left_stick_y()>0){

	}else if(gamepad.get_left_stick_y()<0 ){
		;
	}else if(gamepad.get_left_stick_x()<0 ){

	}else if(gamepad.get_left_stick_x()>0 ){

	}*/
}

void Daniel_Test_State::update_player(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){
    // Player directional input
    float v_hor = keyboard.get_key('d').is_pressed() - keyboard.get_key('a').is_pressed();
    if (v_hor != 0.0f)
    {
        if (ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    else if (fabs(gamepad.get_left_stick_x()) > 0)
    {
        v_hor = gamepad.get_left_stick_x() / 100.f;
        if (!ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    float v_vert = keyboard.get_key('s').is_pressed() - keyboard.get_key('w').is_pressed();
    if (v_vert != 0.0f)
    {
        if (ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    else if (fabs(gamepad.get_left_stick_y()) > 0)
    {
        v_vert = gamepad.get_left_stick_y() / 100.f;
        if (!ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    Point input = Point(v_hor, v_vert);
    input.normalize();
   	player.update(world, input, keyboard.get_key('^').is_pressed() || gamepad.is_pressed(GAMEPAD_X));

    // Player button input
   	if (keyboard.get_key(' ').is_pressed())
    {
        if (!player.get_isLooping())
            player.start_loop();

        if (ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    else if (gamepad.is_pressed(GAMEPAD_A))
    {
        if (!player.get_isLooping())
            player.start_loop();

        if (!ui_handler.get_is_gamepad_active())
            ui_handler.toggle_control_scheme();
    }
    else
    {
        if (player.get_isLooping())
            player.validate_loop();
    }

    // Check collision of bullets with player
    Bullet_Vector bhp=bullet_manager.bullets_colliding_with_hitbox(player.get_hitbox());
	//if(mouse.is_clicked()){std::cout<<bhp.size();}
	for(int i=0;i<(int)bhp.size();i++){
		if(player.is_colliding(*bhp.at(i))){
            if (!bhp.at(i)->is_exploding()){
            	//std::cout<<"ASKDFA"<<std::endl;
                player.take_damage(bhp.at(i)->get_damage());
                if(player.get_HealthLeft()<=0){
                	send_data.push_back(Data_Packet("set_state",MANAGER,{"death_state"}));
                }
            }
			bhp.at(i)->set_exploding(true);
		}
	}

}

void Daniel_Test_State::render_bounds(sf::RenderWindow& window)
{
    // Create world bounds
    sf::VertexArray active_bounds(sf::LinesStrip, 5);
    active_bounds[0].position = sf::Vector2f(world.active_left, world.active_top);
    active_bounds[1].position = sf::Vector2f(world.active_left, world.active_bottom);
    active_bounds[2].position = sf::Vector2f(world.active_right, world.active_bottom);
    active_bounds[3].position = sf::Vector2f(world.active_right, world.active_top);
    active_bounds[4].position = sf::Vector2f(world.active_left, world.active_top);
    window.draw(active_bounds);
}

void Daniel_Test_State::create_waves(){
	/*std::vector<EnemyType> enemies;
	enemies.push_back(EnemyType::kEnemyStraight);
	enemies.push_back(EnemyType::kEnemyBurst);
	enemies.push_back(EnemyType::kEnemySine);
	enemies.push_back(EnemyType::kEnemyV);

	std::deque<Spawn_Data> spawn_data_one;
	std::deque<Spawn_Data> spawn_data_two;

	spawn_data_one.push_back(Spawn_Data(0, 16, Point(500, 100), 100));
	spawn_data_one.push_back(Spawn_Data(1, 16, Point(500, 200), 200));
	spawn_data_one.push_back(Spawn_Data(2, 16, Point(900, 300), 300));
	spawn_data_one.push_back(Spawn_Data(3, 16, Point(500, 400), 400));

	spawn_data_two.push_back(Spawn_Data(1, 16, Point(600, 100), 400));
	spawn_data_two.push_back(Spawn_Data(1, 16, Point(600, 200), 500));
	spawn_data_two.push_back(Spawn_Data(1, 16, Point(600, 300), 600));

	wave_one = Wave(enemies, false, spawn_data_one);
	wave_two = Wave(enemies, false, spawn_data_two);*/
	wave_manager = Wave_Manager(&bullet_manager, &player, &world, &ui_handler);

}

void Daniel_Test_State::add_bullets(){
	std::vector<Bullet_Blueprint> blueprints;

	//blueprints.push_back(Bullet_Blueprint(SINE,1,Point(-4,3),Point(800,20),5,&dummy_enemy));
	//blueprints.push_back(Bullet_Blueprint(HOMING,1,Point(-4,3),Point(800,20),5,&dummy_enemy));
	bullet_manager.add_bullets(blueprints);
}