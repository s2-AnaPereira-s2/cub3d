#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_square(t_img *img, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            put_pixel(img, x + j, y + i, color);
    }
}

// Double check this I think I did it right, but check!
void draw_background(t_game *game)
{
    int x, y;

    for (y = 0; y < game->win_height; y++)
    {
        for (x = 0; x < game->win_width; x++)
        {
            if (y < game->win_height / 2)
                put_pixel(&game->screen, x, y, game->c_color); // ceiling
            else
                put_pixel(&game->screen, x, y, game->f_color); // floor
        }
    }
}

// I think its bonus I will double check this
void draw_minimap(t_game *game)
{
    int y, x;
    int color;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x] && game->map[y][x] != '\n')
        {
            if (game->map[y][x] == '1')
                color = 0xFFFFFF; // wall
            else
                color = 0x333333; // floor

            draw_square(&game->screen,
                MINI_OFFSET_X + x * TILE_SIZE,
                MINI_OFFSET_Y + y * TILE_SIZE,
                TILE_SIZE, color);
            x++;
        }
        y++;
    }
}

// I think this is bonus I will double check 
void draw_player(t_game *game)
{
    int px = MINI_OFFSET_X + (int)(game->px * TILE_SIZE) - PLAYER_SIZE / 2;
    int py = MINI_OFFSET_Y + (int)(game->py * TILE_SIZE) - PLAYER_SIZE / 2;

    draw_square(&game->screen, px, py, PLAYER_SIZE, 0xFF0000);
}

int render_frame(void *param)
{
    t_game *game = (t_game *)param;

    update_movement(game);
    draw_background(game);       // ceiling + floor
    raycast(game, &game->player); // 3D walls
    draw_minimap(game);          // 2D mini-map
    draw_player(game);

    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    return (0);
}