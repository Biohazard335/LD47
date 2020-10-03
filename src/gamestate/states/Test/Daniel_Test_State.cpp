#include "Daniel_Test_State.hpp"
#include "../../../communal/Communal.hpp"


Daniel_Test_State::Daniel_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
	state_name="daniel_test_state";
	load_sprites(imagehandler);

	player.create(Point(500,500),16);
	other.create(Point(600,600),16);
	enemy_spawn_timer.create(10);
}

void Daniel_Test_State::load_sprites(Imagehandler& imagehandler){
	player.load_animations(imagehandler);
	other.load_animations(imagehandler);
	bullet_manager.load_animations(imagehandler);
}

void Daniel_Test_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Daniel_Test_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	mouse.set_layer(test_layer);


	if(enemy_spawn_timer.do_timer_loop()){
		std::vector<Bullet_Blueprint> temp;
		int r=random(0,2);
		if(r==2){
			temp.push_back(Bullet_Blueprint(LINEAR,5,Point(-6,random(-6,6)),Point(1200,random(50,700)),1));
		}if(r==1){
			temp.push_back(Bullet_Blueprint(HOMING,5,Point(-6,random(-6,6)),Point(1200,random(50,700)),1));
		}if(r==0){
			temp.push_back(Bullet_Blueprint(SINE,5,Point(-6,random(-6,6)),Point(1200,random(50,700)),1));
		}
		bullet_manager.add_bullets(temp);
	}

	player.update(other,keyboard,gamepad);
	Bullet_Vector bullets_hitting_player=bullet_manager.bullets_colliding_with_hitbox(player.get_hitbox());
	for(int i=0;i<(int)bullets_hitting_player.size();i++){
		bullets_hitting_player.at(i)->set_exploding(true);
	}
	bullet_manager.update();

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
	window.draw(player);
	window.draw(other);
	//window.draw(linear_bullet);
	window.draw(bullet_manager);
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