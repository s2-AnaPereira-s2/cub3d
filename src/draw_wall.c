#include "cub3d.h"

void calculate_wall(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - game->px + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - game->py + (1 - ray->stepY) / 2) / ray->rayDirY;

    ray->lineHeight = (int)(game->win_height / ray->perpWallDist);
    ray->drawStart = -ray->lineHeight / 2 + game->win_height / 2;
    if (ray->drawStart < 0)
        ray->drawStart = 0;
    ray->drawEnd = ray->lineHeight / 2 + game->win_height / 2;
    if (ray->drawEnd >= game->win_height)
        ray->drawEnd = game->win_height - 1;
}

int get_index_wall(t_ray *ray)
{

    if (ray->side == 0)  // Vertical wall (East/West)
    {
        if (ray->stepX == 1)
            return (3);  // East wall
        else
            return 2;  // West wall
    }
    else  // Horizontal wall (North/South)
    {
        if (ray->stepY == 1)
            return 1;  // South wall
        else
            return 0;  // North wall
    }
}

double get_wallX(t_game *game, t_ray *ray)
{
    double wallX;

    if (ray->side == 0)
        wallX = game->py + ray->perpWallDist * ray->rayDirY;
    else
        wallX = game->px + ray->perpWallDist * ray->rayDirX;
    wallX -= floor(wallX);
    return (wallX);
}

void draw_wall(t_game *game, t_ray *ray, int x)
{
    int y;
    int texX;
    int texY;
    double wallX;
    int tex_index;
    unsigned int color;
    char *tex_addr;

    tex_index = get_index_wall(ray);
    wallX = get_wallX(game, ray);
    texX = (int)(wallX * game->textures[tex_index].width);
    y = ray->drawStart;
    while (y < ray->drawEnd)
    {
        texY = (int)(((y - ray->drawStart) / (double)(ray->drawEnd - ray->drawStart)) 
                * game->textures[tex_index].height);
        tex_addr = game->textures[tex_index].addr 
            + (texY * game->textures[tex_index].line_length 
            + texX * (game->textures[tex_index].bits_per_pixel / 8));
        color = *(unsigned int *)tex_addr;
        put_pixel(&game->screen, x, y, color);
        y++;
    }
}
