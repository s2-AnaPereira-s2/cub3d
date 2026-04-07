
#include "cub3d.h"

void init_textures(t_game *game)
{
	int i;

	game->N_path = NULL;
	game->S_path = NULL;
	game->E_path = NULL;
	game->W_path = NULL;
	game->no_index = 0;
	game->so_index = 0;
	game->we_index = 0;
	game->ea_index = 0;
	game->no_num = 0;
	game->so_num = 0;
	game->we_num = 0;
	game->ea_num = 0;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
}



void	init_game(t_game *game, t_player *player)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->info_size = 0;
	game->fd = -1;
	game->map = NULL;
	game->info = NULL;
	game->p = 0;
	game->px = 0.00;
	game->py = 0.00;
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	player->dir = ' ';
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	game->f_color = 0;
	game->c_color = 0;
	game->f_num = 0;
	game->c_num = 0;
	game->screen.img = NULL;
	game->screen.addr = NULL;
	init_textures(game);
}

void init_ray1(t_game *game, t_player *player, t_ray *ray, int x)
{
    double cameraX;

    cameraX = 2 * x / (double)game->win_width - 1;

    ray->ray_dir_x = player->dir_x + player->plane_x * cameraX;
    ray->ray_dir_y = player->dir_y + player->plane_y * cameraX;

    ray->map_x = (int)game->px;
    ray->map_y = (int)game->py;

    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void init_ray2(t_game *game, t_ray *ray)
{
    ray->hit = 0;

    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->px - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->px) * ray->delta_dist_x;
    }

    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->py - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->py) * ray->delta_dist_y;
    }
}

void init_win_wh(t_game *game)
{
	int screen_w;
	int screen_h;

	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	game->win_width = screen_w;
	game->win_height = screen_h;
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
}
