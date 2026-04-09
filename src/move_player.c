/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtinner <thtinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:35:20 by thtinner          #+#    #+#             */
/*   Updated: 2026/04/09 16:02:41 by thtinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move_to(t_game *game, double x, double y)
{
	char	cell;

	cell = map_at(game, (int)(y - PLAYER_RADIUS), (int)(x - PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y + PLAYER_RADIUS), (int)(x - PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y - PLAYER_RADIUS), (int)(x + PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_at(game, (int)(y + PLAYER_RADIUS), (int)(x + PLAYER_RADIUS));
	if (cell == '1' || cell == ' ')
		return (0);
	return (1);
}

static void	move_player(t_game *game, double vx, double vy)
{
	double	nx;
	double	ny;

	nx = game->px + vx;
	ny = game->py + vy;
	if (can_move_to(game, nx, game->py))
		game->px = nx;
	if (can_move_to(game, game->px, ny))
		game->py = ny;
}

static void	rotate_player(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

void	update_movement(t_game *game)
{
	if (game->key_w)
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->key_s)
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (game->key_d)
		move_player(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	if (game->key_a)
		move_player(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	if (game->key_left)
		rotate_player(&game->player, -ROT_SPEED);
	if (game->key_right)
		rotate_player(&game->player, ROT_SPEED);
}
