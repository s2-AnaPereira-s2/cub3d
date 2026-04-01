
#include "cub3d.h"

static int	line_len_no_nl(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

static char	map_at(t_game *game, int y, int x)
{
	int	len;

	if (y < 0 || y >= game->map_height)
		return (' ');
	len = line_len_no_nl(game->map[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (game->map[y][x]);
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	char_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			if (!is_valid_map_char(game->map[i][j]))
				return (perror("Wrong char in map"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	bad_extension(t_game *game)
{
	int	size;
	int	i;
	int	check;

	size = ft_strlen(game->file_name);
	if (size < 11)
		return (perror("Bad file extension"), 1);
	else if (game->file_name[size - 4] != '.' 
		|| game->file_name[size - 3] != 'c' 
		|| game->file_name[size - 2] != 'u' 
		|| game->file_name[size - 1] != 'b')
		return (perror("Bad file extension"), 1);
	i = 5;
	while (i < (size - 4))
	{
		check = ft_isalnum(game->file_name[i]);
		if (check == 1 && game->file_name[i] != '_' 
			&& game->file_name[i] != '-')
			return (perror("Bad file extension"), 1);
		i++;
	}
	return (0);
}

int	one_player_check(t_game *game)
{
	if (game->p != 1)
		return (1);
	return (0);
}

static int	tile_open_to_void(t_game *game, int y, int x)
{
	if (map_at(game, y - 1, x) == ' ' || map_at(game, y + 1, x) == ' '
		|| map_at(game, y, x - 1) == ' ' || map_at(game, y, x + 1) == ' ')
		return (1);
	return (0);
}

static int	row_is_open(t_game *game, int y)
{
	int		x;
	int		len;
	char	c;

	x = 0;
	len = line_len_no_nl(game->map[y]);
	while (x < len)
	{
		c = game->map[y][x];
		if (is_walkable(c) && tile_open_to_void(game, y, x))
			return (1);
		x++;
	}
	return (0);
}

int	map_check(t_game *game)
{
	int	y;

	if (char_check(game))
		return (1);
	if (one_player_check(game))
		return (perror("Invalid number of players"), 1);
	y = 0;
	while (game->map[y])
	{
		if (row_is_open(game, y))
			return (perror("Map is not surrounded by walls"), 1);
		y++;
	}
	return (0);
}