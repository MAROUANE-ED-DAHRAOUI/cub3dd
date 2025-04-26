/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:34:32 by kadam             #+#    #+#             */
/*   Updated: 2024/11/08 12:56:29 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	color_pixel(int *arr)
{
	return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0xFF);
}

static uint32_t	colorr(uint8_t *arr)
{
	return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3]);
}

void	draw_f_c(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(data->image, x++, y, color_pixel(data->c));
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(data->image, x++, y, color_pixel(data->f));
		y++;
	}
}

int	tex_index(t_dis_h dis_h, t_dis_v dis_v, double rayangle)
{
	if (dis_v.inter_type_v == 'V')
	{
		if (rayangle > M_PI_2 && rayangle < 3 * M_PI_2)
			return (2);
		else
			return (3);
	}
	else if (dis_h.inter_type_h == 'H')
	{
		if (rayangle > M_PI && rayangle < 2 * M_PI)
			return (1);
		else
			return (0);
	}
	return (-1);
}

uint32_t	get_color(t_data *data, t_rays rays, double tex_y,
		int texture_index)
{
	double	tex_x;
	int		index;

	tex_x = 0;
	if (rays.dis_h.inter_type_h == 'H')
		tex_x = ((rays.dis_h.x_h / SIZE) - floor(rays.dis_h.x_h / SIZE))
			* data->textur[texture_index]->width;
	else if (rays.dis_v.inter_type_v == 'V')
		tex_x = ((rays.dis_v.y_v / SIZE) - floor(rays.dis_v.y_v / SIZE))
			* data->textur[texture_index]->width;
	if (tex_x < 0 || tex_y < 0
		|| (uint32_t)tex_x >= data->textur[texture_index]->width
		|| (uint32_t)tex_y >= data->textur[texture_index]->height)
		return (0);
	index = ((int)tex_y * data->textur[texture_index]->width
			* data->textur[texture_index]->bytes_per_pixel) + ((int)tex_x
			* data->textur[texture_index]->bytes_per_pixel);
	return (colorr(&data->textur[texture_index]->pixels[index]));
}
