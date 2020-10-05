#include "Window_Manager.hpp"
#include "../communal/Communal.hpp"
#include "../communal/Duration_Check.hpp"
#include <thread>

int Window_Manager::execution_fps =30;

Window_Manager::Window_Manager(){
	set_execution_fps(60);
	seed();
	videomode= sf::VideoMode::getFullscreenModes().at(0);
	window.create(videomode, "Whorl", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true); 
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);


	Layer::set_new_resolution(window.getSize().x,window.getSize().y);
	gamestate_manager.update_layer_resolutions();
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-(videomode.width/2),/*(sf::VideoMode::getDesktopMode().height/2)-(videomode.height/2)*/0));

}

void Window_Manager::set_execution_fps(int i_p){
	execution_fps=i_p;
	sleep_time=(chrono::milliseconds(1000)/execution_fps);
}

void Window_Manager::recieve_data(Data_Packet data_p){

	if(data_p.get_data_type()=="close"){
		Duration_Check::kill();
		window.close();
		open=false;
	}
	if(data_p.get_data_type()=="hide_mouse"){
		window.setMouseCursorVisible(false);
	}else if(data_p.get_data_type()=="unhide_mouse"){
		window.setMouseCursorVisible(true);
	}else if(data_p.get_data_type()=="recreate_window"){
		videomode= sf::VideoMode(Layer::get_current_res_x(), Layer::get_current_res_y(), sf::VideoMode::getFullscreenModes().at(0).bitsPerPixel);
		Duration_Check::start("changing resolution");
		if(!Layer::is_fullscreen()){
			window.create(videomode, "Whorl", sf::Style::Close);
			window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-(videomode.width/2),/*(sf::VideoMode::getDesktopMode().height/2)-(videomode.height/2)*/0));
		}else{
			window.create(videomode, "Whorl", sf::Style::Fullscreen);
		}
		incorrect_window_size_counter=iws_counter_max;
		gamestate_manager.update_layer_resolutions();
		gamestate_manager.resolution_error(false);
		Duration_Check::stop("changing resolution");
	}
}

void Window_Manager::update(){
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	Duration_Check::start("total");


	if(incorrect_window_size_counter==0){
		if(Layer::get_current_res_x()!=window.getSize().x ||Layer::get_current_res_y()!=window.getSize().y){
			//std::cout<<"Incorrect window size detected!"<<std::endl;
			Layer::set_new_resolution(window.getSize().x,window.getSize().y);
			gamestate_manager.update_layer_resolutions();
			gamestate_manager.resolution_error(true);
		}
		incorrect_window_size_counter=iws_counter_max;
	}else{
		incorrect_window_size_counter--;
	}

	gamestate_manager.update(window);
	gamestate_manager.render(window);

	while(gamestate_manager.has_send_data()){
		recieve_data(gamestate_manager.get_send_data());
	}

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	 	chrono::milliseconds duration = chrono::duration_cast<chrono::milliseconds>( (t2 - t1) );
	 	chrono::microseconds duration2 = chrono::duration_cast<chrono::microseconds>( (t2 - t1) );
	Duration_Check::stop("total");
	this_thread::sleep_for(sleep_time-duration);
}