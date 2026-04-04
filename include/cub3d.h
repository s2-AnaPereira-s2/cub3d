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

#define NO 0
#define SO 1
#define WE 2
#define EA 3

#define TILE_SIZE 10
#define MINI_OFFSET_X 10 // pixels from left
#define MINI_OFFSET_Y 10 // pixels from top
#define PLAYER_SIZE (TILE_SIZE / 2)    // red dot size

#define MOVE_SPEED 0.1

#define TEXTURE_WH 300

// -------------------- Includes --------------------
# include "libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

#endif

// -------------------- Structs --------------------

typedef struct s_player {
    char dir;
    double dirX;             // Direction vector
    double dirY;             // Direction vector
    double planeX;           // Camera plane (FOV)
    double planeY;           // Camera plane (FOV)
} t_player;

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
	void	*mlx;
	void	*win;
	void	*mlx_destroy_display;

	char	**info;
	char	**map;
	char	*file_name;

	int		win_width;
	int		win_height;

	int		map_height;
	int		map_width;
	int		info_size;
	int		fd;

	int		np_x;
	int		np_y;
	int		p;
    double  px;                // Position
    double  py;                // Position

	char	*N_path;
	char	*S_path;
	char	*E_path;
	char	*W_path;

	int		f_color;
	int		c_color;

	t_img	screen;        
	t_img	textures[4];   

    t_player player;
}	t_game;

typedef struct s_ray
{
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
} t_ray;

// -------------------- Functions --------------------

int	    get_info(t_game *game);
int	    get_map(t_game *game);
int		map_check(t_game *game);
void	get_pn_pos(t_game *game, t_player *player);
void	get_direction(t_player *player);
int		get_helpers(t_game *game, t_player *player);
int	    get_length(t_game *game);
void	init_game(t_game *game, t_player *player);
int	    close_window(t_game *game);
int	    char_check(t_game *game);
int		bad_extension(t_game *game);
int	    render_frame(void *param);
void    get_dir_textures(t_game *game);
void    get_colors(t_game *game);
void    raycast(t_game *game, t_player *player);
void    perform_dda(t_game *game, t_ray *ray);
void    calculate_wall(t_game *game, t_ray *ray);
void    draw_wall(t_game *game, t_ray *ray, int x);
int     keypress(int keycode, t_game *game);
void    put_pixel(t_img *img, int x, int y, int color);
int	    line_len_no_nl(char *line);
void    init_ray1(t_game *game, t_player *player, t_ray *ray, int x);
void    init_ray2(t_game *game, t_ray *ray);
void    init_win_wh(t_game *game);
char	map_at(t_game *game, int y, int x);