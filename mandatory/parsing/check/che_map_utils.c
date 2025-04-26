/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   che_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:13:31 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 21:31:51 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_borders(char **map, int y, int x)
{
	if (!ft_strchr("1 ", map[y][x]) && (y == 0 || y == array_length(map) - 1))
		return (-1);
	if (map[y][x] == '0' && (y == 0 || y == array_length(map) - 1))
		return (-1);
	return (0);
}

int	check_adjacent_cells(char **map, int y, int x)
{
	if (!map[y][x + 1] || !ft_strchr("1WESN0", map[y][x + 1]))
		return (-1);
	if (!ft_strchr("1WESN0", map[y][x - 1]))
		return (-1);
	if (y > 0 && (x >= _strlen(map[y - 1]) || !ft_strchr("1WESN0", map[y - 1][x])))
		return (-1);
	if (y != array_length(map) - 1 && (x >= _strlen(map[y + 1])
			|| !ft_strchr("1WESN0", map[y + 1][x])))
		return (-1);
	return (0);
}

int	valid_path(char **map, int y, int x)
{
	if (check_borders(map, y, x) == -1)
		return (-1);
	if (check_adjacent_cells(map, y, x) == -1)
		return (-1);
	return (0);
}

int	check_position(char **arr, int x, int y, t_data *data)
{
	if (arr[y][x] == '0' || ft_strchr("WESN", arr[y][x]))
	{
		data->player.x = x;
		data->player.y = y;
		return (1);
	}
	return (0);
}

int	scan_row(char **arr, int y, t_data *data)
{
	int	x;

	x = 0;
	while (arr[y][x])
	{
		if (check_position(arr, x, y, data))
			return (1);
		x++;
	}
	return (0);
}

int	found_zero_index(char **arr, t_data *data)
{
	int	y;

	y = 0;
	while (arr[y])
	{
		if (scan_row(arr, y, data))
			return (1);
		y++;
	}
	return (0);
}

int	check_duplicate_directions(char **arr, t_data *data)
{
	int		y;
	int		x;
	bool	is_exist;

	y = 0;
	is_exist = true;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (ft_strchr("WESN", arr[y][x]) && is_exist == true)
				is_exist = false;
			else if (ft_strchr("WESN", arr[y][x]) && is_exist == false)
				put_err("Error: Multiple directions.", data);
			x++;
		}
		y++;
	}
	return (is_exist);
}

int	validate_direction_existence(bool is_exist)
{
	if (is_exist == true)
		return (-1);
	return (0);
}

int	valid_char(char **arr, t_data *data)
{
	bool	is_exist;

	is_exist = check_duplicate_directions(arr, data);
	return (validate_direction_existence(is_exist));
}
