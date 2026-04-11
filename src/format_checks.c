/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:26 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 18:43:03 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	colors_format(t_game *game)
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

static int	file_start_check(t_game *game)
{
	if (game->map_start < game->c_index || game->map_start < game->f_index
		|| game->map_start < game->no_index || game->map_start < game->so_index
		|| game->map_start < game->we_index || game->map_start < game->ea_index)
		return (1);
	return (0);
}

int	p_c_d_check(t_game *game)
{
	if (file_start_check(game))
		return (ft_putstr_fd("Error\nInvalid file order\n", 2),
			close_window(game), 1);
	if (colors_format(game))
		return (ft_putstr_fd("Error\nInvalid rgb colors numbers\n", 2),
			close_window(game), 1);
	if (game->f_num != 1 || game->c_num != 1
		|| game->no_num != 1 || game->so_num != 1
		|| game->we_num != 1 || game->ea_num != 1)
		return (ft_putstr_fd("Error\nInvalid colors/textures count\n", 2),
			close_window(game), 1);
	return (0);
}

int	bad_extension(t_game *game)
{
	int	size;
	int	i;
	int	check;

	size = ft_strlen(game->file_name);
	if (size < 11)
		return (ft_putstr_fd("Error\nBad file extension\n", 2),
			close_window(game), 1);
	else if (game->file_name[size - 4] != '.'
		|| game->file_name[size - 3] != 'c'
		|| game->file_name[size - 2] != 'u'
		|| game->file_name[size - 1] != 'b')
		return (ft_putstr_fd("Error\nBad file extension\n", 2),
			close_window(game), 1);
	i = 5;
	while (i < (size - 4))
	{
		check = ft_isalnum(game->file_name[i]);
		if (check == 1 && game->file_name[i] != '_'
			&& game->file_name[i] != '-')
			return (ft_putstr_fd("Error\nBad file extension\n", 2),
				close_window(game), 1);
		i++;
	}
	return (0);
}
