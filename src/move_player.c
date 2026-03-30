
#include "cub3d.h"

//Its not rotating, I need to fix keys. Also not working with arrows.

int func_keypress(int keycode, t_game *game, t_player *player)
{
    double new_x;
    double new_y;

    if (keycode == KEY_W)
    {
        new_x = game->px + player->dirX * MOVE_SPEED;
        new_y = game->py + player->dirY * MOVE_SPEED;

        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }

    if (keycode == KEY_S)
    {
        new_x = game->px - player->dirX * MOVE_SPEED;
        new_y = game->py - player->dirY * MOVE_SPEED;

        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }

    if (keycode == KEY_A)
    {
        new_x = game->px - player->planeX * MOVE_SPEED;
        new_y = game->py - player->planeY * MOVE_SPEED;

        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }

    if (keycode == KEY_D)
    {
        new_x = game->px + player->planeX * MOVE_SPEED;
        new_y = game->py + player->planeY * MOVE_SPEED;

        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }

    if (keycode == KEY_RIGHT)
    {
        double oldDirX = player->dirX;

        player->dirX = player->dirX * cos(-ROT_SPEED) - player->dirY * sin(-ROT_SPEED);
        player->dirY = oldDirX * sin(-ROT_SPEED) + player->dirY * cos(-ROT_SPEED);

        double oldPlaneX = player->planeX;

        player->planeX = player->planeX * cos(-ROT_SPEED) - player->planeY * sin(-ROT_SPEED);
        player->planeY = oldPlaneX * sin(-ROT_SPEED) + player->planeY * cos(-ROT_SPEED);
    }

    if (keycode == KEY_LEFT)
    {
        double oldDirX = player->dirX;

        player->dirX = player->dirX * cos(ROT_SPEED) - player->dirY * sin(ROT_SPEED);
        player->dirY = oldDirX * sin(ROT_SPEED) + player->dirY * cos(ROT_SPEED);

        double oldPlaneX = player->planeX;

        player->planeX = player->planeX * cos(ROT_SPEED) - player->planeY * sin(ROT_SPEED);
        player->planeY = oldPlaneX * sin(ROT_SPEED) + player->planeY * cos(ROT_SPEED);
    }
    return (0);
}

int keypress(int keycode, t_game *game)
{
    return (func_keypress(keycode, game, &game->player));
}