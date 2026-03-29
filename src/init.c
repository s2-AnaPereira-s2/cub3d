
#include "cub3d.h"

void	init_game(t_game *game, t_player *player)
{
	game->img_width = 32;
	game->img_height = 32;
	game->win_width = 0;
	game->win_height = 0;
	game->map_height = 0;
	game->info_size = 0;
	game->fd = -1;
	game->p = 0;
	game->map_cpy = NULL;
	game->map = NULL;
	game->info = NULL;
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
	game->N_path = " ";
    game->S_path = " ";
	game->E_path = " ";
	game->W_path = " ";
	game->f_color = 0;
	game->c_color = 0;
}