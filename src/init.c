
#include "cub3d.h"

void	init_game(t_game *game, t_player *player)
{
	// MLX
	game->mlx = NULL;
	game->win = NULL;

	// Window
	game->win_width = 0;
	game->win_height = 0;

	// Map / parsing
	game->map_height = 0;
	game->map_width = 0;
	game->info_size = 0;
	game->fd = -1;
	game->map = NULL;
	game->map_cpy = NULL;
	game->info = NULL;

	// Player
	game->p = 0;
	game->px = 0.00;
	game->py = 0.00;

	// Player struct
	player->dir = ' ';
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0.0;
	player->planeY = 0.0;

	// Textures paths
	game->N_path = NULL;
	game->S_path = NULL;
	game->E_path = NULL;
	game->W_path = NULL;

	// Colors
	game->f_color = 0;
	game->c_color = 0;

	// Screen image
	game->screen.img = NULL;
	game->screen.addr = NULL;

	// Textures
	int i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
}