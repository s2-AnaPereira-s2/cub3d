/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:36:18 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:36:25 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arrays(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_images(t_game *game)
{
	int	i;
	int	size;

	size = 4;
	i = 0;
	while (i < size)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

void	free_map(t_game *game)
{
	if (!game->map)
		return ;
	free(game->map);
	game->map = NULL;
}

void	free_paths(t_game *game)
{
	free(game->n_path);
	free(game->s_path);
	free(game->e_path);
	free(game->w_path);
}

int	close_window(t_game *game)
{
	free_images(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->map)
		free_map(game);
	if (game->info)
		free_arrays(game->info);
	if (game->f_rgb)
		free_arrays(game->f_rgb);
	if (game->c_rgb)
		free_arrays(game->c_rgb);
	free_paths(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_printf("...bye bye!!!\n");
	exit(0);
	return (0);
}
