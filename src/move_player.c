
#include "cub3d.h"

static int	can_move_to(t_game *game, double x, double y)
{
    char	cell;

    cell = map_at(game, (int)y, (int)x);
    if (cell == '1' || cell == ' ')
        return (0);
    return (1);
}

static void	move_player(t_game *game, double vx, double vy)
{
    double	nx;
    double	ny;

    nx = game->px + vx;
    ny = game->py + vy;
    if (can_move_to(game, nx, game->py))
        game->px = nx;
    if (can_move_to(game, game->px, ny))
        game->py = ny;
}

void rotate_rl(t_player *player, int keycode)
{
    double oldDirX;
    double oldPlaneX;

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
}

int func_keypress(int keycode, t_game *game, t_player *player)
{
    double vx;
    double vy;
    
    if (keycode == KEY_W)
    {
        vx = player->dirX * MOVE_SPEED;
        vy = player->dirY * MOVE_SPEED;
        move_player(game, vx, vy);
    }
    if (keycode == KEY_S)
    {
        vx = - player->dirX * MOVE_SPEED;
        vy = - player->dirY * MOVE_SPEED;
        move_player(game, vx, vy);
    }
    if (keycode == KEY_A)
    {
        vx = - player->planeX * MOVE_SPEED;
        vy = - player->planeY * MOVE_SPEED;
        move_player(game, vx, vy);
    }
    if (keycode == KEY_D)
    {
        vx = player->planeX * MOVE_SPEED;
        vy = player->planeY * MOVE_SPEED;
        move_player(game, vx, vy);
    }
    if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
        rotate_rl(player, keycode);
    return (0);
}

int keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        return (close_window(game), 1);
    return (func_keypress(keycode, game, &game->player));
}