#include "Bullet_Quadtree.hpp"
#include <iostream>


int Bullet_Quadtree::instance_cap=5;

//std::vector<sf::RectangleShape> Bullet_Quadtree::rectangles;


void Bullet_Quadtree::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(rect, states);
	if(children){
		target.draw(*top_left_child, states);
		target.draw(*top_right_child, states);
		target.draw(*bottom_left_child, states);
		target.draw(*bottom_right_child, states);
	}
}
Bullet_Quadtree::Bullet_Quadtree(Point tlb_p, Point brb_p,int depth_p){
	top_left_bound=tlb_p;
	bottom_right_bound=brb_p;
	this_depth=depth_p;
	Point size=brb_p-tlb_p;
	center=Point((size*0.5f)+top_left_bound);
	bullets= Bullet_Vector();

	//std::cout<<"new: d="<<this_depth<<" tl="<<top_left_bound.get_x()<<","<<top_left_bound.get_y()<<" br="<<bottom_right_bound.get_x()<<","<<bottom_right_bound.get_y()
		//<<" c="<<center.get_x()<<","<<center.get_y()<<std::endl;

	/*sf::RectangleShape rect(sf::Vector2f(size.get_x(),size.get_y()));*/
	rect=sf::RectangleShape(sf::Vector2f(size.get_x(),size.get_y()));
	rect.setPosition(tlb_p.get_x(),tlb_p.get_y());
	rect.setFillColor(sf::Color(0,0,0,0));
	rect.setOutlineColor(sf::Color(255,255,255));
	rect.setOutlineThickness(1.0f);
	//rectangles.push_back(rect);
}

void Bullet_Quadtree::update(){
	Bullet_Vector all =get_all_bullets();
	clear();
	for(int i=0;i<(int)all.size();i++){
		all.at(i)->update();
		if(!all.at(i)->is_removing()){
			insert(all.at(i));
		}
	}
}

void Bullet_Quadtree::clear(){
	if(children){
		top_left_child->clear();
		top_right_child->clear();
		bottom_right_child->clear();
		bottom_left_child->clear();
	}
	top_left_child=nullptr;
	top_right_child=nullptr;
	bottom_left_child=nullptr;
	bottom_right_child=nullptr;
	children=false;
	bullets.clear();
	//rectangles.clear();
}

bool Bullet_Quadtree::insert(std::shared_ptr<Bullet> bullet){
	//std::cout<<"current depth: "<<this_depth<<std::endl;
	if(bullet->get_center().get_x()>=top_left_bound.get_x() &&bullet->get_center().get_x()<=bottom_right_bound.get_x() 
		&&bullet->get_center().get_y()>=top_left_bound.get_y() &&bullet->get_center().get_y()<=bottom_right_bound.get_y()){
		if(children){
			//std::cout<<"children found"<<std::endl;
			insert_into_children(bullet);
		}else{
			//std::cout<<"NO children found"<<std::endl;
			if(bullets.size()<instance_cap){
				//std::cout<<"size limit not reached"<<std::endl;
				bullets.push_back(bullet);
			}else{
				//std::cout<<"size limit reached"<<std::endl;
				split();
				if(children){insert_into_children(bullet);}
			}
		}
	}else{
		return false;
	}
	//std::cout<<"success"<<std::endl<<std::endl;
}

void Bullet_Quadtree::insert_into_children(std::shared_ptr<Bullet> bullet){
	bool top=true;
	bool left=true;
	if(center.get_x() < bullet->get_center().get_x()){left=false;}
	if(center.get_y() < bullet->get_center().get_y()){top=false;}

	if(center.get_x()<bottom_right_bound.get_x() && center.get_y()<bottom_right_bound.get_y()){
		if(top&&left){top_left_child->insert(bullet);}
		else if(!top&&left){bottom_left_child->insert(bullet);}
		else if(top&&!left){top_right_child->insert(bullet);}
		else if(!top&&!left){bottom_right_child->insert(bullet);}
	}
}

void Bullet_Quadtree::split(){
	if(this_depth<max_depth){
		//std::cout<<"splitting"<<std::endl;
		children=true;
		top_left_child=std::make_unique<Bullet_Quadtree>(top_left_bound,center,this_depth+1);
		top_right_child=std::make_unique<Bullet_Quadtree>(Point(center.get_x(),top_left_bound.get_y()),
					Point(bottom_right_bound.get_x(),center.get_y()),this_depth+1);
		bottom_left_child=std::make_unique<Bullet_Quadtree>(Point(top_left_bound.get_x(),center.get_y()),
					Point(center.get_x(),bottom_right_bound.get_y()),this_depth+1);
		bottom_right_child=std::make_unique<Bullet_Quadtree>(center,bottom_right_bound,this_depth+1);

		for(int i=0;i<(int)bullets.size();i++){
			insert_into_children(bullets.at(i));
		}
		bullets.clear();
	}else{
		//std::cout<<"max depth reached"<<std::endl;

	}

	/*for(auto it = bullets.begin();it!=bullets.end();){
		insert_into_children(*it);
		it=bullets.erase(it);
	}*/
}

void Bullet_Quadtree::unsplit(){
	bullets=get_all_bullets();
	top_left_child=nullptr;
	top_right_child=nullptr;
	bottom_left_child=nullptr;
	bottom_right_child=nullptr;
	children=false;
}


Bullet_Vector Bullet_Quadtree::get_collidable_bullets(Point p_p){
	Bullet_Vector return_vector=Bullet_Vector();
//	if(p_p.get_x()>top_left_bound.get_x() && p_p.get_x()<bottom_right_bound.get_x() 
//		&& p_p.get_y()>top_left_bound.get_y() && p_p.get_y()<bottom_right_bound.get_y()){

	//std::cout<<this_depth<<" "<<bullets.size()<<std::endl;
		if(children){
			Bullet_Vector child_bullets;
			bool left=true;
			bool top=true;

			if(center.get_x() < p_p.get_x()){left=false;}
			if(center.get_y() < p_p.get_y()){top=false;}

			if(top&&left){child_bullets=top_left_child->get_collidable_bullets(p_p);}
			else if(!top&&left){child_bullets=bottom_left_child->get_collidable_bullets(p_p);}
			else if(top&&!left){child_bullets=top_right_child->get_collidable_bullets(p_p);}
			else if(!top&&!left){child_bullets=bottom_right_child->get_collidable_bullets(p_p);}

			return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
		}else{
			//std::cout<<"deepest: d="<<this_depth<<" BULLETS= "<<bullets.size()<<std::endl;
			return_vector=bullets;
		}
//	}
	return return_vector;

}
Bullet_Vector Bullet_Quadtree::get_collidable_bullets_bound(Point tl_p,Point br_p){
	Bullet_Vector return_vector=Bullet_Vector();
	if(colliding_with_bound(tl_p,br_p)){	
		if(children){
			Bullet_Vector child_bullets;
			if(top_left_child->colliding_with_bound(tl_p,br_p)){
				child_bullets=top_left_child->get_collidable_bullets_bound(tl_p,br_p);
				return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
				//top_left_child->rect.setOutlineColor(sf::Color::Red);
			}
			//else{top_left_child->rect.setOutlineColor(sf::Color::White);}
			if(top_right_child->colliding_with_bound(tl_p,br_p)){
				child_bullets=top_right_child->get_collidable_bullets_bound(tl_p,br_p);
				return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
				//top_right_child->rect.setOutlineColor(sf::Color::Red);
			}
			//else{top_right_child->rect.setOutlineColor(sf::Color::White);}
			if(bottom_left_child->colliding_with_bound(tl_p,br_p)){
				child_bullets=bottom_left_child->get_collidable_bullets_bound(tl_p,br_p);
				return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
				//bottom_left_child->rect.setOutlineColor(sf::Color::Red);
			}
			//else{bottom_left_child->rect.setOutlineColor(sf::Color::White);}
			if(bottom_right_child->colliding_with_bound(tl_p,br_p)){
				child_bullets=bottom_right_child->get_collidable_bullets_bound(tl_p,br_p);
				return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
				//bottom_right_child->rect.setOutlineColor(sf::Color::Red);
			}
			//else{bottom_right_child->rect.setOutlineColor(sf::Color::White);}
			
		}else{
			rect.setOutlineColor(sf::Color::Red);
			rect.setOutlineThickness(5.0f);
			return_vector=bullets;
		}
	}
	return return_vector;
}


bool Bullet_Quadtree::colliding_with_bound(Point tl_p,Point br_p){
	if(tl_p.get_x()>=bottom_right_bound.get_x() || top_left_bound.get_x()>=br_p.get_x())
		return false;
	if(tl_p.get_y()>=bottom_right_bound.get_y() || top_left_bound.get_y()>=br_p.get_y())
		return false;

	return true;
}


Bullet_Vector Bullet_Quadtree::get_all_bullets(){
	Bullet_Vector return_vector=bullets;
	if(children){
		Bullet_Vector child_bullets=top_left_child->get_all_bullets();
		return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
		child_bullets=top_right_child->get_all_bullets();
		return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
		child_bullets=bottom_right_child->get_all_bullets();
		return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
		child_bullets=bottom_left_child->get_all_bullets();
		return_vector.insert(return_vector.end(),child_bullets.begin(),child_bullets.end());
	}
	if(return_vector.size()<instance_cap-1 && this_depth>0 && children){
		unsplit();
	}
	return return_vector;	
}