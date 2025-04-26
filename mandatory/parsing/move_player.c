/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:54:14 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 19:58:48 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_forward_backward(t_data *data, double *new_px, double *new_py)
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
}

static void	handle_left_right(t_data *data, double *new_px, double *new_py)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
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

static void	handle_movement(t_data *data, double *new_px, double *new_py)
{
	handle_forward_backward(data, new_px, new_py);
	handle_left_right(data, new_px, new_py);
}

void	handle_player_actions(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
	
	data->player.angle = fmod(data->player.angle, 2 * M_PI);
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
}

void	key_hook(t_data *data)
{
	double	new_px;
	double	new_py;

	new_px = data->player.px;
	new_py = data->player.py;
	handle_movement(data, &new_px, &new_py);
	
	handle_player_actions(data);
	
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
