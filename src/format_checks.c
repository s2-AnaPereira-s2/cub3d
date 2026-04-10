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

static int file_start_check(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < (game->info_size - game->map_height))
	{
		if (game->info[i][0] != 'N' && game->info[i][0] != 'S' && game->info[i][0] != 'W' && game->info[i][0] != 'E' 
			&& game->info[i][0] != 'F' && game->info[i][0] != 'C' && game->info[i][0] != '\n' && game->info[i][0] != ' ' && game->info[i][0] != '\t')
			return 1;
		j = 0;
		while (game->info[i][j] == ' ' && game->info[i][j] == '\t')
			j++;
		if (game->info[i][j] != 'N' && game->info[i][j] != 'S' && game->info[i][j] != 'W' && game->info[i][j] != 'E' 
			&& game->info[i][j] != 'F' && game->info[i][0] != 'C' && game->info[i][j] != '\n')
			return 1;
		i++;
	}
	return 0;
}

int	p_c_d_check(t_game *game)
{
	if (file_start_check(game))
		return (perror("Invalid file order"), close_window(game), 1);
	if (colors_format(game))
		return (perror("Invalid rgb colors numbers"), close_window(game), 1);
	if (game->f_num != 1 || game->c_num != 1 || game->no_num != 1
		|| game->so_num != 1 || game->we_num != 1 || game->ea_num != 1)
		return (perror("Invalid number of colors or textures"), 
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
		return (perror("Bad file extension"), close_window(game), 1);
	else if (game->file_name[size - 4] != '.'
		|| game->file_name[size - 3] != 'c'
		|| game->file_name[size - 2] != 'u'
		|| game->file_name[size - 1] != 'b')
		return (perror("Bad file extension"), close_window(game), 1);
	i = 5;
	while (i < (size - 4))
	{
		check = ft_isalnum(game->file_name[i]);
		if (check == 1 && game->file_name[i] != '_'
			&& game->file_name[i] != '-')
			return (perror("Bad file extension"), close_window(game), 1);
		i++;
	}
	return (0);
}

