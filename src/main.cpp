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
#include "bounding_box.h"

static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

bn::random random;

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    bn::fixed x_start = 44;
    bn::fixed y_start = 22;
    Player player = Player(x_start, y_start);

    // array of enemies
    static constexpr int MAX_ENEMIES = 5;
    bn::vector<Enemy, MAX_ENEMIES> Enemies = {};

    bool is_game_over = false;

    while (true)
    {
        if (!is_game_over)
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
                enemy.bounding_box = create_bounding_box(enemy.sprite, ENEMY_SIZE);
                // Reset the current score and player position if the player collides with enemy
                if (enemy.bounding_box.intersects(player.bounding_box))
                {
                    scoreDisplay.lives--;

                    if (scoreDisplay.lives > 0)
                    {
                        // player spawns at the start_x location
                        player.sprite.set_x(x_start);
                        player.sprite.set_y(y_start);

                        // enemy spawns in random location
                        enemy.sprite.set_x(random.get_unbiased_fixed(MIN_X, MAX_X));
                        enemy.sprite.set_y(random.get_unbiased_fixed(MIN_Y, MAX_Y));
                    }
                    else
                    {
                        // out of lives trigger game over state
                        is_game_over = true;
                        scoreDisplay.show_game_over();
                    }
                    break;
                }
            }
            // Game over: out of lives, fully reset score/lives (highscore presists)
            scoreDisplay.update();
        }
        else
        {
            // Game Over State: Wait for player to press START to restart
            if (bn::keypad::start_pressed())
            {
                scoreDisplay.resetScore(); // Resets score to 0 and lives back to 3

                player.sprite.set_x(x_start);
                player.sprite.set_y(y_start);

                Enemies = {};
                Enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MAX_X), random.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, true, random.get_unbiased_fixed(-0.8, 0.8), random.get_unbiased_fixed(-0.8, 0.8)));

                is_game_over = false; // Resume normal gameplay
            }
        }

        bn::core::update();
    }
}