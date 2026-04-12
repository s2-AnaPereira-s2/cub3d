/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:48 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/09 15:37:50 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_window_and_image(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: mlx_init failed\n", 2),
			close_window(game), 1);
	init_win_wh(game);
	game->win = mlx_new_window(game->mlx,
			game->win_width, game->win_height, "Cub3d");
	if (!game->win)
		return (ft_putstr_fd("Error: mlx_new_window failed\n", 2),
			close_window(game), 1);
	game->screen.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	if (!game->screen.img)
		return (ft_putstr_fd("Error: mlx_new_image failed\n", 2),
			close_window(game), 1);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_length, &game->screen.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc <= 1)
		return (0);
	init_game(&game, &game.player);
	game.file_name = argv[1];
	if (startup_1(&game))
		return (close_window(&game), 1);
	if (init_window_and_image(&game))
		return (close_window(&game), 1);
	if (startup_2(&game))
		return (close_window(&game), 1);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, keyrelease, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
