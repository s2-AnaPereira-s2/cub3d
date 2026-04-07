#include "cub3d.h"

int	keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (close_window(game));
	if (keycode == KEY_W)
		game->key_w = 1;
	if (keycode == KEY_A)
		game->key_a = 1;
	if (keycode == KEY_S)
		game->key_s = 1;
	if (keycode == KEY_D)
		game->key_d = 1;
	if (keycode == KEY_LEFT)
		game->key_left = 1;
	if (keycode == KEY_RIGHT)
		game->key_right = 1;
	return (0);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = 0;
	if (keycode == KEY_A)
		game->key_a = 0;
	if (keycode == KEY_S)
		game->key_s = 0;
	if (keycode == KEY_D)
		game->key_d = 0;
	if (keycode == KEY_LEFT)
		game->key_left = 0;
	if (keycode == KEY_RIGHT)
		game->key_right = 0;
	return (0);
}