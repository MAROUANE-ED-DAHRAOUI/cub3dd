/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:28:44 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 23:06:04 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_hrz_intersection(t_data *data, t_dis_h *dis_h, double angle, double *ya)
{
	if (angle >= M_PI)
	{
		dis_h->y_h = floor(data->player.py / SIZE) * SIZE - 0.000001;
		*ya = -SIZE;
	}
	else
	{
		dis_h->y_h = floor((data->player.py) / SIZE) * SIZE + SIZE;
		*ya = SIZE;
	}
	dis_h->x_h = ((dis_h->y_h - data->player.py) / tan(angle))
		+ data->player.px;
}

void	find_hrz_wall_collision(t_data *data, t_dis_h *dis_h, double angle, double ya)
{
	while (1)
	{
		if (is_ray_blocked(data, dis_h->y_h, dis_h->x_h) == -1)
			break ;
		dis_h->y_h += ya;
		dis_h->x_h += ya / tan(angle);
	}
}

double	distance_hrz(t_data *data, t_dis_h *dis_h, double angle)
{
	double	hdis;
	double	ya;

	init_hrz_intersection(data, dis_h, angle, &ya);
	find_hrz_wall_collision(data, dis_h, angle, ya);
	hdis = ft_calculate_distance(data->player.px, data->player.py, dis_h->x_h, dis_h->y_h);
	return (hdis);
}

static void	calculate_initial_x(t_data *data, t_dis_v *dis_v, double angle, double *xa)
{
	if (angle > M_PI_2 && angle < M_PI_2 * 3)
	{
		dis_v->x_v = floor(data->player.px / SIZE) * SIZE - 0.000001;
		*xa = -SIZE;
	}
	else
	{
		dis_v->x_v = floor(data->player.px / SIZE) * SIZE + SIZE;
		*xa = SIZE;
	}
}

static void	cast_vertical_ray(t_data *data, t_dis_v *dis_v, double angle, double xa)
{
	dis_v->y_v = data->player.py + (dis_v->x_v - data->player.px) * tan(angle);
	while (1)
	{
		if (is_ray_blocked(data, dis_v->y_v, dis_v->x_v) == -1)
			break ;
		dis_v->x_v += xa;
		dis_v->y_v += xa * tan(angle);
	}
}

double	distance_vrt(t_data *data, t_dis_v *dis_v, double angle)
{
	double	vdis;
	double	xa;

	calculate_initial_x(data, dis_v, angle, &xa);
	cast_vertical_ray(data, dis_v, angle, xa);
	vdis = ft_calculate_distance(data->player.px, data->player.py, dis_v->x_v, dis_v->y_v);
	return (vdis);
}

double calculate_horizontal(t_data *data, t_dis_h *dis_h, double rayangle)
{
    return distance_hrz(data, dis_h, rayangle);
}

double calculate_vertical(t_data *data, t_dis_v *dis_v, double rayangle)
{
    return distance_vrt(data, dis_v, rayangle);
}

double determine_shortest(t_dis_h *dis_h, t_dis_v *dis_v, double vdis, double hdis)
{
    if (vdis < hdis && vdis > 0)
    {
        dis_h->wall_type = 'N';
        dis_v->inter_type_v = 'V';
        return (vdis);
    }
    else
    {
        dis_v->inter_type_v = 'N';
        dis_h->wall_type = 'H';
        return (hdis);
    }
}

double cal_distance(t_data *data, t_dis_h *dis_h, t_dis_v *dis_v, double rayangle)
{
    double vdis = calculate_vertical(data, dis_v, rayangle);
    double hdis = calculate_horizontal(data, dis_h, rayangle);
    return determine_shortest(dis_h, dis_v, vdis, hdis);
}

void	init_raycasting(t_data *data, double *rayangle, double *angle, t_rays **rays)
{
	*rayangle = data->player.angle - FOV / 2;
	*angle = FOV / WIDTH;
	*rays = malloc(sizeof(t_rays) * WIDTH);
}

void	calculate_ray(t_data *data, t_rays *ray, double rayangle, double *dis)
{
	*dis = cal_distance(data, &ray->dis_h, &ray->dis_v, rayangle);
	*dis = *dis * cos(data->player.angle - rayangle);
	ray->rayangle = rayangle;
}

void	cast_rays(t_data *data, int i, double dis)
{
	double	rayangle;
	double	angle;
	double	line_height;
	t_rays	*rays;

	init_raycasting(data, &rayangle, &angle, &rays);
	while (i < WIDTH)
	{
		rayangle = normalize_angle(rayangle);
		calculate_ray(data, &rays[i], rayangle, &dis);
		line_height = (SIZE / dis) * (WIDTH / 2) / tan(FOV / 2);
		render_wall(data, line_height, i, rays[i]);
		rayangle += angle;
		i++;
	}
	free(rays);
}