
#include "cub3d.h"

void init_textures(t_game *game)
{
	int i;

	game->N_path = NULL;
	game->S_path = NULL;
	game->E_path = NULL;
	game->W_path = NULL;
	game->NO_index = 0;
	game->SO_index = 0;
	game->WE_index = 0;
	game->EA_index = 0;
	game->NO_num = 0;
	game->SO_num = 0;
	game->WE_num = 0;
	game->EA_num = 0;
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
	player->dir = ' ';
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0.0;
	player->planeY = 0.0;
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

    ray->rayDirX = player->dirX + player->planeX * cameraX;
    ray->rayDirY = player->dirY + player->planeY * cameraX;

    ray->mapX = (int)game->px;
    ray->mapY = (int)game->py;

    if (ray->rayDirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1 / ray->rayDirX);
    if (ray->rayDirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void init_ray2(t_game *game, t_ray *ray)
{
    ray->hit = 0;

    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (game->px - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->px) * ray->deltaDistX;
    }

    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game->py - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->py) * ray->deltaDistY;
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
