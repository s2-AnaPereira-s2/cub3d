
#include "cub3d.h"

int func_keypress(int keycode, t_game *game, t_player *player)
{
    double new_x;
    double new_y;
    double buffer;
    double oldDirX;
    double oldPlaneX;

    buffer = 0.9;
    if (keycode == KEY_ESC)
        return (close_window(game), 1);
    if (keycode == KEY_W)
    {
        new_x = game->px + player->dirX * MOVE_SPEED;
        new_y = game->py + player->dirY * MOVE_SPEED;
    
        if (game->map[(int)(new_y + player->dirY * buffer)][(int)(new_x + player->dirX * buffer)] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }
    if (keycode == KEY_S)
    {
        new_x = game->px - player->dirX * MOVE_SPEED;
        new_y = game->py - player->dirY * MOVE_SPEED;

        if (game->map[(int)(new_y - player->dirY * buffer)][(int)(new_x - player->dirX * buffer)] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }
    if (keycode == KEY_A)
    {
        new_x = game->px - player->planeX * MOVE_SPEED;
        new_y = game->py - player->planeY * MOVE_SPEED;

        if (game->map[(int)(new_y - player->planeY * buffer)][(int)(new_x - player->planeX * buffer)] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }
    if (keycode == KEY_D)
    {
        new_x = game->px + player->planeX * MOVE_SPEED;
        new_y = game->py + player->planeY * MOVE_SPEED;

        if (game->map[(int)(new_y + player->planeY * buffer)][(int)(new_x + player->planeX * buffer)] != '1')
        {
            game->px = new_x;
            game->py = new_y;
        }
    }
    if (keycode == KEY_RIGHT)
    {
        oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-MOVE_SPEED) - player->dirY * sin(-MOVE_SPEED);
        player->dirY = oldDirX * sin(-MOVE_SPEED) + player->dirY * cos(-MOVE_SPEED);
        oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-MOVE_SPEED) - player->planeY * sin(-MOVE_SPEED);
        player->planeY = oldPlaneX * sin(-MOVE_SPEED) + player->planeY * cos(-MOVE_SPEED);
    }
    if (keycode == KEY_LEFT)
    {
        oldDirX = player->dirX;
        player->dirX = player->dirX * cos(MOVE_SPEED) - player->dirY * sin(MOVE_SPEED);
        player->dirY = oldDirX * sin(MOVE_SPEED) + player->dirY * cos(MOVE_SPEED);
        oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(MOVE_SPEED) - player->planeY * sin(MOVE_SPEED);
        player->planeY = oldPlaneX * sin(MOVE_SPEED) + player->planeY * cos(MOVE_SPEED);
    }
    return (0);
}

int keypress(int keycode, t_game *game)
{
    return (func_keypress(keycode, game, &game->player));
}