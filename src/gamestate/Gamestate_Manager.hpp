#ifndef GAMESTATE_MANAGER_HPP
#define GAMESTATE_MANAGER_HPP


#include "Gamestate.hpp"
#include "states/Main_Menu_State.hpp"
#include "states/Options_Menu_State.hpp"
#include "states/Gameplay_State.hpp"
#include "states/Test/Andrew_Test_State.hpp"
#include "states/Test/Horus_Test_State.hpp"
#include "states/Test/Daniel_Test_State.hpp"
#include "states/Pause_Menu_State.hpp"
#include "states/Death_State.hpp"
#include "../audio/Audiohandler.hpp"
#include "../input/Gamepad.hpp"


class Gamestate_Manager{
private:
	Gamestate* current_state;
	Main_Menu_State* main_menu_state;
	Pause_Menu_State* pause_menu_state;
	Options_Menu_State* options_menu_state;
	Gameplay_State* gameplay_state;
	Andrew_Test_State* andrew_test_state;
	Horus_Test_State* horus_test_state;
	Daniel_Test_State* daniel_test_state;
	Death_State* death_state;

	Imagehandler imagehandler;
	Audiohandler audiohandler;

	Mousey mouse;
	Keyblade keyboard;
	Gamepad gamepad;

	std::vector<Data_Packet> send_data;

	bool set_state(Data_Packet);

	void receive_data(Data_Packet);

public:

	void render(sf::RenderWindow&);
	void update(sf::RenderWindow&);

	Gamestate_Manager();
	~Gamestate_Manager(){
		delete main_menu_state;
		delete gameplay_state;
		delete pause_menu_state;
		delete options_menu_state;
		delete daniel_test_state;
		delete andrew_test_state;
		delete horus_test_state;
		delete death_state;
	}

	Data_Packet get_send_data(){
		if(send_data.size()>0){
			Data_Packet tmp=send_data.at(0);
			send_data.erase(send_data.begin());
			return tmp;
		}else{
			return Data_Packet();
		}
	}
	bool has_send_data(){
		return(send_data.size()>0);
	}	

	void resolution_error(bool exists_p){
		options_menu_state->resolution_error(exists_p);
	}

	void update_layer_resolutions();

	void reset_game(){
		delete gameplay_state;
		gameplay_state = new Gameplay_State(imagehandler,audiohandler);
	}
};

#endif