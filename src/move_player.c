
#include "cub3d.h"

static int	line_len_no_nl(char *line)
{
    int	len;

    len = 0;
    while (line[len] && line[len] != '\n')
        len++;
    return (len);
}

static char	map_at(t_game *game, int y, int x)
{
    int	len;

    if (y < 0 || y >= game->map_height)
        return (' ');
    len = line_len_no_nl(game->map[y]);
    if (x < 0 || x >= len)
        return (' ');
    return (game->map[y][x]);
}

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

static void	rotate_player(t_player *player, double rot)
{
    double	old_dir_x;
    double	old_plane_x;

    old_dir_x = player->dirX;
    player->dirX = player->dirX * cos(rot) - player->dirY * sin(rot);
    player->dirY = old_dir_x * sin(rot) + player->dirY * cos(rot);
    old_plane_x = player->planeX;
    player->planeX = player->planeX * cos(rot) - player->planeY * sin(rot);
    player->planeY = old_plane_x * sin(rot) + player->planeY * cos(rot);
}

void	update_movement(t_game *game)
{
    double  move_step;
    double  rot_step;

    move_step = MOVE_SPEED * 0.25;
    rot_step = move_step;
    if (game->key_w)
        move_player(game, game->player.dirX * move_step,
            game->player.dirY * move_step);
    if (game->key_s)
        move_player(game, -game->player.dirX * move_step,
            -game->player.dirY * move_step);
    if (game->key_d)
        move_player(game, game->player.planeX * move_step,
            game->player.planeY * move_step);
    if (game->key_a)
        move_player(game, -game->player.planeX * move_step,
            -game->player.planeY * move_step);
    if (game->key_left)
        rotate_player(&game->player, -rot_step);
    if (game->key_right)
        rotate_player(&game->player, rot_step);
}

int	keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        return (close_window(game));
    if (keycode == KEY_W)
        game->key_w = 1;
    if (keycode == KEY_A)
        game->key_a = 1;
    if (keycode == KEY_S)
        game->key_s = 1;
    if (keycode == KEY_D)
        game->key_d = 1;
    if (keycode == KEY_LEFT)
        game->key_left = 1;
    if (keycode == KEY_RIGHT)
        game->key_right = 1;
    return (0);
}

int	keyrelease(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->key_w = 0;
    if (keycode == KEY_A)
        game->key_a = 0;
    if (keycode == KEY_S)
        game->key_s = 0;
    if (keycode == KEY_D)
        game->key_d = 0;
    if (keycode == KEY_LEFT)
        game->key_left = 0;
    if (keycode == KEY_RIGHT)
        game->key_right = 0;
    return (0);
}
