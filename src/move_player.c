
#include "cub3d.h"

static int	can_move_to(t_game *game, double x, double y)
{
	char	cell;

	cell = map_at(game, (int)(y - PLAYER_RADIUS), (int)(x - PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y + PLAYER_RADIUS), (int)(x - PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y - PLAYER_RADIUS), (int)(x + PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y + PLAYER_RADIUS), (int)(x + PLAYER_RADIUS));
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
	if (game->key_w)
		move_player(game, game->player.dirX * MOVE_SPEED,
			game->player.dirY * MOVE_SPEED);
	if (game->key_s)
		move_player(game, -game->player.dirX * MOVE_SPEED,
			-game->player.dirY * MOVE_SPEED);
	if (game->key_d)
		move_player(game, game->player.planeX * MOVE_SPEED,
			game->player.planeY * MOVE_SPEED);
	if (game->key_a)
		move_player(game, -game->player.planeX * MOVE_SPEED,
			-game->player.planeY * MOVE_SPEED);
	if (game->key_left)
		rotate_player(&game->player, -ROT_SPEED);
	if (game->key_right)
		rotate_player(&game->player, ROT_SPEED);
}