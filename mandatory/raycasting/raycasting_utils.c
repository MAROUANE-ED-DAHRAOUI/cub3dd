/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:57:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/08 12:56:29 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_pos(t_data *data, double py, double px, double num_pix)
{
	int	y;
	int	x;

	x = px / SIZE;
	y = (py + num_pix) / SIZE;
	if (data->map[y] && data->map[y][x] == '1')
		return (-1);
	y = (py - num_pix) / SIZE;
	if (y >= 0 && data->map[y][x] == '1')
		return (-1);
	y = py / SIZE;
	x = (px + num_pix) / SIZE;
	if (data->map[y][x] && data->map[y][x] == '1')
		return (-1);
	x = (px - num_pix) / SIZE;
	if (x >= 0 && data->map[y][x] == '1')
		return (-1);
	return (0);
}

double	cal_dis(double xp, double yp, double x, double y)
{
	double	dx;
	double	dy;

	dx = x - xp;
	dy = y - yp;
	return (sqrt(dx * dx + dy * dy));
}

int	check_ray(t_data *data, double y, double x)
{
	int	ay;
	int	ax;

	ay = y / SIZE;
	ax = x / SIZE;
	if (ay < 0 || ay >= ft_lenarray(data->map) || ax >= _strlen(data->map[ay])
		|| ax < 0)
		return (-1);
	if (check_pos(data, y, x, 0.000001) == -1)
		return (-1);
	if (data->map[ay][ax] && data->map[ay][ax] == '1')
		return (-1);
	return (0);
}

void	draw_3d(t_data *data, double line_height, double i, t_rays rays)
{
	double	top;
	double	bot;
	double	tex_y;
	int		tex_indexx;
	double	j;

	tex_indexx = tex_index(rays.dis_h, rays.dis_v, rays.rayangle);
	top = (HEIGHT / 2) - (line_height / 2);
	j = top;
	bot = (HEIGHT / 2) + (line_height / 2);
	if (top < 0)
		top = 0;
	if (bot > HEIGHT)
		bot = HEIGHT;
	while (top < bot)
	{
		tex_y = ((top - j) / line_height) * data->textur[tex_indexx]->height;
		mlx_put_pixel(data->image, i, top, get_color(data, rays, tex_y,
				tex_indexx));
		top++;
	}
}
