#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>
#include "player.h"

class Enemy
{
public:
    bn::sprite_ptr sprite;
    bn::size size;
    bn::rect bounding_box;
    bn::fixed speed;

    Enemy(bn::fixed x_start_enemy, bn::fixed y_start_enemy, bn::size size);
    
    void update(Player &player);
    
private:
};