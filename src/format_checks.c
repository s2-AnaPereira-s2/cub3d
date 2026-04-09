#include "cub3d.h"

int	colors_format(t_game *game)
{
	if ((ft_atoi(game->f_rgb[0]) < 0 || ft_atoi(game->f_rgb[0]) > 255)
		|| (ft_atoi(game->f_rgb[1]) < 0 || ft_atoi(game->f_rgb[1]) > 255)
		|| (ft_atoi(game->f_rgb[2]) < 0 || ft_atoi(game->f_rgb[2]) > 255))
		return (1);
	if ((ft_atoi(game->c_rgb[0]) < 0 || ft_atoi(game->c_rgb[0]) > 255)
		|| (ft_atoi(game->c_rgb[1]) < 0 || ft_atoi(game->c_rgb[1]) > 255)
		|| (ft_atoi(game->c_rgb[2]) < 0 || ft_atoi(game->c_rgb[2]) > 255))
		return (1);
	return (0);
}

int	p_c_d_check(t_game *game)
{
	if (colors_format(game))
		return (perror("Invalid rgb colors numbers"), close_window(game), 1);
	if (game->f_num != 1 || game->c_num != 1 || game->no_num != 1
		|| game->so_num != 1 || game->we_num != 1 || game->ea_num != 1)
		return (perror("Invalid number of colors or textures"),
			close_window(game), 1);
	return (0);
}
