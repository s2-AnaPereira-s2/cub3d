#include "cub3d.h"

void	calculate_wall(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->px
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->py
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(game->win_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

int	text_index_wall(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x == 1)
			return (3);
		return (2);
	}
	if (ray->step_y == 1)
		return (1);
	return (0);
}

double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;
	double	intersection_x;
	double	intersection_y;

	intersection_x = game->px + ray->perp_wall_dist * ray->ray_dir_x;
	intersection_y = game->py + ray->perp_wall_dist * ray->ray_dir_y;
	if (ray->side == 0)
		wall_x = intersection_y - floor(intersection_y);
	else
		wall_x = intersection_x - floor(intersection_x);
	if (wall_x < 0)
		wall_x += 1.0;
	return (wall_x);
}

static double	get_text_pos(t_game *game, t_ray *ray)
{
	double	wall_x;
	double	tex_pos;

	game->tex_index = text_index_wall(ray);
	wall_x = get_wall_x(game, ray);
	game->tex_x = (int)(wall_x * game->textures[game->tex_index].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		game->tex_x = game->textures[game->tex_index].width - game->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		game->tex_x = game->textures[game->tex_index].width - game->tex_x - 1;
	if (game->tex_x < 0)
		game->tex_x = 0;
	if (game->tex_x >= game->textures[game->tex_index].width)
		game->tex_x = game->textures[game->tex_index].width - 1;
	game->step = 1.0 * game->textures[game->tex_index].height
		/ ray->line_height;
	tex_pos = (ray->draw_start - game->win_height / 2 + ray->line_height / 2)
		* game->step;
	return (tex_pos);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int					y;
	int					tex_y;
	double				tex_pos;
	unsigned int		color;
	char				*tex_addr;

	tex_pos = get_text_pos(game, ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->textures[game->tex_index].height)
			tex_y = game->textures[game->tex_index].height - 1;
		tex_addr = game->textures[game->tex_index].addr
			+ (tex_y * game->textures[game->tex_index].line_length
				+ game->tex_x
				* (game->textures[game->tex_index].bits_per_pixel / 8));
		color = *(unsigned int *)tex_addr;
		put_pixel(&game->screen, x, y, color);
		tex_pos += game->step;
		y++;
	}
}
