#include "cub3d.h"

int	keypress(int keycode, t_game *game)
{

	game->np_x = game->p_x;
	game->np_y = game->p_y;
	if (keycode == KEY_RIGHT || keycode == 'd')
		game->np_x += 32;
	else if (keycode == KEY_LEFT || keycode == 'a')
		game->np_x -= 32;
	else if (keycode == KEY_UP || keycode == 'w')
		game->np_y -= 32;
	else if (keycode == KEY_DOWN || keycode == 's')
		game->np_y += 32;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
    t_player    player;
	if (argc <= 1)
		return (0);
	init_game(&game, &player);
	game.mlx = mlx_init();
	if (!game.mlx)
    	return (perror("mlx_init failed"), 1);
	game.file_name = argv[1];
	game.win_width = WIDTH;
	game.win_height = HEIGHT;
	game.win = mlx_new_window(game.mlx, game.win_width, 
			game.win_height, "Cub3d");
	if (!game.win)
    	return (perror("mlx_new_window failed"), 1);
	get_helpers(&game, &player);
	//mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.win, keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
