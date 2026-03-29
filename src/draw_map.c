
#include "cub3d.h"

void	get_info(t_game *game)
{
	char	*line;

	game->info_size = get_length(game);
	if (game->info_size == 0)
	{
		close_window(game);
		return;
	}
	game->info = ft_calloc(sizeof(char *), game->info_size + 1);
	if (!game->info)
		return ;
	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
	{
		close(game->fd);
		close_window(game);
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

void get_dir_textures(t_game *game, t_imgs *imgs)
{
	int N_len;
	int S_len;
	int W_len;
	int E_len;

	N_len = ft_strlen(game->info[0]);
	S_len = ft_strlen(game->info[1]);
	W_len = ft_strlen(game->info[2]);
	E_len = ft_strlen(game->info[3]);
	imgs->N_path = ft_substr(game->info[0], 5, N_len - 6);
	imgs->S_path = ft_substr(game->info[1], 5, S_len - 6);
	imgs->W_path = ft_substr(game->info[2], 5, W_len - 6);
	imgs->E_path = ft_substr(game->info[3], 5, E_len - 6);
}

void get_colors(t_game *game, t_imgs *imgs)
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
			c_rgb = ft_split((ft_substr(game->info[i], 2, f_rgb_len - 3)), ',');
		}
		i++;
	}
	r = ft_atoi(f_rgb[0]) << 16;
	g = ft_atoi(f_rgb[1]) << 8;
	b = ft_atoi(f_rgb[2]);
	imgs->f_color = r | g | b;
	r = ft_atoi(c_rgb[0]) << 16;
	g = ft_atoi(c_rgb[1]) << 8;
	b = ft_atoi(c_rgb[2]);
	imgs->c_color = r | g | b;

}


int	get_image(t_imgs *imgs, t_game *game)
{
	int	i;

	imgs->img = malloc(sizeof(void *) * (5));
	if (!imgs->img)
		return (ft_printf("Error\n"), close_window(game));
	i = 0;
	while (i < 5)
	{
		imgs->img[i] = NULL;
		i++;
	}
	imgs->img[0] = file_to_img(game, imgs->N_path);
	imgs->img[1] = file_to_img(game, imgs->S_path);
	imgs->img[2] = file_to_img(game, imgs->W_path);
	imgs->img[3] = file_to_img(game, imgs->E_path);
	if (check_images(game, 4))
		return (perror("Error: failed to load image\n"), exit(0), 1);
	return (0);
}

int	put_image_map(int y, int x, t_game *game, t_imgs *imgs)
{
	while (x < game->map_width && game->map[y][x])
	{
		if (game->map[y][x] == '1')
			put_img_window(game, imgs->img[0], imgs->img_width * x, 
				imgs->img_height * y);
		else
			put_img_window(game, imgs->img[1], imgs->img_width * x, 
				imgs->img_height * y);
		x++;
	}
	return (0);
}

void draw_player(t_game *game, t_player *player)
{
    int px = (int)(player->x * (32 - 16));
    int py = (int)(player->y * (32 - 16));

    put_img_window(game, game->img[3], px, py);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		put_image_map(y, x, game);
		y++;
	}
}

