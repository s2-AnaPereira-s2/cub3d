#include "cub3d.h"

int render_frame(t_game *game, t_player *player)
{
    // 1. Clear the screen / image buffer
    clear_screen(game);

    // 2. Draw ceiling
    draw_ceiling(game);

    // 3. Draw floor
    draw_floor(game);

    // 4. Draw walls (raycasting)
    cast_rays(game);

    // 5. Draw sprites (if any)
    draw_sprites(game);

    // 6. Put the final image to the window
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return (0);
}