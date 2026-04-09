#include "cub3d.h"

static int	find_map_start(t_game *game)
{
	int	i;

	i = 0;
	while (game->info[i] && game->info[i][0] != '1'
		&& game->info[i][0] != '0' && game->info[i][0] != ' ')
		i++;
	return (i);
}

static void	copy_map(t_game *game, int map_start)
{
	int	i;

	i = 0;
	while (game->info[map_start])
	{
		game->map[i] = game->info[map_start];
		map_start++;
		i++;
	}
	game->map[i] = NULL;
}

int	get_info(t_game *game)
{
	char	*line;

	game->info_size = get_length(game);
	if (game->info_size == 0)
		return (perror("empty map"), 1);
	game->info = ft_calloc(sizeof(char *), game->info_size + 1);
	if (!game->info)
		return (1);
	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (close(game->fd), perror("error to open file"), 1);
	game->info_size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		game->info[game->info_size++] = line;
		line = get_next_line(game->fd);
		if (!line)
			break ;
	}
	game->info[game->info_size] = NULL;
	pass_text_index(game);
	close(game->fd);
	return (0);
}

int	get_map(t_game *game)
{
	int	i;
	int	map_start;

	map_start = find_map_start(game);
	i = map_start;
	while (game->info[i])
	{
		game->map_height++;
		i++;
	}
	game->map = ft_calloc(sizeof(char *), game->map_height + 1);
	if (!game->map || game->map_height == 0)
		return (perror("No map"), 1);
	copy_map(game, map_start);
	get_map_width(game);
	return (0);
}
