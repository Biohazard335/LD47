#include "Audiohandler.hpp"
#include "Audiokey.hpp"

#include <iterator>
#include <iostream>



const int Audiohandler::other_size=226;
std::shared_ptr<Audiokey> Audiohandler::other_player[Audiohandler::other_size];
float Audiohandler::other_volume=1.0f;

const int Audiohandler::sfx_size=20;
std::shared_ptr<Audiokey> Audiohandler::sfx_player[Audiohandler::sfx_size];
float Audiohandler::sfx_volume=1.0f;

const int Audiohandler::dialogue_size=10;
std::shared_ptr<Audiokey> Audiohandler::dialogue_player[dialogue_size];
float Audiohandler::dialogue_volume=1.0f;

bool Audiohandler::volume_update=false;

void Audiohandler::instantiate_player(){
	for(int i=0;i<other_size;i++){
		other_player[i]=nullptr;
	}

	for(int i=0;i<sfx_size;i++){
		sfx_player[i]=nullptr;
	}

	for(int i=0;i<dialogue_size;i++){
		dialogue_player[i]=nullptr;
	}

}

void Audiohandler::load(){
	error_sound.loadFromFile("../assets/error/error_sound.wav");
	background_music.openFromFile("../assets/audio/music/Whorl.wav");
	background_music.play();
	background_music.setLoop(true);
	add_buffer("../assets/audio/bplayer_hit.wav","player_hit");
}
void Audiohandler::add_buffer(std::string file_p,std::string name_p){
	buffers.push_back(std::make_unique<Sound_Texture>(Sound_Texture(file_p,name_p)));
}
void Audiohandler::load_audiokey(Audiokey& key){
	for(int i=0;i<(int)buffers.size();i++){
		if(buffers.at(i)->get_name()==key.get_name()){
			key.set_buffer(buffers.at(i)->ref_buffer());
			return;
		}
	}
	std::cout<<"ERROR: unable to find sound: "<<key.get_name()<<std::endl;
}


void Audiohandler::set_background_music(std::string name_p){
	if(name_p=="Whorl"){
		background_music.openFromFile("../assets/audio/music/Whorl.wav");
	}else{
		std::cout<<"ERROR: invalid music name: "<<name_p<<std::endl;
	}
}

void Audiohandler::update(){
	for(int i=0;i<other_size;i++){
		if(other_player[i]!=nullptr){
			if(other_player[i]->sound.getStatus()!=sf::SoundSource::Playing){
				other_player[i]->is_playing=false;
				other_player[i]=nullptr;
			}else if(volume_update){
				other_player[i]->sound.setVolume(other_volume*global_volume_scale);
			}
		}
	}

	for(int i=0;i<sfx_size;i++){
		if(sfx_player[i]!=nullptr){
			if(sfx_player[i]->sound.getStatus()!=sf::SoundSource::Playing){
				sfx_player[i]->is_playing=false;
				sfx_player[i]=nullptr;
			}else if(volume_update){
				sfx_player[i]->sound.setVolume(sfx_volume*global_volume_scale);
			}
		}
	}

	for(int i=0;i<dialogue_size;i++){
		if(dialogue_player[i]!=nullptr){
			if(dialogue_player[i]->sound.getStatus()!=sf::SoundSource::Playing){
				dialogue_player[i]->is_playing=false;
				dialogue_player[i]=nullptr;
			}else if(volume_update){
				dialogue_player[i]->sound.setVolume(sfx_volume*global_volume_scale);
			}
		}
	}
}

void Audiohandler::change_gamestate(std::string state_p){
	current_state=state_p;
	for(int i=0;i<other_size;i++){
		if(other_player[i]!=nullptr){
			if(other_player[i]->get_state_of_origin()!=current_state){
				paused_by_manager.push_back(other_player[i]);
				other_player[i]->pause_sound();
				other_player[i]=nullptr;
			}
		}
	}

	for(int i=0;i<sfx_size;i++){
		if(sfx_player[i]!=nullptr){
			if(sfx_player[i]->get_state_of_origin()!=current_state){
				paused_by_manager.push_back(sfx_player[i]);
				sfx_player[i]->pause_sound();
				sfx_player[i]=nullptr;
			}
		}
	}

	for(int i=0;i<dialogue_size;i++){
		if(dialogue_player[i]!=nullptr){
			if(dialogue_player[i]->get_state_of_origin()!=current_state){
				paused_by_manager.push_back(dialogue_player[i]);
				dialogue_player[i]->pause_sound();
				dialogue_player[i]=nullptr;
			}
		}
	}

	
	for(auto it=paused_by_manager.begin();it!=paused_by_manager.end();){
		if((*it)->get_state_of_origin()==current_state){
			if((*it)->is_maker_valid()){
				add_sound_request(*it);
			}
			it=paused_by_manager.erase(it);
		}else{
			++it;
		}
	}
}

void Audiohandler::set_volume(float volume_p, sound_category::CATEGORY category_p){
	if(category_p==sound_category::OTHER){
		other_volume=volume_p;
	}else if(category_p==sound_category::SFX){
		sfx_volume=volume_p;
	}else if(category_p==sound_category::DIALOGUE){
		dialogue_volume=volume_p;
	}
	volume_update=true;
}




void Audiohandler::add_sound_request(std::shared_ptr<Audiokey> key){
	//std::cout<<"requesting sound "<<key->get_name()<<std::endl;
	if(key->get_category()==sound_category::OTHER){
		request_other(key);
	}else if(key->get_category()==sound_category::SFX){
		request_sfx(key);
	}else if(key->get_category()==sound_category::DIALOGUE){
		request_dialogue(key);
	}
}

void Audiohandler::request_other(std::shared_ptr<Audiokey> key){
	for(int i=0;i<other_size;i++){
		if(other_player[i]==nullptr){
			other_player[i]=key;
			other_player[i]->sound.play();
			other_player[i]->is_playing=true;
			return;
		}
	}
}
void Audiohandler::request_sfx(std::shared_ptr<Audiokey> key){
	//std::cout<<"requesting SFX "<<key->get_name()<<std::endl;
	for(int i=0;i<sfx_size;i++){
		if(sfx_player[i]==nullptr){
			sfx_player[i]=key;
			sfx_player[i]->sound.play();
			sfx_player[i]->is_playing=true;
			return;
		}
	}
}
void Audiohandler::request_dialogue(std::shared_ptr<Audiokey> key){
	for(int i=0;i<dialogue_size;i++){
		if(dialogue_player[i]==nullptr){
			dialogue_player[i]=key;
			dialogue_player[i]->sound.play();
			dialogue_player[i]->is_playing=true;
			return;
		}
	}
}