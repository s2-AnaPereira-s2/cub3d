
#include "cub3d.h"

void	init_game(t_game *game, t_player *player)
{
	game->img_width = 0;
	game->img_height = 0;
	game->win_width = 0;
	game->win_height = 0;
	game->map_height = 0;
	game->tile_w = 0;
	game->tile_h = 0;
	game->line_len = 0;
	game->fd = -1;
	game->np_x = 0;
	game->np_y = 0;
	game->game_win = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->movements = 0;
	game->p = 0;
	game->map_cpy = NULL;
	game->map = NULL;
	game->img = NULL;
	game->mlx = NULL;
	game->win = NULL;
    player->x = 0.0;
	player->y = 0.0;
    player->dir = ' ';
    player->dirX = 0;
    player->dirY = 0;
    player->planeX = 0.00;
    player->planeY = 0.00;
}