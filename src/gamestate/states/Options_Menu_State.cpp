#include "Options_Menu_State.hpp"
#include "../../audio/Audiohandler.hpp"

Options_Menu_State::Options_Menu_State(Imagehandler& imagehandler):res_error_layer("res_error"),res_error_okay("okay", 650, 650, Data_Packet("okay",LOCAL),-1,-1,-1,-1){


	populate_fullscreen_resolutions();
	populate_windowed_resolutions();

	res_slider_swap = make_unique<Slider>(Slider("resolution",400,250,windowed_resolutions.size()-2,0,windowed_resolutions.size()-1,
		Data_Packet("set_resolution",LOCAL),-1,0,3,2,(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST | Slider::NO_VALUE)));

	/*display_type_swap = std::make_unique<Slider>(Slider("display type",400,350,0,0,1,Data_Packet("display_type",LOCAL),-1,3,5,-1,							
		(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST | Slider::NO_VALUE)));*/


	gui_layer_buttons.push_back(std::make_unique<Slider>(Slider("volume",400,150,0,100,Data_Packet("set_volume",LOCAL,{100}),-1,-1,1,-1,							//0
		(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST))));

	gui_layer_buttons.push_back(std::make_unique<Slider>(Slider("sfx volume",400,200,0,100,Data_Packet("set_sfx_volume",LOCAL,{100}),-1,0,2,-1,							//1
		(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST))));

	gui_layer_buttons.push_back(std::make_unique<Slider>(Slider("resolution",400,250,fullscreen_resolutions.size()-2,0,fullscreen_resolutions.size()-1,				//2
		Data_Packet("set_resolution",LOCAL),-1,1,4,3,(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST | Slider::NO_VALUE))));

	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("error", 1050, 235, Data_Packet("res_error",LOCAL),2,1,4,-1)));						//3
	gui_layer_buttons.at(3)->set_active(false);
	gui_layer_buttons.at(3)->set_visible(false);

	gui_layer_buttons.push_back(std::make_unique<Sprite_Button>(Sprite_Button("fullscreen","checkbox",0,400,285,Data_Packet("set_fullscreen",LOCAL),-1,2,5,-1)));	//4
	gui_layer_buttons.at(4)->set_togglable(true);
	gui_layer_buttons.at(4)->manually_set_on(true);

	gui_layer_buttons.push_back(std::make_unique<Slider>(Slider("display type",400,350,0,0,1,Data_Packet("display_type",LOCAL),-1,4,6,-1,							//5
		(Slider::ALIGN_BAR | Slider::ABS_NAME_DIST | Slider::NO_VALUE))));
	static_cast<Slider*>(gui_layer_buttons.at(5).get())->manually_set_value(0);

	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("apply", 100, 500, Data_Packet("apply",LOCAL),-1,5,-1,7)));								//6

	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("return", 500, 500, Data_Packet("return",LOCAL),6,5,-1,-1)));							//7



	state_name="options_menu";
	cri0=fullscreen_resolutions.size()-1;
	current_res_index=cri0;
	load_sprites(imagehandler);

	res_error_layer.set_active(false);

}

void Options_Menu_State::load_sprites(Imagehandler& imagehandler){
	for(unsigned int i=0;i<gui_layer_buttons.size();i++){
		imagehandler.load_button(gui_layer_buttons[i].get());
	}
	imagehandler.load_button(&res_error_okay);
	imagehandler.load_button(res_slider_swap.get());

	//imagehandler.load_sprite(background,"options_menu_background");
	imagehandler.load_sprite(res_error_grey,"options_menu_background");

	imagehandler.load_sf_text(title);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(3.0f);
	title.setString("Options");
	title.setPosition(100,50);

	imagehandler.load_sf_text(fullscreen);
	fullscreen.setCharacterSize(23);
	fullscreen.setFillColor(sf::Color::White);
	fullscreen.setOutlineColor(sf::Color::White);
	fullscreen.setOutlineThickness(1.0f);
	fullscreen.setString("fullscreen");
	fullscreen.setPosition(100,290);


	imagehandler.load_sf_text(display_type);
	display_type.setCharacterSize(23);
	display_type.setFillColor(sf::Color::White);
	display_type.setOutlineColor(sf::Color::White);
	display_type.setOutlineThickness(1.0f);
	display_type.setString("stretch to fit");
	display_type.setPosition(850,340);

	imagehandler.load_sf_text(resolution_text);
	resolution_text.setCharacterSize(23);
	resolution_text.setFillColor(sf::Color::White);
	resolution_text.setOutlineColor(sf::Color::White);
	resolution_text.setOutlineThickness(1.0f);
	resolution_text.setPosition(850,240);
	int x=0;
	int y=0;
	if(full){
		x=(int)fullscreen_resolutions.at(current_res_index).get_x();
		y=(int)fullscreen_resolutions.at(current_res_index).get_y();
	}else{
		x=(int)windowed_resolutions.at(current_res_index).get_x();
		y=(int)windowed_resolutions.at(current_res_index).get_y();
	}
	resolution_text.setString(to_string(x)+"X"+to_string(y));

	imagehandler.load_sf_text(res_error_text);
	res_error_text.setCharacterSize(20);
	res_error_text.setFillColor(sf::Color::White);
	res_error_text.setOutlineColor(sf::Color::White);
	res_error_text.setOutlineThickness(1.0f);
	res_error_text.setLineSpacing(2.0f);
	res_error_text.setString(	"\
							 The program has detected that the current fullscreen resolution\n\
							 option provided by your computer does not match the\n\
						 	actual resolution size that has been generated.\n\n\
						 	Most likely this is a result of using multiple monitors.\n\n\
						 	This is a known bug with SFML 2.5.1, the library I am using\n\
						 	to interface cross platform with different operating systems.\n\n\
						 	Your game should work just fine, when this error appears\n\
						 	it just means that the current resolution you have selected \n\
						 	in the menu is not the actual resolution the program is using.\n\n\
						 	If you do require a specific resolution \n\
						 	this bug should not affect windowed mode.\n\n\
						 	Apologies for the inconvenience!");
	res_error_text.setPosition(-100,50);
}


void Options_Menu_State::update(Mousey& mouse,Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-OM update");

	if(res_error_layer.is_active()){//res_error layer
		mouse.set_layer(res_error_layer);
		if(mouse.is_active()){
			//check_buttons(mouse, res_error_layer_buttons);
			//std::cout<<mouse.is_layer_valid()<<std::endl;
			res_error_okay.check_highlighted(mouse);
			if(res_error_okay.check_clicked(mouse)){
				res_error_layer.set_active(false);
			}
		}
		if(gamepad.is_active()){
			res_error_okay.manually_set_highlighted(true);
			gamepad.set_current_layer("res_error");
			if(gamepad.was_just_pressed(GAMEPAD_A)){
				execute_data(Data_Packet("okay",LOCAL));
			}
		}
	}else{
		gamepad.set_current_layer(gui_layer.get_layer_name());
	}

	Gamestate::update(mouse,keyboard,gamepad);
	Duration_Check::stop("-OM update");
}

void Options_Menu_State::render(sf::RenderWindow& window){
	Duration_Check::start("-OM render");
	Gamestate::render(window);
	//gui_layer additions
	window.draw(fullscreen);
	window.draw(display_type);
	window.draw(resolution_text);

	if(res_error_layer.is_active()){//res_error layer
		window.draw(res_error_grey);
		window.draw(res_error_text);
		//res_error_layer_buttons[0]->draw(window);
		res_error_okay.draw(window);
	}


	Duration_Check::stop("-OM render");
}

void Options_Menu_State:: execute_data(Data_Packet data){
	if(data.get_data_type()=="set_volume"){
		sf::Listener::setGlobalVolume(data.get_ints().at(0));
	}
	if(data.get_data_type()=="set_sfx_volume"){
		Audiohandler::set_volume(data.get_ints().at(0),sound_category::SFX);
	}
	if(data.get_data_type()=="display_type"){
		display_type_i=data.get_ints().at(0);
		if(display_type_i==0){
			display_type.setString("stretch to fit");
		}else if(display_type_i==1){
			display_type.setString("smart scale");
		}else if(display_type_i==2){
			display_type.setString("pixel perfect");
		}
	}
	if(data.get_data_type()=="set_fullscreen"){
		full=!full;
		int res_slider_index=get_gui_button_index("resolution");
		gui_layer_buttons.at(res_slider_index).swap(res_slider_swap);
		current_res_index=gui_layer_buttons.at(res_slider_index)->get_data().get_ints().at(0);
		int x=0;
		int y=0;
		if(full){
			x=(int)fullscreen_resolutions.at(current_res_index).get_x();
			y=(int)fullscreen_resolutions.at(current_res_index).get_y();
		}else{
			x=(int)windowed_resolutions.at(current_res_index).get_x();
			y=(int)windowed_resolutions.at(current_res_index).get_y();
		}
		resolution_text.setString(to_string(x)+"X"+to_string(y));
	}
	if(data.get_data_type()=="set_resolution"){
		current_res_index=data.get_ints().at(0);
		int x=0;
		int y=0;
		if(full){
			x=(int)fullscreen_resolutions.at(current_res_index).get_x();
			y=(int)fullscreen_resolutions.at(current_res_index).get_y();
		}else{
			x=(int)windowed_resolutions.at(current_res_index).get_x();
			y=(int)windowed_resolutions.at(current_res_index).get_y();
		}
		resolution_text.setString(to_string(x)+"X"+to_string(y));
	}
	if(data.get_data_type()=="apply"){
		if(current_res_index!=cri0 || full!=full0 ||display_type_i!=display_type_i0){

			if(display_type_i!=display_type_i0){
				Layer::set_display_type(static_cast<Layer::DISPLAY_TYPE>(display_type_i));
				display_type_i0=display_type_i;
			}
			if(full){
				Layer::set_new_resolution(fullscreen_resolutions.at(current_res_index).get_x(),fullscreen_resolutions.at(current_res_index).get_y());
			}else{
				Layer::set_new_resolution(windowed_resolutions.at(current_res_index).get_x(),windowed_resolutions.at(current_res_index).get_y());
			}

			Layer::set_fullscreen(full);

			cri0=current_res_index;
			send_data.push_back(Data_Packet("recreate_window",WINDOW,{full}));
			full0=full;
		}
	}
	if(data.get_data_type()=="return"){
		int res_slider_index=get_gui_button_index("resolution");
		if(full!=full0){
			gui_layer_buttons.at(res_slider_index).swap(res_slider_swap);
			full=full0;
			current_res_index=gui_layer_buttons.at(res_slider_index)->get_data().get_ints().at(0);
			int x=0;
			int y=0;
			if(full){
				x=(int)fullscreen_resolutions.at(current_res_index).get_x();
				y=(int)fullscreen_resolutions.at(current_res_index).get_y();
			}else{
				x=(int)windowed_resolutions.at(current_res_index).get_x();
				y=(int)windowed_resolutions.at(current_res_index).get_y();
			}
			resolution_text.setString(to_string(x)+"X"+to_string(y));
		}

		int fullscreen_index=get_gui_button_index("fullscreen");
		gui_layer_buttons.at(fullscreen_index)->manually_set_on(full);

		current_res_index=cri0;
		static_cast<Slider*>(gui_layer_buttons.at(res_slider_index).get())->manually_set_value(cri0);

		display_type_i=display_type_i0;
		if(display_type_i==0){
			display_type.setString("stretch to fit");
		}else if(display_type_i==1){
			display_type.setString("smart scale");
		}else if(display_type_i==2){
			display_type.setString("pixel perfect");
		}
		int display_type_index=get_gui_button_index("display type");
		static_cast<Slider*>(gui_layer_buttons.at(display_type_index).get())->manually_set_value(display_type_i0);

		send_data.push_back(Data_Packet("set_state",MANAGER,{previous_state}));
		int x=0;
		int y=0;
		if(full){
			x=(int)fullscreen_resolutions.at(current_res_index).get_x();
			y=(int)fullscreen_resolutions.at(current_res_index).get_y();
		}else{
			x=(int)windowed_resolutions.at(current_res_index).get_x();
			y=(int)windowed_resolutions.at(current_res_index).get_y();
		}
		resolution_text.setString(to_string(x)+"X"+to_string(y));
	}

	if(data.get_data_type()=="res_error"){
		res_error_layer.set_active(true);
	}

	if(data.get_data_type()=="okay"){
		res_error_layer.set_active(false);
	}

}

void Options_Menu_State::populate_fullscreen_resolutions(){
	int modes =sf::VideoMode::getFullscreenModes().size();
	fullscreen_resolutions.clear();
	for (int i=0;i<modes;i++){
		if(i>0){
			if(sf::VideoMode::getFullscreenModes().at(i).bitsPerPixel!=sf::VideoMode::getFullscreenModes().at(i-1).bitsPerPixel){
				break;
			}
		}
		fullscreen_resolutions.insert(fullscreen_resolutions.begin(),
			Point(sf::VideoMode::getFullscreenModes().at(i).width,sf::VideoMode::getFullscreenModes().at(i).height));
	}

}

void Options_Menu_State::populate_windowed_resolutions(){
	windowed_resolutions.push_back(Point(960,540));
	windowed_resolutions.push_back(Point(1024,576));
	windowed_resolutions.push_back(Point(1280,720));
	windowed_resolutions.push_back(Point(1366,768));
}

void Options_Menu_State::resolution_error(bool exists_p){
	int error_button_index=get_gui_button_index("error");
	gui_layer_buttons.at(error_button_index)->set_active(exists_p);
	gui_layer_buttons.at(error_button_index)->set_visible(exists_p);
}