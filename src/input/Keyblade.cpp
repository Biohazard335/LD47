#include "Keyblade.hpp"
#include <iostream>


Keyblade::Keyblade(){
	keys= new Keyb[num_keys];
	for(int i=0;i<26;i++){
		keys[i]= Keyb(char(i+97),static_cast<sf::Keyboard::Key>(i));
	}
	for(int i=0;i<10;i++){
		keys[26+i]= Keyb(char(i+48),static_cast<sf::Keyboard::Key>(i+26));
	}
	keys[36]= Keyb('E',sf::Keyboard::Escape);
	keys[37]=Keyb('B',sf::Keyboard::BackSpace);
	keys[38]=Keyb(' ',sf::Keyboard::Space);
	keys[39]=Keyb('\n',sf::Keyboard::Return);
	keys[40]=Keyb('^',sf::Keyboard::LShift);
	keys[41]=Keyb('\t',sf::Keyboard::Tab);
	keys[42]=Keyb('@',sf::Keyboard::LControl);
}

void Keyblade::event_update(sf::Event& event){
	bool pressed=false;
	bool released=false;
	for(int i=0;i<num_keys;i++){
		if(event.key.code==keys[i].get_key_k()){
			(event.type==sf::Event::KeyPressed)?pressed=true:pressed=false;
			(event.type==sf::Event::KeyReleased)?released=true:released=false;
			//std::cout<<keys[i].get_key_c()<<pressed<<std::endl;
			keys[i].update(pressed);
			keys[i].update_released(released);
		}
	}
}
void Keyblade::update_jps(){
	for(int i=0;i<num_keys;i++){
		keys[i].update_jp();
	}
}

Keyb Keyblade::get_key(char c_p){
	for(int i=0;i<num_keys;i++){
		if(keys[i].get_key_c()==c_p){
			return keys[i];
		}
	}
	return Keyb('U',sf::Keyboard::Unknown);
}


Keyb Keyblade::get_index(int i_p){
	if(keys!=nullptr && i_p<num_keys && i_p>=0){
		return keys[i_p];
	}else{
		return Keyb('U',sf::Keyboard::Unknown);
	}
}