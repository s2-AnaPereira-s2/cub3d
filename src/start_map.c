#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	pixel_index;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return ;
    pixel_index = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
    img->addr[pixel_index] = color & 0xFF;
    img->addr[pixel_index + 1] = (color >> 8) & 0xFF;
    img->addr[pixel_index + 2] = (color >> 16) & 0xFF;
    if (img->bits_per_pixel == 32)
        img->addr[pixel_index + 3] = 0;
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				put_pixel(&game->screen, x++, y, game->c_color);
			else
				put_pixel(&game->screen, x++, y, game->f_color);
		}
		y++;
	}
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_movement(game);
	draw_background(game);
	raycast(game, &game->player);
	draw_minimap(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}