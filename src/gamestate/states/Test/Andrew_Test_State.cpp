#include "Andrew_Test_State.hpp"
#include "../../../communal/Communal.hpp"



Andrew_Test_State::Andrew_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
/*	state_name="andrew_test_state";
    world.init(Point(0, 0), test_layer.get_original_size());

	if (!m_debug_font.loadFromFile("../assets/font/System_Breach_wide.ttf"))
	{
		std::cout << "Error Loading Font!";
	}

	m_debug_text.setFont(m_debug_font);

	m_bullet_manager = Bullet_Manager();
	m_bullet_manager.create(Point(world.active_left,world.active_top),Point(world.active_right,world.active_bottom));

	std::vector<EnemyType> enemies;
	enemies.push_back(EnemyType::kEnemyBoss);

	std::deque<Spawn_Data> spawn_data_one;
	std::deque<Spawn_Data> spawn_data_two;

	spawn_data_one.push_back(Spawn_Data(0, 0, Point(500, 100), 100));

	m_wave_one = Wave(enemies, false, spawn_data_one);
	m_wave_manager = Wave_Manager(&m_bullet_manager, &m_test_player, &world);


    ui_handler.load_animations(imagehandler);

	load_sprites(imagehandler);

	m_test_player.create(Point(500, 500), 2);

    uptime.restart();*/

}

void Andrew_Test_State::load_sprites(Imagehandler& imagehandler){
	/*m_bullet_manager.load_animations(imagehandler);
	m_test_player.load_animations(imagehandler);
	m_wave_manager.load_animations(imagehandler);
	m_test_player.scale_animations(Point(32.0f/310.0f,32.0f/310.0f));*/

}

void Andrew_Test_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Andrew_Test_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	/*Gamestate::update_gui_layer(mouse,keyboard,gamepad);

    check_gamepad(gamepad);
    check_keyboard(keyboard);

	mouse.set_layer(test_layer);
	
    float v_hor = keyboard.get_key('d').is_pressed() - keyboard.get_key('a').is_pressed();
    v_hor = fabs(gamepad.get_left_stick_x()) > 0 ? gamepad.get_left_stick_x() / 100.f : v_hor;
    float v_vert = keyboard.get_key('s').is_pressed() - keyboard.get_key('w').is_pressed();
    v_vert = fabs(gamepad.get_left_stick_y()) > 0 ? gamepad.get_left_stick_y() / 100.f : v_vert;
    Point input = Point(v_hor, v_vert);
    //input.normalize();

    m_test_player.update(world, input, keyboard.get_key('^').is_pressed() || gamepad.is_pressed(GAMEPAD_X));

    if (keyboard.get_key(' ').is_pressed() || gamepad.is_pressed(GAMEPAD_A))
    {
        if (!m_test_player.get_isLooping())
            m_test_player.start_loop();
    }
    else
    {
        if (m_test_player.get_isLooping())
            m_test_player.validate_loop();
    }

	bool spawn = mouse.is_clicked();


	if (spawn) {
		m_wave_manager.add_wave(m_wave_one);
		//m_wave_manager.add_wave(m_wave_two);
		//m_wave_manager.generate_waves();
		spawn = false;
	}

	m_wave_manager.update();

	m_bullet_manager.update();
	Bullet_Vector bullets_hitting_player = m_bullet_manager.bullets_colliding_with_hitbox(m_test_player.get_hitbox());
	for (int i = 0; i < (int)bullets_hitting_player.size(); i++) {
		if(m_test_player.is_colliding(*bullets_hitting_player.at(i))){
            if (!bullets_hitting_player.at(i)->is_exploding())
                m_test_player.take_damage(bullets_hitting_player.at(i)->get_damage());
			bullets_hitting_player.at(i)->set_exploding(true);
		}
	}

	int wave = m_wave_manager.get_current_wave();
	float wave_difficulty = m_wave_manager.get_wave_difficulty();

	m_debug_text.setString("Current Wave: " + std::to_string(wave) + "\nWave Difficulty: " + std::to_string(wave_difficulty));

    //m_test_player.take_damage(10);
    ui_handler.update(m_test_player.get_HealthRatio(), m_test_player.get_LineRatio());
	m_debug_text.setCharacterSize(12);
	m_debug_text.setFillColor(sf::Color::White);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);
Duration_Check::stop("-Platformer update");}

void Andrew_Test_State::render(sf::RenderWindow& window){Duration_Check::start("-Platformer render");
/*
	Gamestate::render_background_layer(window);
	window.setView(test_layer);
	window.draw(m_debug_text);

    // Create world bounds
    sf::VertexArray active_bounds(sf::LinesStrip, 5);
    active_bounds[0].position = sf::Vector2f(world.active_left, world.active_top);
    active_bounds[1].position = sf::Vector2f(world.active_left, world.active_bottom);
    active_bounds[2].position = sf::Vector2f(world.active_right, world.active_bottom);
    active_bounds[3].position = sf::Vector2f(world.active_right, world.active_top);
    active_bounds[4].position = sf::Vector2f(world.active_left, world.active_top);
    window.draw(active_bounds);

	window.draw(m_wave_manager);
	window.draw(m_bullet_manager);
	m_test_player.draw(world, window);

  ui_handler.draw(window);

	Gamestate::render_gui_layer(window);*/
Duration_Check::stop("-Platformer render");}


void Andrew_Test_State::execute_data(Data_Packet data_p){

}
void Andrew_Test_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
}
void Andrew_Test_State::check_gamepad(Gamepad& gamepad){
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