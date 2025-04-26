/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:57 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 21:32:30 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	floodfill_check(char **map, int row, int col)
{
	if (!map[row][col] || map[row][col] == '1')
		return (0);
	if (map[row][col] != '1')
	{
		if (valid_path(map, row, col) == -1)
			return (-1);
	}
	return (1);
}

int	floodfill_fill(char **map, int row, int col)
{
	if (floodfill_check(map, row, col) <= 0)
		return (floodfill_check(map, row, col));
		
	if (map[row][col] != '1')
		map[row][col] = '1';
	if (floodfill_fill(map, row + 1, col) == -1)
		return (-1);
	if (floodfill_fill(map, row - 1, col) == -1)
		return (-1);
	if (floodfill_fill(map, row, col + 1) == -1)
		return (-1);
	if (floodfill_fill(map, row, col - 1) == -1)
		return (-1);
	return (0);
}

int	floodfill(char **map, int row, int col)
{
	return (floodfill_fill(map, row, col));
}

static int	check_player_pos(t_data *data)
{
	int	x;
	int	y;

	x = data->player.x;
	y = data->player.y;
	if (x == 0 || x == _strlen(data->map[y]))
		return (-1);
	if (y == 0 || y == array_length(data->map))
		return (-1);
	return (0);
}

static int	check_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_strchr("10SWEN ", data->map[i][j]) == NULL)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check_map_chars(t_data *data)
{
	if (valid_char(data->map, data) == -1)
		put_err("Error: No direction in the map.", data);
	if (check_player_pos(data))
		put_err("Error: Player position is invalid", data);
	if (check_chars(data))
		put_err("Error: Invalid character in the map", data);
}

void	check_map_floodfill(t_data *data, char **cpy_arr)
{
	while (found_zero_index(cpy_arr, data))
	{
		if (floodfill(cpy_arr, data->player.y, data->player.x))
		{
			free_array_2d(cpy_arr);
			put_err("Error: Invalid map", data);
		}
	}
}

void	check_map(t_data *data)
{
	char	**cpy_arr;

	check_map_chars(data);
	cpy_arr = copy_arr(data->map);
	check_map_floodfill(data, cpy_arr);
	free_array_2d(cpy_arr);
}