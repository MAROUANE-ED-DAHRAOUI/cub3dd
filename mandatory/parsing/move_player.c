/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 21:00:50 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_movement(t_data *data, double *new_px, double *new_py)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*new_px += cos(data->player.angle) * MOVE_SPEED;
		*new_py += sin(data->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*new_px -= cos(data->player.angle) * MOVE_SPEED;
		*new_py -= sin(data->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		*new_px += sin(data->player.angle) * MOVE_SPEED;
		*new_py -= cos(data->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		*new_px -= sin(data->player.angle) * MOVE_SPEED;
		*new_py += cos(data->player.angle) * MOVE_SPEED;
	}
}

void	key_hook(t_data *data)
{
	double	new_px;
	double	new_py;

	new_px = data->player.px;
	new_py = data->player.py;
	handle_movement(data, &new_px, &new_py);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
	data->player.angle = fmod(data->player.angle, 2 * M_PI);
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	if (check_pos(data, new_py, new_px, 4) == 0)
	{
		data->player.px = new_px;
		data->player.py = new_py;
	}
}

void	start_key_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	key_hook(data);
}
