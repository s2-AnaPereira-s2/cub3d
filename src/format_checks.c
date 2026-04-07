
#include "cub3d.h"

int p_c_d_check(t_game *game)
{
	if (game->f_num != 1 || game->c_num != 1 || game->no_num != 1 || game->so_num != 1 || game->we_num != 1 || game->ea_num != 1)
		return 1;
	return 0;
}

