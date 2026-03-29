
#include "cub3d.h"


int	one_player_check(t_game *game)
{
	if (game->p != 1)
		return (1);
	return (0);
}

int	map_check(t_game *game)
{

	if (one_player_check(game))
		return (perror("More than one player"), close_window(game));
	return (0);
}
