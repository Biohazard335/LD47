#include "Bullet_Manager.hpp"
#include "../../image/Imagehandler.hpp"

Bullet_Manager::Bullet_Manager(){

}

void Bullet_Manager::load_animations(Imagehandler& imagehandler){
	linear_bullet.load_animations(imagehandler);
	sine_bullet.load_animations(imagehandler);
	homing_bullet.load_animations(imagehandler);
	linear_bullet.scale_animations(Point(0.2f,0.2f));
	sine_bullet.scale_animations(Point(0.2f,0.2f));
	homing_bullet.scale_animations(Point(0.2f,0.2f));
}

void Bullet_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for(int i=0;i<(int)live_bullets.size();i++){		
		target.draw(*live_bullets.at(i), states);
	}
}



Bullet_Vector Bullet_Manager::bullets_colliding_with_hitbox(Circular_Hitbox hitbox_p){
	Bullet_Vector colliding_bullets;
	for(int i=0;i<(int)live_bullets.size();i++){
		if(live_bullets.at(i)->get_hitbox().is_colliding(hitbox_p)){
			colliding_bullets.push_back(live_bullets.at(i));
		}
	}
	return colliding_bullets;
}

void Bullet_Manager::capture_bullets(std::vector<Point> line_p){

}

void Bullet_Manager::add_bullets(std::vector<Bullet_Blueprint> blueprints_p){
	for(int i=0;i<(int)blueprints_p.size();i++){
		if(blueprints_p.at(i).type==LINEAR){
			live_bullets.push_back(make_unique<Linear_Bullet>(linear_bullet.create_copy(blueprints_p.at(i))));
		}else if(blueprints_p.at(i).type==SINE){
			live_bullets.push_back(make_unique<Sine_Bullet>(sine_bullet.create_copy(blueprints_p.at(i))));
		}else if(blueprints_p.at(i).type==HOMING){
			live_bullets.push_back(make_unique<Homing_Bullet>(homing_bullet.create_copy(blueprints_p.at(i))));
		}
	}
}

void Bullet_Manager::update(){
	for(auto it = live_bullets.begin();it!=live_bullets.end();){
		(*it)->update();
		Point center=(*it)->get_center();
		if(center.get_x()<-10||center.get_x()>1400||center.get_y()<-10||center.get_y()>800 || (*it)->is_removing()){
			it= live_bullets.erase(it);
			//std::cout<<"erasing bullet at "<<center.get_x()<<", "<<center.get_y()<<std::endl;
		}else{
			it++;
		}
	}
}

void Bullet_Manager::update_player_position(Point pos_p){
	for(int i=0;i<(int)live_bullets.size();i++){
	}
}