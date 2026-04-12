/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:39:27 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:39:29 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pn_pos(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\n' && game->map[y][x] != '\0')
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				player->dir = game->map[y][x];
				game->p += 1;
				game->px = x + 0.5f;
				game->py = y + 0.5f;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

static void	get_direction_ns(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

static void	get_direction_we(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

int	startup_1(t_game *game)
{
	if (bad_extension(game) || get_info(game))
		return (close_window(game), 1);
	get_dir_textures(game);
	if (bad_text_extension(game))
		return (close_window(game), 1);
	get_colors(game);
	return (0);
}

int	startup_2(t_game *game)
{
	if (get_map(game))
		return (close_window(game), 1);
	get_pn_pos(game, &game->player);
	if (map_check(game) || load_text_img(game))
		return (close_window(game), 1);
	get_direction_ns(&game->player);
	get_direction_we(&game->player);
	return (0);
}
