#include "Main_Menu_State.hpp"

using namespace std;

Main_Menu_State::Main_Menu_State(Imagehandler& imagehandler){
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("play", 550, 480, Data_Packet("set_state",MANAGER,{"gameplay_state"}),-1,-1,1,-1)));
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("options", 550, 560, Data_Packet("set_state",MANAGER,{"options_menu"}),-1,0,2,-1)));
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("close", 550, 640, Data_Packet("close",WINDOW),-1,1,-1,-1)));

	load_sprites(imagehandler);
	state_name="main_menu";
	//gui_layer.setCenter(300,400);
}

void Main_Menu_State::load_sprites(Imagehandler& imagehandler){
	for(unsigned int i=0;i<gui_layer_buttons.size();i++){
		imagehandler.load_button(gui_layer_buttons[i].get());
	}
	//imagehandler.load_sprite(background,"main_menu_background");

	imagehandler.load_sf_text(title);
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Red);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(3.0f);
	title.setString("");
	title.setPosition(683-(int)(title.getLocalBounds().width/2),50);

	imagehandler.load_sprite(game_title,"game_title");
	game_title.setPosition(180,130);
	imagehandler.load_sprite(o,"o");
	o.setScale(0.6f,0.6f);
	o.setPosition(600,130);
}

void Main_Menu_State::update(Mousey& mouse,Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-MM update");
	Gamestate::update(mouse,keyboard,gamepad);
	Duration_Check::stop("-MM update");
}

void Main_Menu_State::render(sf::RenderWindow& window){
	Duration_Check::start("-MM render");
	Gamestate::render(window);
	window.draw(game_title);
	window.draw(o);
	Duration_Check::stop("-MM render");
}

void Main_Menu_State:: execute_data(Data_Packet data){

}
