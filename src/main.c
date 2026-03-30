#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc <= 1)
		return (0);
	init_game(&game, &game.player);
	game.mlx = mlx_init();
	if (!game.mlx)
    	return (perror("mlx_init failed"), 1);
	game.win_width = WIDTH;
	game.win_height = HEIGHT;
	game.win = mlx_new_window(game.mlx, game.win_width, 
			game.win_height, "Cub3d");
	if (!game.win)
    	return (perror("mlx_new_window failed"), 1);
	game.screen.width = game.win_width;
	game.screen.height = game.win_height;
	game.file_name = argv[1];
	get_helpers(&game, &game.player);
	game.screen.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.screen.img)
		return (perror("mlx_new_image failed"), 1);
	game.screen.addr = mlx_get_data_addr(
		game.screen.img,
		&game.screen.bits_per_pixel,
		&game.screen.line_length,
		&game.screen.endian);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.win, keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	
	mlx_loop(game.mlx);
	return (0);
}
