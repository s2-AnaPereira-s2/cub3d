#include "cub3d.h"

int	keypress(int keycode, t_game *game)
{
	//int	move;

	game->np_x = game->p_x;
	game->np_y = game->p_y;
	if (game->game_win)
		return (close_window(game));
	if (keycode == KEY_RIGHT || keycode == 'd')
		game->np_x += 32;
	else if (keycode == KEY_LEFT || keycode == 'a')
		game->np_x -= 32;
	else if (keycode == KEY_UP || keycode == 'w')
		game->np_y -= 32;
	else if (keycode == KEY_DOWN || keycode == 's')
		game->np_y += 32;
	/*move = move_check(game);
	if (move == 0)
	{
		move_player(game, keycode);
		get_score(game);
		return (0);
	}*/
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
    t_player    player;
	int		size;

	if (argc <= 1)
		return (0);
	init_game(&game, &player);
	game.mlx = mlx_init();
	game.file_name = argv[1];
	size = get_map(&game);
	game.map_height = (size - 1) * 32;
	game.win_width = (game.line_len - 1) * 32;
	game.win_height = game.map_height + (3 * 32);
	if (window_check(&game))
		return (perror("Map bigger than screen!"), close_window(&game));
	game.win = mlx_new_window(game.mlx, game.win_width, 
			game.win_height, "Turtle");
	get_image(&game);
	get_helpers(&game, &player);
	if (map_check(&game))
		return (exit(0), 0);
	draw_map(&game);
	mlx_key_hook(game.win, keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
