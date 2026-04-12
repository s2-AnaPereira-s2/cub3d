/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:38:45 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:38:47 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_start(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->info[i])
	{
		j = 0;
		while (game->info[i][j] == ' ' || game->info[i][j] == '\t')
			j++;
		if (game->info[i][j] == '1' || game->info[i][j] == '0'
			|| (game->info[i][j] == 'N' && game->info[i][j + 1] != 'O')
			|| (game->info[i][j] == 'S' && game->info[i][j + 1] != 'O')
			|| (game->info[i][j] == 'E' && game->info[i][j + 1] != 'A')
			|| (game->info[i][j] == 'W' && game->info[i][j + 1] != 'E'))
			return (i);
		i++;
	}
	return (-1);
}

static void	copy_map(t_game *game, int map_start)
{
	int	i;
	int	j;

	i = map_start;
	j = 0;
	while (j < game->map_height)
	{
		game->map[j] = game->info[i];
		i++;
		j++;
	}
	game->map[j] = NULL;
}

int	get_info(t_game *game)
{
	char	*line;

	game->info_size = get_length(game);
	if (game->info_size == 0)
		return (ft_putstr_fd("Error: empty map\n", 2), close_window(game), 1);
	game->info = ft_calloc(sizeof(char *), game->info_size + 1);
	if (!game->info)
		return (1);
	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (perror("Invalid file"), close_window(game), 1);
	game->info_size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		game->info[game->info_size++] = line;
		line = get_next_line(game->fd);
		if (!line)
			break ;
	}
	game->info[game->info_size] = NULL;
	pass_text_index(game);
	close(game->fd);
	return (0);
}

static int	is_text_color(char *s)
{
	int	j;

	j = 0;
	while (s[j] == ' ' || s[j] == '\t')
		j++;
	if ((s[j] == 'N' && s[j + 1] == 'O')
		|| (s[j] == 'S' && s[j + 1] == 'O')
		|| (s[j] == 'W' && s[j + 1] == 'E')
		|| (s[j] == 'E' && s[j + 1] == 'A')
		|| s[j] == 'F' || s[j] == 'C')
		return (1);
	return (0);
}

int	get_map(t_game *game)
{
	int	i;

	game->map_start = find_map_start(game);
	i = game->map_start;
	if (i < 0)
		return (ft_putstr_fd("Error: No map\n", 2), close_window(game), 1);
	while (game->info[i] && !is_text_color(game->info[i]))
	{
		game->map_height++;
		i++;
	}
	game->map = ft_calloc(sizeof(char *), game->map_height + 1);
	if (!game->map || game->map_height == 0)
		return (ft_putstr_fd("Error: No map\n", 2), close_window(game), 1);
	copy_map(game, game->map_start);
	get_map_width(game);
	return (0);
}
