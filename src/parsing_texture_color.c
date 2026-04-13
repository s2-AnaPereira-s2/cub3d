/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:38:55 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/13 13:23:22 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pass_text_imgstruct(t_game *game)
{
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bits_per_pixel,
			&game->textures[0].line_length, &game->textures[0].endian);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bits_per_pixel,
			&game->textures[1].line_length, &game->textures[1].endian);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bits_per_pixel,
			&game->textures[2].line_length, &game->textures[2].endian);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bits_per_pixel,
			&game->textures[3].line_length, &game->textures[3].endian);
}

int	load_text_img(t_game *game)
{
	char	*paths[4];
	int		i;
	int		text_w;
	int		text_h;

	paths[0] = game->n_path;
	paths[1] = game->s_path;
	paths[2] = game->w_path;
	paths[3] = game->e_path;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				paths[i], &text_w, &text_h);
		if (!game->textures[i].img)
			return (ft_putstr_fd("Error: Failed to load texture\n", 2),
				close_window(game), 1);
		game->textures[i].width = text_w;
		game->textures[i].height = text_h;
		i++;
	}
	pass_text_imgstruct(game);
	return (0);
}

void	get_dir_textures(t_game *game)
{
	char	*trim;

	trim = trim_path(game->info[game->no_index]);
	game->n_path = ft_substr(trim, 4, ft_strlen(trim) - 4);
	free(trim);
	trim = trim_path(game->info[game->so_index]);
	game->s_path = ft_substr(trim, 4, ft_strlen(trim) - 4);
	free(trim);
	trim = trim_path(game->info[game->we_index]);
	game->w_path = ft_substr(trim, 4, ft_strlen(trim) - 4);
	free(trim);
	trim = trim_path(game->info[game->ea_index]);
	game->e_path = ft_substr(trim, 4, ft_strlen(trim) - 4);
	free(trim);
}

void	get_colors_index(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->info[i])
	{
		j = 0;
		while (game->info[i][j] == ' ' || game->info[i][j] == '\t')
			j++;
		if (game->info[i][j] == 'F')
		{
			game->f_index = i;
			game->f_num++;
		}
		else if (game->info[i][j] == 'C')
		{
			game->c_index = i;
			game->c_num++;
		}
		i++;
	}
}

void	get_colors(t_game *game)
{
	char	*color;

	get_colors_index(game);
	if (game->c_num != 1 && game->f_num != 1)
		return;
	color = trim_color(game->info[game->f_index]);
	game->f_rgb = ft_split(color, ',');
	free(color);
	color = trim_color(game->info[game->c_index]);
	game->c_rgb = ft_split(color, ',');
	free(color);
	game->f_color = (ft_atoi(game->f_rgb[0]) << 16)
		| (ft_atoi(game->f_rgb[1]) << 8) | ft_atoi(game->f_rgb[2]);
	game->c_color = (ft_atoi(game->c_rgb[0]) << 16)
		| (ft_atoi(game->c_rgb[1]) << 8) | ft_atoi(game->c_rgb[2]);
}
