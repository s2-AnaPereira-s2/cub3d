#include "cub3d.h"

static int	init_window_and_image(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (perror("mlx_init failed"), 1);
	init_win_wh(game);
	game->win = mlx_new_window(game->mlx,
			game->win_width, game->win_height, "Cub3d");
	if (!game->win)
		return (perror("mlx_new_window failed"), 1);
	game->screen.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	if (!game->screen.img)
		return (perror("mlx_new_image failed"), 1);
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
	if (init_window_and_image(&game))
		return (close_window(&game), 1);
	game.file_name = argv[1];
	get_helpers(&game, &game.player);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, keyrelease, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
