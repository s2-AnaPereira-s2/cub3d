/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:26 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 18:30:54 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extension_check(char *path)
{
	int	size;

	size = ft_strlen(path);
	if (path[size - 4] != '.' || path[size - 3] != 'x'
		|| path[size - 2] != 'p' || path[size - 1] != 'm')
		return (1);
	return (0);
}

static int	skipspaces(char *path)
{
	int	size;
	int	i;

	size = ft_strlen(path);
	i = 0;
	while (i < size && (path[i] == ' ' || path[i] == '\t'))
		i++;
	if (i + 2 > size)
		return (-1);
	i += 2;
	while (i < size && (path[i] == ' ' || path[i] == '\t'))
	{
		i++;
	}
	return (i);
}

static int	pathname_check(char *path)
{
	int	size;
	int	i;

	size = ft_strlen(path);
	i = skipspaces(path);
	if (i < 0)
		return (1);
	i += 11;
	while (i < size - 5)
	{
		if (path[i] == ' ' || path[i] == '\t')
			return (1);
		if (!ft_isalnum(path[i]) && path[i] != '_' && path[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

int	bad_text_extension(t_game *game)
{
	if (ft_strlen(game->n_path) < 5 || ft_strlen(game->s_path) < 5
		|| ft_strlen(game->w_path) < 5 || ft_strlen(game->e_path) < 5)
		return (ft_putstr_fd("Error: Invalid path\n", 2),
			close_window(game), 1);
	else if (extension_check(game->n_path) || extension_check(game->s_path)
		|| extension_check(game->w_path) || extension_check(game->e_path))
		return (ft_putstr_fd("Error: Invalid texture extension\n", 2),
			close_window(game), 1);
	if (pathname_check(game->info[game->no_index])
		|| pathname_check(game->info[game->so_index])
		|| pathname_check(game->info[game->we_index])
		|| pathname_check(game->info[game->ea_index]))
		return (ft_putstr_fd("Error: Invalid path\n", 2),
			close_window(game), 1);
	return (0);
}
