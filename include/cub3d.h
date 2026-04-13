/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:44:42 by ana-pdos          #+#    #+#             */
/*   Updated: 2026/04/13 18:29:08 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TILE_SIZE 10
# define MINI_OFFSET_X 10
# define MINI_OFFSET_Y 10
# define PLAYER_SIZE 5
# define PLAYER_RADIUS 0.2
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define TEXTURE_WH 300

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	char	dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*mlx_destroy_display;
	char		**info;
	char		**map;
	char		*file_name;
	int			win_width;
	int			win_height;
	int			map_height;
	int			map_width;
	int			map_start;
	int			info_size;
	int			fd;
	int			np_x;
	int			np_y;
	int			p;
	double		px;
	double		py;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	char		**paths;
	char		*n_path;
	char		*s_path;
	char		*e_path;
	char		*w_path;
	char		**f_rgb;
	char		**c_rgb;
	int			tex_index;
	int			tex_x;
	double		step;
	int			no_index;
	int			so_index;
	int			we_index;
	int			ea_index;
	int			no_num;
	int			so_num;
	int			we_num;
	int			ea_num;
	int			f_color;
	int			c_color;
	int			f_index;
	int			c_index;
	int			f_rgb_len;
	int			c_rgb_len;
	int			f_num;
	int			c_num;
	t_img		screen;
	t_img		textures[4];
	t_player	player;
}	t_game;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

int			get_info(t_game *game);
int			get_map(t_game *game);
int			map_check(t_game *game);
void		get_pn_pos(t_game *game, t_player *player);
int			startup_1(t_game *game);
int			startup_2(t_game *game);
int			get_length(t_game *game);
void		init_game(t_game *game, t_player *player);
int			close_window(t_game *game);
int			char_check(t_game *game);
int			bad_extension(t_game *game);
int			bad_text_extension(t_game *game);
int			render_frame(void *param);
void		get_dir_textures(t_game *game);
int			get_colors(t_game *game);
void		raycast(t_game *game, t_player *player);
int			load_text_img(t_game *game);
void		perform_dda(t_game *game, t_ray *ray);
void		calculate_wall(t_game *game, t_ray *ray);
void		draw_wall(t_game *game, t_ray *ray, int x);
int			keypress(int keycode, t_game *game);
int			keyrelease(int keycode, t_game *game);
void		draw_player(t_game *game);
void		update_movement(t_game *game);
void		put_pixel(t_img *img, int x, int y, int color);
int			line_len_no_nl(char *line);
void		init_ray1(t_game *game, t_player *player, t_ray *ray, int x);
void		init_ray2(t_game *game, t_ray *ray);
void		init_win_wh(t_game *game);
char		map_at(t_game *game, int y, int x);
void		get_map_width(t_game *game);
void		pass_text_index(t_game *game);
int			p_c_d_check(t_game *game);
void		draw_minimap(t_game *game);
char		*trim_color(char *color);
char		*trim_path(char *path);
char		*trim_core(char *str, int skip_fc);
int			is_empty_line(char *line);

#endif