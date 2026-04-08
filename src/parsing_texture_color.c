
#include "cub3d.h"

void load_text_img(t_game *game)
{
	int text_width;
	int text_height;

	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->N_path, &text_width, &text_height);
	if (!game->textures[0].img)
        return (perror("Failed to load texture"));
	game->textures[0].width = text_width;
    game->textures[0].height = text_height;
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, game->S_path, &text_width, &text_height);
	if (!game->textures[1].img)
        return (perror("Failed to load texture"));
	game->textures[1].width = text_width;
    game->textures[1].height = text_height;
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, game->W_path, &text_width, &text_height);
	if (!game->textures[2].img)
        return (perror("Failed to load texture"));
	game->textures[2].width = text_width;
    game->textures[2].height = text_height;
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, game->E_path, &text_width, &text_height);
	if (!game->textures[3].img)
        return (perror("Failed to load texture"));
	game->textures[3].width = text_width;
    game->textures[3].height = text_height;
}

void pass_text_imgstruct(t_game *game)
{
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img, &game->textures[0].bits_per_pixel,
        &game->textures[0].line_length, &game->textures[0].endian);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img, &game->textures[1].bits_per_pixel,
        &game->textures[1].line_length, &game->textures[1].endian);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img, &game->textures[2].bits_per_pixel,
        &game->textures[2].line_length, &game->textures[2].endian);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img, &game->textures[3].bits_per_pixel,
        &game->textures[3].line_length, &game->textures[3].endian);
}

void get_dir_textures(t_game *game)
{
	int N_len;
	int S_len;
	int W_len;
	int E_len;

	N_len = ft_strlen(game->info[game->NO_index]);
	S_len = ft_strlen(game->info[game->SO_index]);
	W_len = ft_strlen(game->info[game->WE_index]);
	E_len = ft_strlen(game->info[game->EA_index]);
	game->N_path = ft_substr(game->info[game->NO_index], 5, N_len - 6);
	game->S_path = ft_substr(game->info[game->SO_index], 5, S_len - 6);
	game->W_path = ft_substr(game->info[game->WE_index], 5, W_len - 6);
	game->E_path = ft_substr(game->info[game->EA_index], 5, E_len - 6);
	load_text_img(game);
    pass_text_imgstruct(game);
}

void pass_colors(t_game *game)
{
	int r;
	int g;
	int b;

	r = ft_atoi(game->f_rgb[0]) << 16;
	g = ft_atoi(game->f_rgb[1]) << 8;
	b = ft_atoi(game->f_rgb[2]);
	game->f_color = r | g | b;
	r = ft_atoi(game->c_rgb[0]) << 16;
	g = ft_atoi(game->c_rgb[1]) << 8;
	b = ft_atoi(game->c_rgb[2]);
	game->c_color = r | g | b;

}

void get_colors(t_game *game)
{
	int i;
	int f_rgb_len;
	int c_rgb_len;

	i = 0;
	while (game->info[i])
	{
		if (game->info[i][0] == 'F')
		{
			f_rgb_len = ft_strlen(game->info[i]);
			game->f_rgb = ft_split((ft_substr(game->info[i], 2, f_rgb_len - 3)), ',');
			game->f_num++;
		}
		else if (game->info[i][0] == 'C')
		{
			c_rgb_len = ft_strlen(game->info[i]);
			game->c_rgb = ft_split((ft_substr(game->info[i], 2, c_rgb_len - 3)), ',');
			game->c_num++;
		}
		i++;
	}
	pass_colors(game);
}





