#ifndef CUB3D_H
# define CUB3D_H

// -------------------- Keycodes --------------------
#ifdef __APPLE__
    #define KEY_UP     126
    #define KEY_DOWN   125
    #define KEY_LEFT   123
    #define KEY_RIGHT  124
    #define KEY_ESC    53
    #define KEY_W      13
    #define KEY_A      0
    #define KEY_S      1
    #define KEY_D      2
#else
    #define KEY_UP     65362
    #define KEY_DOWN   65364
    #define KEY_LEFT   65361
    #define KEY_RIGHT  65363
    #define KEY_ESC    65307
    #define KEY_W      119
    #define KEY_A      97
    #define KEY_S      115
    #define KEY_D      100
#endif

// -------------------- Other defines --------------------
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// -------------------- Includes --------------------
# include "libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include "minilibx_macos_opengl/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

#endif

// -------------------- Struct --------------------

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*mlx_destroy_display;
	char	**map;
	char	**map_cpy;
	void	**img;
	char	*file_name;
	int		img_width;
	int		img_height;
	int		win_width;
	int		win_height;
	int		map_height;
	int		tile_w;
	int		tile_h;
	int		line_len;
	int		fd;
	int		p_x;
	int		p_y;
	int		np_x;
	int		np_y;
	int		game_win;
	int		exit_x;
	int		exit_y;
	int		movements;
	int		p;
}	t_game;

typedef struct s_player {
    char dir;
    double x;                // Position
    double y;                // Position
    double dirX;             // Direction vector
    double dirY;             // Direction vector
    double planeX;           // Camera plane (FOV)
    double planeY;           // Camera plane (FOV)
} t_player;

// -------------------- Functions --------------------

int		get_image(t_game *game);
int		get_map(t_game *game);
int		put_image_map(int y, int x, t_game *game);
void	draw_map(t_game *game);
void	get_score(t_game *game);
int		move_player(t_game *game, int keycode);
//int		move_check(t_game *game);
int		map_check(t_game *game);
void	map_copy(t_game *game);
void	get_pn_pos(t_game *game, t_player *player);
void	get_direction(t_player *player);
int		get_helpers(t_game *game, t_player *player);
int		close_window(t_game *game);
int		put_img_window(t_game *game, char *img, int x, int y);
void	*file_to_img(t_game *game, char *path);
int		check_images(t_game *game, int size);
int		get_length(t_game *game);
void	init_game(t_game *game, t_player *player);
int		window_check(t_game *game);
int		char_check(t_game *game);
int		bad_extension(t_game *game);


