
#include "cub3d.h"

int	line_len_no_nl(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

char	map_at(t_game *game, int y, int x)
{
	int	len;

	if (y < 0 || y >= game->map_height)
		return (' ');
	len = line_len_no_nl(game->map[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (game->map[y][x]);
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

void get_map_width(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != '\n')
			j++;
		if (game->map_width < j)
			game->map_width = j;
		i++;
	}
}



