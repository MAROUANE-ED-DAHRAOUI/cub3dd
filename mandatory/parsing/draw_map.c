#include "../include/cub3d.h"

void	start_drawing(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	 draw_floor_ceiling(data);
	data->player.angle = ft_normalize(data->player.angle);
	start_raycasting(data, 0, 0);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
