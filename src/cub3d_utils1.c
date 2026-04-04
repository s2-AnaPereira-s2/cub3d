
#include "cub3d.h"

void	get_pn_pos(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\n' && game->map[y][x] != '\0')
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				player->dir = game->map[y][x];
				game->p += 1;
				game->px = x + 0.5;
				game->py = y + 0.5;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	get_direction_NS(t_player *player)
{
	if (player->dir == 'N')
	{
    	player->dirX = 0;
    	player->dirY = -1;
		player->planeX = 0.66;
    	player->planeY = 0;
	}
	else if (player->dir == 'S')
	{
    	player->dirX = 0;
    	player->dirY = 1;
		player->planeX = -0.66;
    	player->planeY = 0;
	}
}

void	get_direction_WE(t_player *player)
{
	if (player->dir == 'E')
	{
    	player->dirX = 1;
    	player->dirY = 0;
		player->planeX = 0;
    	player->planeY = 0.66;
	}
	else if (player->dir == 'W')
	{
    	player->dirX = -1;
    	player->dirY = 0;
		player->planeX = 0;
    	player->planeY = -0.66;
	}
}

int	get_helpers(t_game *game, t_player *player)
{
	if (bad_extension(game))
		return (close_window(game), 1);
	get_info(game);
	get_map(game);
	get_pn_pos(game, player);
	if (map_check(game))
		return (close_window(game), 1);
	get_direction_NS(player);
	get_direction_WE(player);
	get_dir_textures(game);
	get_colors(game);
	return (0);
}

int	get_length(t_game *game)
{
	char	*line;
	int		size;

	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (perror("Wrong file"), close(game->fd));
	if (bad_extension(game))
		return (close(game->fd));
	size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
	return (size);
}
