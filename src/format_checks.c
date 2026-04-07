
#include "cub3d.h"

int colors_format(t_game *game)
{
	int f_r;
	int f_g;
	int f_b;
	int c_r;
	int c_g;
	int c_b;

	f_r = ft_atoi(game->f_rgb[0]);
	f_g = ft_atoi(game->f_rgb[1]);
	f_b = ft_atoi(game->f_rgb[2]);
	c_r = ft_atoi(game->c_rgb[0]);
	c_g = ft_atoi(game->c_rgb[1]);
	c_b = ft_atoi(game->c_rgb[2]);
	if ((f_r < 0 || f_r > 255) || (f_g < 0 || f_g > 255) || (f_b < 0 || f_b > 255))
		return 1;
	if ((c_r < 0 || c_r > 255) || (c_g < 0 || c_g > 255) || (c_b < 0 || c_b > 255))
		return 1;
	return 0;
}

int p_c_d_check(t_game *game)
{
	if (colors_format(game))
		return (perror("Invalid rgb colors numbers"), 1);
	if (game->f_num != 1 || game->c_num != 1 || game->NO_num != 1 || game->SO_num != 1 || game->WE_num != 1 || game->EA_num != 1)
		return (perror("Invalid number of colors or textures"), 1);
	return 0;
}

