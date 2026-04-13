/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:32 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/13 13:14:55 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	int	i;

	game->n_path = NULL;
	game->s_path = NULL;
	game->e_path = NULL;
	game->w_path = NULL;
	game->f_rgb = NULL;
	game->c_rgb = NULL;
	game->step = 0.0;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
}

void	init_game(t_game *game, t_player *player)
{
	ft_bzero(game, sizeof(t_game));
	game->f_index = -1;
	game->fd = -1;
	player->dir = ' ';
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	init_textures(game);
}

void	init_ray1(t_game *game, t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->win_width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)game->px;
	ray->map_y = (int)game->py;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_ray2(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->px - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->px) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->py - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->py) * ray->delta_dist_y;
	}
}

void	init_win_wh(t_game *game)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	game->win_width = screen_w;
	game->win_height = screen_h;
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
}
