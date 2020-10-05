#ifndef IMAGEHANDLER_HPP
#define IMAGEHANDLER_HPP

#include "Animation.hpp"
#include "Sprite_Sheet.hpp"
#include "Animation_Sheet.hpp"
#include "../gui/Sprite_Button.hpp"
#include "../gui/Text_Button.hpp"
#include "../gui/MEBL.hpp"
#include "../gui/Text_Input_Box.hpp"
#include "../gui/Slider.hpp"

class Imagehandler{
private:
	std::vector<std::unique_ptr<Animation_Sheet>> animation_sheets;

	sf::Texture error_texture;
	Animation_Sheet error_animation;

	sf::Texture menu_background;
	sf::Texture core_game_background;

	sf::Texture game_title;
	sf::Texture panel;
	sf::Texture o;
	sf::Texture panelx;

	sf::Texture text_input_box;
	sf::Texture text_input_cursor;

	Sprite_Sheet slider_sheet;

	Sprite_Sheet text_buttons;
	Sprite_Sheet checkbox;

	sf::Font font;

public:
	Imagehandler();
	void load();
	~Imagehandler(){
	}

	void load_sprite(sf::Sprite& sprite,std::string name_p);
	void load_text_button(Text_Button& button);
	void load_sprite_button(Sprite_Button& button);
	void load_MEBL(MEBL& button);
	void load_slider(Slider& button);
	void load_animation(Animation& animation);
	void load_text_input_box(Text_Input_Box& tib);
	void load_button(Button* button);
	void load_sf_text(sf::Text& text);

	void load_animation_sheet(std::string file_p);
};

#endif