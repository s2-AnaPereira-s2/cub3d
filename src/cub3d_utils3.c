/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:46:09 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/07/14 18:07:41 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			if (game->map[i][j] != '1' && game->map[i][j] != 'N' 
				&& game->map[i][j] != 'S' && game->map[i][j] != 'E' 
				&& game->map[i][j] != 'W' && game->map[i][j] != '0')
				return (perror("Wrong char in map"), close_window(game));
			j++;
		}
		i++;
	}
	return (0);
}

int	bad_extension(t_game *game)
{
	int	size;
	int	i;
	int	check;

	size = ft_strlen(game->file_name);
	if (size < 11)
		return (perror("Bad file extension"), 1);
	else if (game->file_name[size - 4] != '.' 
		|| game->file_name[size - 3] != 'c' 
		|| game->file_name[size - 2] != 'u' 
		|| game->file_name[size - 1] != 'b')
		return (perror("Bad file extension"), close_window(game));
	i = 5;
	while (i < (size - 4))
	{
		check = ft_isalnum(game->file_name[i]);
		if (check == 1 && game->file_name[i] != '_' 
			&& game->file_name[i] != '-')
			return (perror("Bad file extension"), close_window(game));
		i++;
	}
	return (0);
}
