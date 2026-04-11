/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:38:15 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:38:18 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_len_no_nl(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

char	map_at(t_game *game, int y, int x)
{
	int	len;

	if (y < 0 || y >= game->map_height)
		return (' ');
	len = line_len_no_nl(game->map[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (game->map[y][x]);
}

void	get_map_width(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != '\n')
			j++;
		if (game->map_width < j)
			game->map_width = j;
		i++;
	}
}

char	*trim_core(char *str, int skip_fc)
{
	int		i;
	int		j;
	char	*out;

	out = malloc(line_len_no_nl(str) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ' || str[i] == '\t'
			|| (skip_fc && (str[i] == 'F' || str[i] == 'C')))
			i++;
		else
		{
			out[j] = str[i];
			j++;
			i++;
		}
	}
	out[j] = '\0';
	return (out);
}
