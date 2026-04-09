/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtinner <thtinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:35:20 by thtinner          #+#    #+#             */
/*   Updated: 2026/04/09 16:03:07 by thtinner         ###   ########.fr       */
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
