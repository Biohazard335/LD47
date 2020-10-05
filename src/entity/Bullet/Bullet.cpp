#include "Bullet.hpp"
#include "../../communal/Communal.hpp"


void Bullet::update()
{
    if(exploding){
        current_animation_int=1;
        if(animations.at(1).is_finished()){
            removing=true;
        }
        animate();
        movement=Point(0,0);
    }else if (returning){
        if (!sender)
        {
            removing = true;
            returning = false;
        }
        else
        {
            // Get parent position
            Point home = sender->get_center();

            Point target = home - get_center();
            float distance = target.magnitude();

            if (distance < 5.f) {
                sender->take_damage(damage);
                exploding = true;
                returning = false;
                movement = Point(0, 0);
            }
            else {
                target.normalize();
                movement = target * speed;
            }
        }
    }
    int degrees=atan2_degrees(movement.get_y(),(movement.get_x()))+180;
    rotate_animations(degrees);
    move();
    movement=Point(0,0);
}
