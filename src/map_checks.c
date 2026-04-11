/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:58 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:38:00 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	char_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			if (!is_valid_map_char(game->map[i][j]))
				return (ft_putstr_fd("Error\nWrong char in map\n", 2), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	tile_open_to_void(t_game *game, int y, int x)
{
	if (map_at(game, y - 1, x) == ' ' || map_at(game, y + 1, x) == ' '
		|| map_at(game, y, x - 1) == ' ' || map_at(game, y, x + 1) == ' ')
		return (1);
	return (0);
}

static int	row_is_open(t_game *game, int y)
{
	int		x;
	int		len;
	char	c;

	x = 0;
	len = line_len_no_nl(game->map[y]);
	while (x < len)
	{
		c = game->map[y][x];
		if (c == '0' && tile_open_to_void(game, y, x))
			return (1);
		x++;
	}
	return (0);
}

int	map_check(t_game *game)
{
	int	y;

	if (char_check(game))
		return (close_window(game), 1);
	if (game->p != 1)
		return (ft_putstr_fd("Error\nInvalid number of players\n", 2),
			close_window(game), 1);
	if (p_c_d_check(game))
		return (1);
	y = 0;
	while (game->map[y])
	{
		if (row_is_open(game, y))
			return (ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2),
				close_window(game), 1);
		y++;
	}
	return (0);
}
