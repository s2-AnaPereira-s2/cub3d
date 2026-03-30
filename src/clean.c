
#include "cub3d.h"

// nothing has been cleaned. Program needs to check for leaks and close everything properly. I have to implement it yet!


/*
void	free_images(t_game *game)
{
	int	i;
	int	size;

	size = 11;
	if (!imgs->img)
		return ;
	i = 0;
	while (i < size)
	{
		if (imgs->img[i])
			mlx_destroy_image(game->mlx, imgs->img[i]);
		i++;
	}
	free(imgs->img);
	imgs->img = NULL;
}

void	free_map_cpy(t_game *game)
{
	int	i;

	if (!game->map_cpy)
		return ;
	i = 0;
	while (game->map_cpy[i])
	{
		free(game->map_cpy[i]);
		game->map_cpy[i] = NULL;
		i++;
	}
	free(game->map_cpy);
	game->map_cpy = NULL;
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game->map)
		return ;
	while (game->map && game->map[i])
	{
		free(game->map[i]);
		game->map[i] = NULL;
		i++;
	}
	free(game->map);
	free_map_cpy(game);
	game->map = NULL;
}*/

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);  // skip mlx_destroy_display for now just to make it work
	ft_printf("...bye bye!!!\n");
	exit(0);
	return (0);
}