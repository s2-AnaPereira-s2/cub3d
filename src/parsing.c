
#include "cub3d.h"

void	get_info(t_game *game)
{
	char	*line;

	game->info_size = get_length(game);
	if (game->info_size == 0)
	{
		return;
	}
	game->info = ft_calloc(sizeof(char *), game->info_size + 1);
	if (!game->info)
		return ;
	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
	{
		close(game->fd);
		return;
	}
	game->info_size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		game->info[game->info_size++] = line;
		line = get_next_line(game->fd);
		if (!line)
			break;
	}
	game->info[game->info_size] = NULL;
	close(game->fd);
}

int	get_map(t_game *game)
{
	int i;
	int map_start;

	i = 0;
	while (game->info[i] && game->info[i][0] != '1' && game->info[i][0] != '0' && game->info[i][0] != ' ')
    	i++;
	map_start = i;
	while (game->info[i])
	{
		game->map_height++;
		i++;
	}
	game->map = ft_calloc(sizeof(char *), game->map_height + 1);
	if (!game->map)
		return (0);
	i = 0;
	while (game->info[map_start])
	{
		game->map[i] = game->info[map_start];
		map_start++;
		i++;
	}
	game->map[i] = NULL;
	return (0);
}

void get_dir_textures(t_game *game)
{
	int N_len;
	int S_len;
	int W_len;
	int E_len;

	N_len = ft_strlen(game->info[0]);
	S_len = ft_strlen(game->info[1]);
	W_len = ft_strlen(game->info[2]);
	E_len = ft_strlen(game->info[3]);
	game->N_path = ft_substr(game->info[0], 5, N_len - 6);
	game->S_path = ft_substr(game->info[1], 5, S_len - 6);
	game->W_path = ft_substr(game->info[2], 5, W_len - 6);
	game->E_path = ft_substr(game->info[3], 5, E_len - 6);
}

void get_colors(t_game *game)
{
	int i;
	char **f_rgb;
	char **c_rgb;
	int f_rgb_len;
	int c_rgb_len;
	int r;
	int g;
	int b;

	i = 0;
	while (game->info[i])
	{
		if (game->info[i][0] == 'F')
		{
			f_rgb_len = ft_strlen(game->info[i]);
			f_rgb = ft_split((ft_substr(game->info[i], 2, f_rgb_len - 3)), ',');
		}
		else if (game->info[i][0] == 'C')
		{
			c_rgb_len = ft_strlen(game->info[i]);
			c_rgb = ft_split((ft_substr(game->info[i], 2, c_rgb_len - 3)), ',');
		}
		i++;
	}
	r = ft_atoi(f_rgb[0]) << 16;
	g = ft_atoi(f_rgb[1]) << 8;
	b = ft_atoi(f_rgb[2]);
	game->f_color = r | g | b;
	r = ft_atoi(c_rgb[0]) << 16;
	g = ft_atoi(c_rgb[1]) << 8;
	b = ft_atoi(c_rgb[2]);
	game->c_color = r | g | b;

}




