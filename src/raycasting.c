#include "cub3d.h"

static void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (map_at(game, ray->mapY, ray->mapX) == '1')
            ray->hit = 1;
    }
}

void raycast(t_game *game, t_player *player)
{
    int x;
    t_ray ray;

    x = 0;
    while (x < game->win_width)
    {
        init_ray1(game, player, &ray, x);
        init_ray2(game, &ray);
        perform_dda(game, &ray);
        calculate_wall(game, &ray);
        draw_wall(game, &ray, x);
        x++;
    }
}