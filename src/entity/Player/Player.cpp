#include "Player.hpp"

void Player::load_ring(Imagehandler& image_handler)
{
    a_Ring = Animation("Player_Bod_Idle");
    a_Core = Animation("Player_Core_Idle");

    a_HappyCore = Animation("Player_Core_Smile");

    a_DeadCore = Animation("Player_Core_Ow");
    a_DeadRing = Animation("Player_Bod_Death");
    
    image_handler.load_animation(a_Ring);
    image_handler.load_animation(a_Core);
    image_handler.load_animation(a_HappyCore);
    image_handler.load_animation(a_DeadCore);
    image_handler.load_animation(a_DeadRing);

    a_Ring.set_looping(false);
    a_Core.set_looping(false);
    a_HappyCore.set_looping(false);
    a_DeadRing.set_looping(false);
    a_DeadCore.set_looping(false);

    float player_scale = 0.15f;

    a_Ring.set_position(get_center());
    a_Ring.scale(Point(player_scale, player_scale));
    a_Core.set_position(get_center());
    a_Core.scale(Point(player_scale, player_scale));

    a_HappyCore.scale(Point(player_scale, player_scale));
    a_DeadRing.scale(Point(player_scale, player_scale));
    a_DeadCore.scale(Point(player_scale, player_scale));
}

void Player::update(World_Data world, Point move, bool shifted)
{
    if (!b_isDead)
    {// LIVE!
        // Set movement based on vector
        movement = shifted ? move * f_PlayerSpd * 0.5f : move * f_PlayerSpd;

        // Keep player in screen
        Point next_p = get_center() + movement;
        if (next_p.get_x() < world.active_left + 16)
        {
            set_center(Point(world.active_left + 16, next_p.get_y()));
            next_p.set_x(world.active_left + 16);
            movement.set_x(0);
        }
        else if (next_p.get_x() > world.active_right - 16)
        {
            set_center(Point(world.active_right - 16, next_p.get_y()));
            next_p.set_x(world.active_right - 16);
            movement.set_x(0);
        }

        if (next_p.get_y() < world.active_top + 16)
        {
            set_center(Point(next_p.get_x(), world.active_top + 16));
            movement.set_y(0);
        }
        else if (next_p.get_y() > world.active_bottom - 16)
        {
            set_center(Point(next_p.get_x(), world.active_bottom - 16));
            movement.set_y(0);
        }

        // Move and reset movement vector
        Player::move();
        if (b_isSnappingLoop)
        {
            if (a_HappyCore.is_finished())
            {
                b_isSnappingLoop = false;
                a_HappyCore.start();
            }
            a_HappyCore.animate();
        }
        a_HappyCore.set_position(get_center());
        a_Core.set_position(get_center());
        a_Ring.set_position(get_center());
        a_Ring.set_rotation(a_Ring.get_rotation() + 5);
        movement = Point(0, 0);

        // Add points if looping
        if (b_isLooping && !b_isHoldingLoop)
        {
            // Don't add duplicate points
            if (f_LineLeft > 0 && get_center() != v_Line.back())
            {
                // Add current position
                v_Line.push_back(get_center());

                // Newest line segment
                Point B1 = v_Line[v_Line.size() - 2];
                Point B2 = v_Line.back();

                if (v_Line.size() > 3)
                {// Don't do it if line too short to intersect meaningfully
                    for (int i = 0; i < v_Line.size() - 3; i++)
                    {// Check all line segments except for last 2
                        float intersect_x;
                        float intersect_y;

                        Point A1 = v_Line[i];
                        Point A2 = v_Line[i + 1];

                        if (get_line_intersection(
                            A1.get_x(), A1.get_y(), A2.get_x(), A2.get_y(), B1.get_x(), B1.get_y(), B2.get_x(), B2.get_y(),
                            &intersect_x, &intersect_y))
                        {
                            v_Line[i] = Point(intersect_x, intersect_y);
                            v_Line.back() = Point(intersect_x, intersect_y);
                            v_Line.erase(v_Line.begin(), v_Line.begin() + i);

                            b_isHoldingLoop = true;
                            break;
                        }
                    }
                }

                f_LineLeft = shifted ? f_LineLeft - 0.005f : f_LineLeft - 0.01f;
            }
        }
        else if (!b_isHoldingLoop)
        {
            if (f_LineLeft < f_LineLimit)
            {
                f_LineLeft += 0.1f;
                if (f_LineLeft > f_LineLimit)
                    f_LineLeft = f_LineLimit;
            }
        }
    }
    else
    {// ...perish
        if (a_DeadCore.is_finished())
            b_isDeadOver = true;

        a_DeadCore.animate();
        a_DeadRing.animate();
    }
}

void Player::draw(World_Data world, sf::RenderWindow &window)
{
    // Create capture line
    sf::VertexArray points(sf::LinesStrip, 0);
    for (Point p : v_Line) {
        points.append(sf::Vertex(sf::Vector2f(p.get_x(), p.get_y()), sf::Color::White));
    }

    window.draw(points);
    if (b_isDead)
    {// Death anim
        window.draw(a_DeadRing.get_current_frame());
        window.draw(a_DeadCore.get_current_frame());
    }
    else if (b_isSnappingLoop)
    {// Happy looper
        window.draw(a_Ring.get_current_frame());
        window.draw(a_HappyCore.get_current_frame());
    }
    else
    {// Default
        window.draw(a_Ring.get_current_frame());
        window.draw(a_Core.get_current_frame());
    }
}

void Player::take_damage(float damage)
{
    f_HealthLeft -= damage;

    if (f_HealthLeft <= 0.0f)
    {
        f_HealthLeft = 0.0f;
        b_isDead = true;
        // Player die behaviour
        a_DeadCore.set_position(get_center());
        a_DeadRing.set_position(get_center());
    }
}

void Player::start_loop()
{
    b_isLooping = true;
    v_Line.clear();
    v_Line.push_back(get_center());
}

void Player::validate_loop() 
{
    b_isLooping = false;
    b_isHoldingLoop = false;

    if (v_Line.size() > 2 && v_Line.front() == v_Line.back())
    {
        // send to bullet manager
        p_BulletMan->capture_bullets(v_Line);
        b_isSnappingLoop = true;
    }

    v_Line.clear();
}