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

char *trim_color (char *color)
{
	int i;
	int j;
	int len;
	char	*ns;

	len = line_len_no_nl(color);
    ns = malloc(len + 1);
    if (!ns)
    {
		return (NULL);
	}
	i = 0;
	j = 0;
	while (color[i] && color[i] != '\n')
	{
		if (color[i] == 'F' || color[i] == 'C'
			|| color[i] == ' ' || color[i] == '\t')
			i++;
		else
		{
			ns[j] = color[i];
			j++;
			i++;
		}
	}
	ns[j] = '\0';
	return (ns);
}

char *trim_path (char *path)
{
	int i;
	int j;
	int len;
	char *np;

	len = line_len_no_nl(path);
    np = malloc(len + 1);
    if (!np)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (path[i] && path[i] != '\n')
	{
		if (path[i] == ' ' || path[i] == '\t')
			i++;
		else
		{
			np[j] = path[i];
			j++;
			i++;
		}
	}
	np[j] = '\0';
	return (np);
}