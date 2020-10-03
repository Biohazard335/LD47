#include "Horus_Test_State.hpp"
#include "../../../communal/Communal.hpp"


Horus_Test_State::Horus_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
	state_name="horus_test_state";
	load_sprites(imagehandler);
}

void Horus_Test_State::load_sprites(Imagehandler& imagehandler){
}

void Horus_Test_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Horus_Test_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	mouse.set_layer(test_layer);

	check_gamepad(gamepad);
	check_keyboard(keyboard);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);
Duration_Check::stop("-Platformer update");}

void Horus_Test_State::render(sf::RenderWindow& window){Duration_Check::start("-Platformer render");

	Gamestate::render_background_layer(window);
	window.setView(test_layer);

	Gamestate::render_gui_layer(window);
Duration_Check::stop("-Platformer render");}


void Horus_Test_State::execute_data(Data_Packet data_p){

}
void Horus_Test_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
}
void Horus_Test_State::check_gamepad(Gamepad& gamepad){
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