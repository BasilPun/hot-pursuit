#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>
#include <bn_vector.h>

#include "player.h"

class Enemy
{
public:
    bn::sprite_ptr sprite;
    bn::size size;
    bn::rect bounding_box;
    bn::fixed speed;
    bool isFirst;
    bn::fixed bouncer_x_speed;
    bn::fixed bouncer_y_speed;

    Enemy(bn::fixed x_start_enemy, bn::fixed y_start_enemy, bn::size size, bool isFirst, bn::fixed bouncer_x_speed, bn::fixed bouncer_y_speed);

    void update(Player &player);
    void bounce(bn::fixed &x_speed, bn::fixed &y_speed, bn::fixed MIN_X, bn::fixed MAX_X, bn::fixed MIN_Y, bn::fixed MAX_Y);

private:
};