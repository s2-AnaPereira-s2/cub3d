/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:38:24 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:43:09 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel(&game->screen, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_background_mini(t_game *game)
{
	int	y;
	int	x;
	int	color;

	color = 0x5C4033;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_square(game, MINI_OFFSET_X + x * TILE_SIZE,
				MINI_OFFSET_Y + y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	color;

	draw_background_mini(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width && x < line_len_no_nl(game->map[y]))
		{
			if (game->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x5C4033;
			draw_square(game, MINI_OFFSET_X + x * TILE_SIZE,
				MINI_OFFSET_Y + y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = MINI_OFFSET_X + (int)(game->px * TILE_SIZE) - (PLAYER_SIZE / 2);
	py = MINI_OFFSET_Y + (int)(game->py * TILE_SIZE) - (PLAYER_SIZE / 2);
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			put_pixel(&game->screen, px + j, py + i, 0xFF0000);
			j++;
		}
		i++;
	}
}
