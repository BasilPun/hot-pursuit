#include "enemy.h"
#include "bn_math.h"
#include "bn_sprite_items_ghost.h"
#include "bounding_box.h"

Enemy::Enemy(bn::fixed x_start_enemy, bn::fixed y_start_enemy, bn::size size, bool isFirst, bn::fixed bouncer_x_speed, bn::fixed bouncer_y_speed) : sprite(bn::sprite_items::ghost.create_sprite(x_start_enemy, y_start_enemy)),
                                                                                                                                                    size(size),
                                                                                                                                                    bounding_box(create_bounding_box(sprite, size)),
                                                                                                                                                    speed(0.9),
                                                                                                                                                    isFirst(isFirst),
                                                                                                                                                    bouncer_x_speed(bouncer_x_speed),
                                                                                                                                                    bouncer_y_speed(bouncer_y_speed)
{
}

void Enemy::update(Player &player)
{
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

void Enemy::bounce(bn::fixed &x_speed, bn::fixed &y_speed, bn::fixed MIN_X, bn::fixed MAX_X, bn::fixed MIN_Y, bn::fixed MAX_Y)
{
    bn::fixed x = sprite.x();
    bn::fixed y = sprite.y();

    // Update x position by adding speed
    x += x_speed;
    y += y_speed;

    // If we've gone off the screen on the right
    if (x > MAX_X)
    {
        // Snap back to screen and reverse direction
        x = MAX_X;
        x_speed *= -1;
    }
    // If we've gone off the screen on the left
    if (x < MIN_X)
    {
        // Snap back to screen and reverse direction
        x = MIN_X;
        x_speed *= -1;
    }

    if (y > MAX_Y)
    {
        // Snap back to screen and reverse direction
        y = MAX_Y;
        y_speed *= -1;
    }
    // If we've gone off the screen on the left
    if (y < MIN_Y)
    {
        // Snap back to screen and reverse direction
        y = MIN_Y;
        y_speed *= -1;
    }

    sprite.set_x(x);
    sprite.set_y(y);
}