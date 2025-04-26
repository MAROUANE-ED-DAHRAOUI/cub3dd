/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:16:31 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 16:26:59 by med-dahr         ###   ########.fr       */
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

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(data->image, x++, y, color_pixel(data->c));
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(data->image, x++, y, color_pixel(data->f));
		y++;
	}
}

void	draw_f_c(t_data *data)
{
	draw_ceiling(data);
	draw_floor(data);
}
int	handle_vertical_case(double rayangle)
{
	if (rayangle > M_PI_2 && rayangle < 3 * M_PI_2)
		return (2);
	else
		return (3);
}

int	handle_horizontal_case(double rayangle)
{
	if (rayangle > M_PI && rayangle < 2 * M_PI)
		return (1);
	else
		return (0);
}

int	tex_index(t_dis_h dis_h, t_dis_v dis_v, double rayangle)
{
	if (dis_v.inter_type_v == 'V')
		return (handle_vertical_case(rayangle));
	else if (dis_h.inter_type_h == 'H')
		return (handle_horizontal_case(rayangle));
	return (-1);
}

double	calculate_horizontal_tex_x(t_data *data, t_rays rays, int texture_index)
{
	return ((rays.dis_h.x_h / SIZE) - floor(rays.dis_h.x_h / SIZE))
			* data->textur[texture_index]->width;
}

double	calculate_vertical_tex_x(t_data *data, t_rays rays, int texture_index)
{
	return ((rays.dis_v.y_v / SIZE) - floor(rays.dis_v.y_v / SIZE))
			* data->textur[texture_index]->width;
}

double	calculate_tex_x(t_data *data, t_rays rays, int texture_index)
{
	if (rays.dis_h.inter_type_h == 'H')
		return calculate_horizontal_tex_x(data, rays, texture_index);
	else if (rays.dis_v.inter_type_v == 'V')
		return calculate_vertical_tex_x(data, rays, texture_index);
	return 0;
}

bool	validate_texture_coords(t_data *data, double tex_x, double tex_y,
		int texture_index)
{
	if (tex_x < 0 || tex_y < 0
		|| (uint32_t)tex_x >= data->textur[texture_index]->width
		|| (uint32_t)tex_y >= data->textur[texture_index]->height)
		return (false);
	return (true);
}

uint32_t	get_pixel_color(t_data *data, double tex_x, double tex_y,
		int texture_index)
{
	int		index;

	index = ((int)tex_y * data->textur[texture_index]->width
			* data->textur[texture_index]->bytes_per_pixel) + ((int)tex_x
			* data->textur[texture_index]->bytes_per_pixel);
	return (colorr(&data->textur[texture_index]->pixels[index]));
}

uint32_t	get_color(t_data *data, t_rays rays, double tex_y,
		int texture_index)
{
	double	tex_x;

	tex_x = calculate_tex_x(data, rays, texture_index);
	if (!validate_texture_coords(data, tex_x, tex_y, texture_index))
		return (0);
	return (get_pixel_color(data, tex_x, tex_y, texture_index));
}
