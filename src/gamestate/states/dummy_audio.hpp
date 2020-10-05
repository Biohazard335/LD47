#ifndef DUMMYAUDIO_HPP
#define DUMMYAUDIO_HPP

#include "../../audio/Noise_Maker.hpp"

class Dummy_Audio:public Noise_Maker{
public:
	Dummy_Audio(){
		add_sound("enemy_die",sound_category::SFX);
		add_sound("player_hit",sound_category::SFX);
	}
};

#endif