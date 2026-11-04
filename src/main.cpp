#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include "bn_math.h"
#include <bn_random.h>

#include "common_fixed_8x16_font.h"
#include "player.h"
#include "enemy.h"
#include "scoredisplay.h"

static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

bn::random random;

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    bn::fixed x_start = 44;
    bn::fixed y_start = 22;
    Player player = Player(x_start, y_start);

    // array of enemies
    static constexpr int MAX_ENEMIES = 5;
    bn::vector<Enemy, MAX_ENEMIES> Enemies = {};

    while (true)
    {

        player.update();

        if (scoreDisplay.score % 360 == 0 && (Enemies.size() < MAX_ENEMIES))
        {
            if (Enemies.size() == 0)
            {
                Enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MAX_X), random.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, true, random.get_unbiased_fixed(-0.8, 0.8), random.get_unbiased_fixed(-0.8, 0.8)));
            }
            else
            {
                Enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MAX_X), random.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, false, random.get_unbiased_fixed(-0.8, 0.8), random.get_unbiased_fixed(-0.8, 0.8)));
            }
        }

        for (Enemy &enemy : Enemies)
        {
            if (enemy.isFirst == true)
            {
                enemy.update(player);
            }
            else
            {
                // if not head honcho ghost,
                // become a bouncer
                enemy.bounce(enemy.bouncer_x_speed, enemy.bouncer_y_speed, MIN_X, MAX_X, MIN_Y, MAX_Y);
            }
            // Reset the current score and player position if the player collides with enemy
            if (enemy.bounding_box.intersects(player.bounding_box))
            {
                scoreDisplay.resetScore();

                // enemy spawns in random location
                enemy.sprite.set_x(random.get_unbiased_fixed(MIN_X, MAX_X));
                enemy.sprite.set_y(random.get_unbiased_fixed(MIN_Y, MAX_Y));
                // player spawns at the start_x location
                player.sprite.set_x(x_start);
                player.sprite.set_y(y_start);
                // reset array & spawn 1 as score doesnt seem to start from 0 or at least it doesnt count.
                Enemies = {};
                Enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MAX_X), random.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, true, random.get_unbiased_fixed(-0.8, 0.8), random.get_unbiased_fixed(-0.8, 0.8)));
            }
        }
        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}