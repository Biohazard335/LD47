#include "Wave.hpp"


void Wave::update(){
	for(int i=0;i<(int)spawn_data.size();i++){
		if(spawn_data.at(i).spawn_delay.do_timer_once()){
			enemies_to_spawn.push_back(spawn_data.at(i));
			spawn_data.erase(spawn_data.begin()+i);
			i--;
		}
	}
}