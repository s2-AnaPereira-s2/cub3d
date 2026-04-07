
#include "cub3d.h"

int	get_info(t_game *game)
{
	char	*line;

	game->info_size = get_length(game);
	if (game->info_size == 0)
		return (perror("empty map"), close_window(game), 1);
	game->info = ft_calloc(sizeof(char *), game->info_size + 1);
	if (!game->info)
		return 1;
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
			break;
	}
	game->info[game->info_size] = NULL;
	pass_text_index(game);
	close(game->fd);
	return 0;
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
	if (!game->map || game->map_height == 0)
		return (perror("No map"), close_window(game), 1);
	i = 0;
	while (game->info[map_start])
	{
		game->map[i] = game->info[map_start];
		map_start++;
		i++;
	}
	game->map[i] = NULL;
	get_map_width(game);
	return (0);
}

void get_dir_textures(t_game *game)
{
	int N_len;
	int S_len;
	int W_len;
	int E_len;
	int text_wh;

	N_len = ft_strlen(game->info[game->no_index]);
	S_len = ft_strlen(game->info[game->so_index]);
	W_len = ft_strlen(game->info[game->we_index]);
	E_len = ft_strlen(game->info[game->ea_index]);
	game->N_path = ft_substr(game->info[game->no_index], 5, N_len - 6);
	game->S_path = ft_substr(game->info[game->so_index], 5, S_len - 6);
	game->W_path = ft_substr(game->info[game->we_index], 5, W_len - 6);
	game->E_path = ft_substr(game->info[game->ea_index], 5, E_len - 6);
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->N_path, &text_wh, &text_wh);
	if (!game->textures[0].img)
        return (perror("Failed to load texture"));
    game->textures[0].width = TEXTURE_WH;
	game->textures[0].height = TEXTURE_WH;
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img, &game->textures[0].bits_per_pixel,
        &game->textures[0].line_length, &game->textures[0].endian);
}

void pass_colors(t_game *game, char **f_rgb, char **c_rgb)
{
	int r;
	int g;
	int b;

	r = ft_atoi(f_rgb[0]) << 16;
	g = ft_atoi(f_rgb[1]) << 8;
	b = ft_atoi(f_rgb[2]);
	game->f_color = r | g | b;
	r = ft_atoi(c_rgb[0]) << 16;
	g = ft_atoi(c_rgb[1]) << 8;
	b = ft_atoi(c_rgb[2]);
	game->c_color = r | g | b;

}

void get_colors(t_game *game)
{
	int i;
	char **f_rgb;
	char **c_rgb;
	int f_rgb_len;
	int c_rgb_len;

	i = 0;
	while (game->info[i])
	{
		if (game->info[i][0] == 'F')
		{
			f_rgb_len = ft_strlen(game->info[i]);
			f_rgb = ft_split((ft_substr(game->info[i], 2, f_rgb_len - 3)), ',');
			game->f_num++;
		}
		else if (game->info[i][0] == 'C')
		{
			c_rgb_len = ft_strlen(game->info[i]);
			c_rgb = ft_split((ft_substr(game->info[i], 2, c_rgb_len - 3)), ',');
			game->c_num++;
		}
		i++;
	}
	pass_colors(game, f_rgb, c_rgb);
}





