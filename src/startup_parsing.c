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
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				player->dir = game->map[y][x];
				game->p += 1;
				game->px = x + 0.5f;
				game->py = y + 0.5f;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

static void	get_direction_ns(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

static void	get_direction_we(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

int	get_helpers(t_game *game, t_player *player)
{
	if (bad_extension(game) || get_info(game) || get_map(game))
		return (close_window(game), 1);
	get_pn_pos(game, player);
	get_colors(game);
	if (map_check(game))
		return (close_window(game), 1);
	get_direction_ns(player);
	get_direction_we(player);
	get_dir_textures(game);
	return (0);
}

int	get_length(t_game *game)
{
	char	*line;
	int		size;

	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (perror("Wrong file"), close(game->fd), close_window(game), 1);
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
