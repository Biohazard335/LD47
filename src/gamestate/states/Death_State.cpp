#include "Death_State.hpp"

using namespace std;

Death_State::Death_State(Imagehandler& imagehandler){
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("quit", 550, 480, Data_Packet("set_state",MANAGER,{"main_menu"}),-1,-1,-1,-1)));
	load_sprites(imagehandler);
	state_name="Death";
}

void Death_State::load_sprites(Imagehandler& imagehandler){
	for(unsigned int i=0;i<gui_layer_buttons.size();i++){
		imagehandler.load_button(gui_layer_buttons[i].get());
	}
	//imagehandler.load_sprite(background,"Death_background");

	imagehandler.load_sf_text(title);
	title.setCharacterSize(100);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(1.0f);
	title.setString("You died.");
	title.setPosition(683-(int)(title.getLocalBounds().width/2),150);
}


void Death_State::update(Mousey& mouse,Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-PM update");
	Gamestate::update(mouse,keyboard,gamepad);
	Duration_Check::stop("-PM update");
}

void Death_State::render(sf::RenderWindow& window){
	Duration_Check::start("-PM render");
	Gamestate::render(window);
	Duration_Check::stop("-PM render");
}

void Death_State:: execute_data(Data_Packet data){

}
