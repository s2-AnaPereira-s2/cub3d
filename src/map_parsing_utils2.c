/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:38:15 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:38:18 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_length(t_game *game)
{
	char	*line;
	int		size;

	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (perror("Invalid file"), close_window(game), 1);
	size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
	return (size);
}

char	*trim_color(char *color)
{
	return (trim_core(color, 1));
}

char	*trim_path(char *path)
{
	return (trim_core(path, 0));
}
