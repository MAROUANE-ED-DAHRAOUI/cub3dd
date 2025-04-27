/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:41:27 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/27 08:41:44 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_scene(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	 draw_floor_ceiling(data);
	data->player.angle = normalize_angle(data->player.angle);
	cast_rays(data, 0, 0);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
