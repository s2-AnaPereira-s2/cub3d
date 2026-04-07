#include "cub3d.h"

void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (game->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void calculate_wall(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - game->px + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->py + (1 - ray->step_y) / 2) / ray->ray_dir_y;

    ray->line_height = (int)(game->win_height / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + game->win_height / 2;
    if (ray->draw_end >= game->win_height)
        ray->draw_end = game->win_height - 1;
}

void draw_wall(t_game *game, t_ray *ray, int x)
{
    int y;
    int texX;
    int texY;
    double wallX;
    unsigned int color;
    char *tex_addr;

    if (ray->side == 0)
        wallX = game->py + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wallX = game->px + ray->perp_wall_dist * ray->ray_dir_x;
    wallX -= floor(wallX);
    texX = (int)(wallX * game->textures[0].width);
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        texY = (int)(((y - ray->draw_start) / (double)(ray->draw_end - ray->draw_start)) 
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
        init_ray1(game, player, &ray, x);
        init_ray2(game, &ray);
        perform_dda(game, &ray);
        calculate_wall(game, &ray);
        draw_wall(game, &ray, x);
        x++;
    }
}