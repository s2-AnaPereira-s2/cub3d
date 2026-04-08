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

int text_index_wall(t_ray *ray)
{

    if (ray->side == 0)  // Vertical wall (East/West)
    {
        if (ray->stepX == 1)
            return 3;  // East wall
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
    double intersection_x;
    double intersection_y;

    intersection_x = game->px + ray->perpWallDist * ray->rayDirX;
    intersection_y = game->py + ray->perpWallDist * ray->rayDirY;
    if (ray->side == 0)
        wallX = intersection_y - floor(intersection_y);
    else
        wallX = intersection_x - floor(intersection_x);
    if (wallX < 0)
        wallX += 1.0;
    return (wallX);
}

static double get_text_pos(t_game *game, t_ray *ray)
{
    double          wallX;
    double          tex_pos;

    game->tex_index = text_index_wall(ray);
    wallX = get_wallX(game, ray);
    game->texX = (int)(wallX * game->textures[game->tex_index].width);
    if (ray->side == 0 && ray->rayDirX > 0)
        game->texX = game->textures[game->tex_index].width - game->texX - 1;
    if (ray->side == 1 && ray->rayDirY < 0)
        game->texX = game->textures[game->tex_index].width - game->texX - 1;
    if (game->texX < 0)
        game->texX = 0;
    if (game->texX >= game->textures[game->tex_index].width)
        game->texX = game->textures[game->tex_index].width - 1;
    game->step = 1.0 * game->textures[game->tex_index].height / ray->lineHeight;
    tex_pos = (ray->drawStart - game->win_height / 2 + ray->lineHeight / 2)
        * game->step;
    return (tex_pos);
}

void draw_wall(t_game *game, t_ray *ray, int x)
{
    int             y;
    int             texY;
    double          tex_pos;
    unsigned int    color;
    char            *tex_addr;

    tex_pos = get_text_pos(game, ray);
    y = ray->drawStart;
    while (y <= ray->drawEnd)
    {
        texY = (int)tex_pos;
        if (texY < 0)
            texY = 0;
        if (texY >= game->textures[game->tex_index].height)
            texY = game->textures[game->tex_index].height - 1;
        tex_addr = game->textures[game->tex_index].addr 
            + (texY * game->textures[game->tex_index].line_length 
            + game->texX * (game->textures[game->tex_index].bits_per_pixel / 8));
        color = *(unsigned int *)tex_addr;
        put_pixel(&game->screen, x, y, color);
        tex_pos += game->step;
        y++;
    }
}
