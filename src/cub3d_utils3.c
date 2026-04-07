
#include "cub3d.h"

int get_text_index(t_game *game, int i)
{

	if (!ft_strncmp(game->info[i], "NO", 2))
		return (game->NO_index = i, game->NO_num++, 0);
	if (!ft_strncmp(game->info[i], "SO", 2))
		return (game->SO_index = i, game->SO_num++, 0);
	if (!ft_strncmp(game->info[i], "WE", 2))
		return (game->WE_index = i, game->WE_num++, 0);
	if (!ft_strncmp(game->info[i], "EA", 2))
		return (game->EA_index = i, game->EA_num++, 0);
	return 0;
}

void pass_text_index(t_game *game)
{
	int i;

	i = 0;
	while (game->info[i])
	{
		get_text_index(game, i);
		i++;
	}
	printf("\n%d - NO_num\n%d - SO_num\n%d - WE_num\n%d - EA_num\n", game->NO_num, game->SO_num, game->WE_num, game->EA_num);
}



