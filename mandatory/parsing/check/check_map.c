/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:54:47 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/12 22:18:53 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	floodfill(char **map, int row, int col)
{
	if (!map[row][col] || map[row][col] == '1')
		return (0);
	if (map[row][col] != '1')
	{
		if (valid_path(map, row, col) == -1)
			return (-1);
	}
	if (map[row][col] != '1')
		map[row][col] = '1';
	if (floodfill(map, row + 1, col) == -1)
		return (-1);
	if (floodfill(map, row - 1, col) == -1)
		return (-1);
	if (floodfill(map, row, col + 1) == -1)
		return (-1);
	if (floodfill(map, row, col - 1) == -1)
		return (-1);
	return (0);
}

static int	check_player_pos(t_data *data)
{
	int	x;
	int	y;

	x = data->player.x;
	y = data->player.y;
	if (x == 0 || x == _strlen(data->map[y]))
		return (-1);
	if (y == 0 || y == ft_lenarray(data->map))
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

void	check_map(t_data *data)
{
	char	**cpy_arr;

	if (valid_char(data->map, data) == -1)
		put_err("Error: No direction in the map.", data);
	if (check_player_pos(data))
		put_err("Error: Player position is invalid", data);
	if (check_chars(data))
		put_err("Error: Invalid character in the map", data);
	cpy_arr = copy_arr(data->map);
	while (found_zero_index(cpy_arr, data))
	{
		if (floodfill(cpy_arr, data->player.y, data->player.x))
		{
			free_2d_array(cpy_arr);
			put_err("Error: Invalid map", data);
		}
	}
	free_2d_array(cpy_arr);
}
