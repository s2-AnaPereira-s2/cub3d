#include "cub3d.h"

// this is almost understood. Need to spend some time on this to understand better this calculations


// Step 1: initialize ray for column x

void init_ray(t_game *game, t_player *player, t_ray *ray, int x)
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

// Step 2: perform DDA

void perform_dda(t_game *game, t_ray *ray)
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
        if (game->map[ray->mapY][ray->mapX] == '1')
            ray->hit = 1;
    }
}

// Step 3: calculate perpendicular wall distance & line height

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

void draw_wall(t_game *game, t_ray *ray, int x)
{
    int y, texX, texY;
    double wallX;
    unsigned int color;
    char *tex_addr;

    if (ray->side == 0)
        wallX = game->py + ray->perpWallDist * ray->rayDirY;
    else
        wallX = game->px + ray->perpWallDist * ray->rayDirX;
    wallX -= floor(wallX);
    texX = (int)(wallX * game->textures[0].width);
    y = ray->drawStart;
    while (y < ray->drawEnd)
    {
        texY = (int)(((y - ray->drawStart) / (double)(ray->drawEnd - ray->drawStart)) 
                * game->textures[0].height);
        
        tex_addr = game->textures[0].addr 
            + (texY * game->textures[0].line_length 
            + texX * (game->textures[0].bits_per_pixel / 8));
        color = *(unsigned int *)tex_addr;
        put_pixel(&game->screen, x, y, color);
        y++;
    }
}

void raycast(t_game *game, t_player *player)
{
    int x;
    t_ray ray;

    x = 0;
    while (x < game->win_width)
    {
        init_ray(game, player, &ray, x);
        perform_dda(game, &ray);
        calculate_wall(game, &ray);
        draw_wall(game, &ray, x);
        x++;
    }
}