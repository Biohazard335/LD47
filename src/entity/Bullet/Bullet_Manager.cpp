#include "Bullet_Manager.hpp"
#include "../../image/Imagehandler.hpp"

Bullet_Manager::Bullet_Manager():tree(Point(0,0),Point(1366,768),0){

}
void Bullet_Manager::create(Point top_left_p,Point bottom_right_p){
	tree = Bullet_Quadtree(top_left_p,bottom_right_p,0);
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
	//target.draw(tree,states);
} 



Bullet_Vector Bullet_Manager::bullets_colliding_with_hitbox(Circular_Hitbox hitbox_p){
	Bullet_Vector colliding_bullets=Bullet_Vector();
	//colliding_bullets=live_bullets;
	//colliding_bullets=tree.get_collidable_bullets(hitbox_p.get_center());
	colliding_bullets=tree.get_collidable_bullets_bound(hitbox_p.get_center()-Point(hitbox_p.get_radius(),hitbox_p.get_radius()),
		hitbox_p.get_center()+Point(hitbox_p.get_radius(),hitbox_p.get_radius()));
	return colliding_bullets;
}

void Bullet_Manager::capture_bullets(std::vector<Point> line_p){
    // Determine bounds of loop
    float top = line_p.front().get_y();
    float bot = line_p.front().get_y();
    float left  = line_p.front().get_x();
    float right = line_p.front().get_x();

    for (Point p : line_p)
    {
        top = p.get_y() < top ? p.get_y() : top;
        bot = p.get_y() > bot ? p.get_y() : bot;
        left  = p.get_x() < left  ? p.get_x() : left;
        right = p.get_x() > right ? p.get_x() : right;
    }

    // Check which bullets are in loop
    // Use bounds to determine which quadtree nodes to check, but all for now

    //LINE BOUNDARIES ARE WRONG
    live_bullets=tree.get_collidable_bullets_bound(Point(left,top),Point(right,bot));
   // std::cout<<"linebounds tl="<<left<<","<<top<<" br="<<right<<","<<bot<<std::endl;

    //live_bullets=tree.get_all_bullets();
    for (int i = 0; i < live_bullets.size(); i++)
    {
        if (live_bullets[i] == nullptr)
            continue;

        Point test = live_bullets[i]->get_center();
        int intersection_count = 0;

        
        for (int i = 0; i < line_p.size() - 2; i++)
        {
            Point A1 = line_p[i];
            Point A2 = line_p[i + 1];

            if (&A1 == nullptr || &A2 == nullptr)
                continue;

            // If segment is at least partially to the right of bullet
            if (A1.get_x() > test.get_x() || A2.get_x() > test.get_x())
            {
                if (sgn(A1.get_y() - test.get_y()) != sgn(A2.get_y() - test.get_y()))
                {
                    float intersect_x, intersect_y;
                    if (get_line_intersection(
                        test.get_x(), test.get_y(), test.get_x() + 10000, test.get_y(), A1.get_x(), A1.get_y(), A2.get_x(), A2.get_y(),
                        &intersect_x, &intersect_y))
                    {
                        intersection_count++;
                    }
                }
            }
        }
        

        if (intersection_count % 2 == 1)
        {// Odd count means inside shape
            live_bullets[i]->set_returning(true);
            //live_bullets[i]->set_removing(true);
            //live_bullets[i]->set_exploding(true);
            //live_bullets.erase(live_bullets.begin() + i);
        }
    }
}

void Bullet_Manager::add_bullets(std::vector<Bullet_Blueprint> blueprints_p){
	for(int i=0;i<(int)blueprints_p.size();i++){
		if(blueprints_p.at(i).type==LINEAR){
			//live_bullets.push_back(make_unique<Linear_Bullet>(linear_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Linear_Bullet>(linear_bullet.create_copy(blueprints_p.at(i))));

			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}else if(blueprints_p.at(i).type==SINE){
			//live_bullets.push_back(make_unique<Sine_Bullet>(sine_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Sine_Bullet>(sine_bullet.create_copy(blueprints_p.at(i))));
			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}else if(blueprints_p.at(i).type==HOMING){
			//live_bullets.push_back(make_unique<Homing_Bullet>(homing_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Homing_Bullet>(homing_bullet.create_copy(blueprints_p.at(i),player)));
			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}
		//std::cout<<endl;
	}
}

Bullet_Vector Bullet_Manager::getLiveBullets()
{
	return live_bullets;
}

void Bullet_Manager::update(){
	/*for(int j=0;j<live_bullets.size();j++){
		auto it= live_bullets.at(j);
		if(it->is_exploding()==false){
			Bullet_Vector collisions=tree.get_collidable_bullets(it->get_center());
			//Bullet_Vector collisions=live_bullets;
			for (int i=0;i<collisions.size();i++){
				if(it->is_colliding(*collisions.at(i))&&collisions.at(i)!=it){
					//it->set_exploding(true);
					//std::cout<<"erasing bullet at "<<center.get_x()<<", "<<center.get_y()<<std::endl;
				}
			}
		}
			
	}*/
	live_bullets=tree.get_all_bullets();
	tree.update();
}

void Bullet_Manager::update_player_position(Point pos_p){
	for(int i=0;i<(int)live_bullets.size();i++){
	}
}