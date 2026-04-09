/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:39:04 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:39:06 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map_at(game, ray->map_y, ray->map_x) == '1')
			ray->hit = 1;
	}
}

void	raycast(t_game *game, t_player *player)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < game->win_width)
	{
		init_ray1(game, player, &ray, x);
		init_ray2(game, &ray);
		perform_dda(game, &ray);
		calculate_wall(game, &ray);
		draw_wall(game, &ray, x);
		x++;
	}
}
