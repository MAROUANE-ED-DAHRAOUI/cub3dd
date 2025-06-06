/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:43:06 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 22:19:54 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_vertical(t_data *data, double py, double px, double num_pix)
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
	return (0);
}

int	check_horizontal(t_data *data, double py, double px, double num_pix)
{
	int	y;
	int	x;

	y = py / SIZE;
	x = (px + num_pix) / SIZE;
	if (data->map[y][x] && data->map[y][x] == '1')
		return (-1);
	x = (px - num_pix) / SIZE;
	if (x >= 0 && data->map[y][x] == '1')
		return (-1);
	return (0);
}

int	is_valid_position(t_data *data, double py, double px, double num_pix)
{
	if (check_vertical(data, py, px, num_pix) == -1)
		return (-1);
	if (check_horizontal(data, py, px, num_pix) == -1)
		return (-1);
	return (0);
}

double	ft_calculate_distance(double xp, double yp, double x, double y)
{
	double	dx;
	double	dy;

	dx = x - xp;
	dy = y - yp;
	return (sqrt(dx * dx + dy * dy));
}

int	check_map_bounds(t_data *data, double y, double x)
{
	int	ay;
	int	ax;

	ay = y / SIZE;
	ax = x / SIZE;
	if (ay < 0 || ay >= array_length(data->map) || ax >= _strlen(data->map[ay])
		|| ax < 0)
		return (-1);
	return (0);
}

int	check_wall_collision(t_data *data, double y, double x)
{
	int	ay;
	int	ax;

	ay = y / SIZE;
	ax = x / SIZE;
	if (data->map[ay][ax] && data->map[ay][ax] == '1')
		return (-1);
	return (0);
}

int	is_ray_blocked(t_data *data, double y, double x)
{
	if (check_map_bounds(data, y, x) == -1)
		return (-1);
	if (is_valid_position(data, y, x, 0.000001) == -1)
		return (-1);
	if (check_wall_collision(data, y, x) == -1)
		return (-1);
	return (0);
}

void	calculate_drawing_boundaries(double line_height, double *top, double *bot, double *j)
{
	*top = (HEIGHT / 2) - (line_height / 2);
	*j = *top;
	*bot = (HEIGHT / 2) + (line_height / 2);
	if (*top < 0)
		*top = 0;
	if (*bot > HEIGHT)
		*bot = HEIGHT;
}

uint32_t	get_texture_pixel_color(t_data *data, t_rays rays, double top, 
								double j, double line_height, int  get_texture_indexx)
{
	double	tex_y;
	
	tex_y = ((top - j) / line_height) * data->textur[ get_texture_indexx]->height;
	return ( sample_texture(data, rays, tex_y,  get_texture_indexx));
}

void	render_wall(t_data *data, double line_height, double i, t_rays rays)
{
	double	top;
	double	bot;
	int		 get_texture_indexx;
	double	j;

	 get_texture_indexx =  get_texture_index(rays.dis_h, rays.dis_v, rays.rayangle);
	calculate_drawing_boundaries(line_height, &top, &bot, &j);
	while (top < bot)
	{
		mlx_put_pixel(data->image, i, top, 
			get_texture_pixel_color(data, rays, top, j, line_height,  get_texture_indexx));
		top++;
	}
}