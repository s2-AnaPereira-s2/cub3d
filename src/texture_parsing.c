/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:39:38 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:39:41 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_text_index(t_game *game, int i)
{
	int	j;

	j = 0;
	while (game->info[i][j] == ' ' || game->info[i][j] == '\t')
		j++;
	if (!ft_strncmp(game->info[i] + j, "NO", 2))
		return (game->no_index = i, game->no_num++, 0);
	if (!ft_strncmp(game->info[i] + j, "SO", 2))
		return (game->so_index = i, game->so_num++, 0);
	if (!ft_strncmp(game->info[i] + j, "WE", 2))
		return (game->we_index = i, game->we_num++, 0);
	if (!ft_strncmp(game->info[i] + j, "EA", 2))
		return (game->ea_index = i, game->ea_num++, 0);
	return (0);
}

void	pass_text_index(t_game *game)
{
	int	i;

	i = 0;
	while (game->info[i])
	{
		get_text_index(game, i);
		i++;
	}
}


