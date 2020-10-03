#include "Gameplay_State.hpp"
#include "../../communal/Communal.hpp"


Gameplay_State::Gameplay_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
	state_name="gameplay_state";
	platform_map.load_from_file("../assets/maps/dry_run_map.map");
	platform_map.set_position(Point(0,0));
	load_sprites(imagehandler);
	player.create(platform_map.tile_coord_to_position(1,1),platform_map);
}

void Gameplay_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
	player.load_animations(imagehandler);
	
}

void Gameplay_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Gameplay_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	mouse.set_layer(test_layer);
	player.update(platform_map,keyboard,gamepad);
	test_layer.setCenter(player.get_center().get_x(),player.get_center().get_y());

	check_gamepad(gamepad);
	check_keyboard(keyboard);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);
Duration_Check::stop("-Platformer update");}

void Gameplay_State::render(sf::RenderWindow& window){Duration_Check::start("-Platformer render");

	Gamestate::render_background_layer(window);
	window.setView(test_layer);


	window.draw(platform_map);
	window.draw(player);
	Gamestate::render_gui_layer(window);
Duration_Check::stop("-Platformer render");}


void Gameplay_State::execute_data(Data_Packet data_p){

}
void Gameplay_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
}
void Gameplay_State::check_gamepad(Gamepad& gamepad){
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