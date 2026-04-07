
#include "cub3d.h"

int p_c_d_check(t_game *game)
{
	if (game->f_num != 1 || game->c_num != 1 || game->NO_num != 1 || game->SO_num != 1 || game->WE_num != 1 || game->EA_num != 1)
		return 1;
	return 0;
}

