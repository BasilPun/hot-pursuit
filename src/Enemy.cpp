#include "enemy.h"
#include "bn_math.h"
#include "bn_sprite_items_ghost.h"

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

Enemy::Enemy(bn::fixed x_start_enemy, bn::fixed y_start_enemy, bn::size size) : sprite(bn::sprite_items::ghost.create_sprite(x_start_enemy, y_start_enemy)),
                                                                         size(size),
                                                                         bounding_box(create_bounding_box(sprite, size)),
                                                                         speed(0.9)
{
}

void Enemy::update(Player &player)
{
    // 2d movement for enemy. with v_x, v_y logic.
    bn::fixed player_x = player.sprite.x();
    bn::fixed player_y = player.sprite.y();

    bn::fixed enemy_x = sprite.x();
    bn::fixed enemy_y = sprite.y();

    int y_diff = (player_y - enemy_y).integer();
    int x_diff = (player_x - enemy_x).integer();

    bn::fixed theta = bn::degrees_atan2(y_diff, x_diff);

    bn::fixed velocity_x = speed * bn::degrees_cos(theta);
    bn::fixed velocity_y = speed * bn::degrees_sin(theta);

    sprite.set_x(enemy_x + velocity_x);
    sprite.set_y(enemy_y + velocity_y);

    bounding_box = create_bounding_box(sprite, size);
}