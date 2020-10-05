#include "Player.hpp"

void Player::scale_animations(Point scale_p)
{
	for (int i = 0; i < (int)animations.size(); i++) {
		animations.at(i).scale(scale_p);
	}
	s_Ring.setScale(sf::Vector2f(scale_p.get_x(), scale_p.get_y()));
}

void Player::update(World_Data world, Point move, bool shifted)
{
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
    movement = Point(0,0);

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


	s_Ring.setRotation(s_Ring.getRotation() + 1);
	s_Ring.setPosition(get_center().get_x(), get_center().get_y());
}

void Player::draw(World_Data world, sf::RenderWindow &window)
{
    // Create capture line
    sf::VertexArray points(sf::LinesStrip, 0);
    for (Point p : v_Line) {
        points.append(sf::Vertex(sf::Vector2f(p.get_x(), p.get_y()), sf::Color::White));
    }


	window.draw(s_Ring);
    window.draw(points);
    window.draw(*this);
}

void Player::take_damage(float damage)
{
    f_HealthLeft -= damage;

    if (f_HealthLeft <= 0.0f)
    {
        f_HealthLeft = 0.0f;
        // Player die behaviour
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
    }

    v_Line.clear();
}