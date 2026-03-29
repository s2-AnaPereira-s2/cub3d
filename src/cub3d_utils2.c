
#include "cub3d.h"

void	*file_to_img(t_game *game, char *path)
{
	return (mlx_xpm_file_to_image(game->mlx, path, 
			&game->img_width, &game->img_height));
}

int	check_images(t_game *game, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!game->img[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_length(t_game *game)
{
	char	*line;
	int		size;

	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd < 0)
		return (perror("Wrong file"), close(game->fd), close_window(game));
	if (bad_extension(game))
		return (close(game->fd), close_window(game));
	size = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
	return (size);
}
