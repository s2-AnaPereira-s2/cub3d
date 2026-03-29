
#include "cub3d.h"

/*void	map_copy(t_game *game)
{
	int	y;

	y = 0;
	game->map_cpy = ft_calloc((game->map_height / 32) + 1, sizeof(char *));
	if (!game->map_cpy)
		return ;
	while (game->map[y])
	{
		game->map_cpy[y] = ft_strdup(game->map[y]);
		if (!game->map_cpy[y])
			return ;
		y++;
	}
}*/

void	get_pn_pos(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\n' && game->map[y][x] != '\0')
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				player->dir = game->map[y][x];
				game->p += 1;
				player->x = x + 0.5;
				player->y = y + 0.5;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	get_direction(t_player *player)
{
	if (player->dir == 'N')
	{
    	player->dirX = 0;
    	player->dirY = -1;
		player->planeX = 0.66;
    	player->planeY = 0;
	}
	else if (player->dir == 'S')
	{
    	player->dirX = 0;
    	player->dirY = 1;
		player->planeX = -0.66;
    	player->planeY = 0;
	}
	else if (player->dir == 'E')
	{
    	player->dirX = 1;
    	player->dirY = 0;
		player->planeX = 0;
    	player->planeY = 0.66;
	}
	else if (player->dir == 'W')
	{
    	player->dirX = -1;
    	player->dirY = 0;
		player->planeX = 0;
    	player->planeY = -0.66;
	}
}


int	get_helpers(t_game *game, t_player *player)
{
	get_info(game);
	get_map(game);
	//map_copy(game);
	get_pn_pos(game, player);
	get_direction(player);
	get_dir_textures(game);
	get_colors(game);
	return (0);
}

int	put_img_window(t_game *game, char *img, int x, int y)
{
	return (mlx_put_image_to_window(game->mlx, game->win, img, x, y));
}
