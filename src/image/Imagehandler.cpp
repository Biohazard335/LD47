#include "Imagehandler.hpp"
#include "../tilemap/Tilemap.hpp"
#include <iostream>

Imagehandler::Imagehandler(){
	load();
}

void Imagehandler::load(){
	error_texture.loadFromFile("../assets/error/error_texture.png");
	error_texture.setSmooth(true);
	error_animation.load("../assets/error/error_animation.png",32,32,4,0,"error");


	menu_background.loadFromFile("../assets/image/menu_background.png");
	menu_background.setSmooth(true);

	text_input_box.loadFromFile("../assets/gui/text_input_box.png");
	text_input_box.setSmooth(true);
	text_input_cursor.loadFromFile("../assets/gui/text_input_cursor.png");
	text_input_cursor.setSmooth(true);

	slider_sheet.load("../assets/gui/slider_sheet.png",-1,-1,-1,-1,"slider_sheet");

	text_buttons.load("../assets/gui/text_buttons.png",150,40,2,1,"text_buttons");
	checkbox.load("../assets/gui/checkbox.png",40,40,3,1,"checkbox");
	checkbox.set_button_sheet(true);

	if(!font.loadFromFile("../assets/font/System_Breach_wide.ttf")){
		std::cout<<"ERROR! failed to load font";
	}else{
		/*cout<<"!: l,   t,  w,  h,  a";
		for(int i=97;i<123;i++){
			sf::Glyph g=font.getGlyph(i,30,false,0);
			cout<<"\n"<<char(i)<<": "<<g.bounds.left<<", "<<g.bounds.top<<", "<<g.bounds.width<<", "<<g.bounds.height<<", "<<g.advance;
		}*/
	}

	Tilemap::add_tileset("../assets/image/tilesets/default_tileset_buffer","default_tileset");

	load_animation_sheet("../assets/image/animations/default_player");
	load_animation_sheet("../assets/image/animations/circle_animations");
	load_animation_sheet("../assets/image/animations/bullets");
}

void Imagehandler::load_text_input_box(Text_Input_Box& tib){
	tib.set_font(font);
	tib.set_box_texture(text_input_box);
	tib.set_cursor_texture(text_input_cursor);
}



void Imagehandler::load_sprite(sf::Sprite& sprite, std::string name_p){
	if(name_p=="main_menu_background"){
		sprite.setTexture(menu_background,true);
	}else if(name_p=="pause_menu_background"){
		sprite.setTexture(menu_background,true);
	}else if(name_p=="core_game_background"){
		sprite.setTexture(core_game_background,true);
	}else if(name_p=="options_menu_background"){
		sprite.setTexture(menu_background,true);
	}else if(name_p=="lizerd"){
		sprite.setTexture(lizerd,true);
	}else if(name_p=="hotbar"){
		sprite.setTexture(hotbar,true);
	}
	else{
		std::cout<<"\nERROR: sprite not found: "<<name_p<<std::endl;
		sprite.setTexture(error_texture,true);
	}
}

void Imagehandler::load_animation(Animation& animation){
	for(int i=0;i<(int)animation_sheets.size();i++){
		if(animation_sheets.at(i)->check_for_blueprint(animation)){
			return;
		}
	}
	std::cout<<"\nERROR: animation not found: "<<animation.get_name()<<"\n";
	error_animation.load_animation(animation,0);
}

void Imagehandler::load_sprite_button(Sprite_Button& button){
	if(button.get_sheet_name()=="checkbox"){
		button.load_sprites(checkbox);
	}else{
		std::cout<<"\nERROR: button_sheet not found: "<<button.get_sheet_name()<<"\n";
	}
}

void Imagehandler::load_text_button(Text_Button& button){
	button.set_font(font);
	button.load_sprites(text_buttons);
}
void Imagehandler::load_slider(Slider& button){
	button.set_font(font);
	button.load_sprites(slider_sheet);
}


void Imagehandler::load_MEBL(MEBL& mebl){
	for(unsigned int i=0;i<mebl.get_list().size();i++){
		load_button(mebl.get_list().at(i).get());
	}
}

void Imagehandler::load_button(Button* button){
	if(button->get_type()==SPRITE_BUTTON){
		load_sprite_button(*static_cast<Sprite_Button*>(button));
	}else if(button->get_type()==TEXT_BUTTON){
		load_text_button(*static_cast<Text_Button*>(button));
	}else if(button->get_type()==M_E_B_L){
		load_MEBL(*static_cast<MEBL*>(button));
	}else if(button->get_type()==SLIDER){
		load_slider(*static_cast<Slider*>(button));
	}else{
		std::cout<<"ERROR: attempt to load invalid button type for: "<<button->get_data().get_data_type()<<std::endl;
	}
}

void Imagehandler::load_sf_text(sf::Text& text){
	text.setFont(font);
}

void Imagehandler::load_animation_sheet(std::string file_p){
	animation_sheets.push_back(std::make_unique<Animation_Sheet>(file_p));
}