/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/11/12 22:15:31 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	player_position(t_data *data, int x, int y)
{
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("WESN", data->map[y][x]))
			{
				if (data->map[y][x] == 'N')
					data->player.angle = 3 * M_PI_2;
				else if (data->map[y][x] == 'E')
					data->player.angle = M_PI;
				else if (data->map[y][x] == 'S')
					data->player.angle = M_PI_2;
				else if (data->map[y][x] == 'W')
					data->player.angle = 0;
				data->player.px = (x * SIZE) + SIZE / 2;
				data->player.py = (y * SIZE) + SIZE / 2;
				data->player.x = x;
				data->player.y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	free_pointer(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_all(t_data *data_struct, int i)
{
	int	j;

	free_pointer((void **)&data_struct->no);
	free_pointer((void **)&data_struct->so);
	free_pointer((void **)&data_struct->we);
	free_pointer((void **)&data_struct->ea);
	if (i == 0)
	{
		j = 0;
		while (j < 4)
		{
			if (data_struct->textur[j])
				mlx_delete_texture(data_struct->textur[j]);
			j++;
		}
		if (data_struct->map)
			free_2d_array(data_struct->map);
	}
}

int	main(int ac, char **av)
{
	t_data	map_struct;
	int		fd;

	if (ac != 2 || (ac == 2 && av[1] && !check_av_path(av[1], ft_strlen(av[1]),
				0)))
		return (ft_putstrn_fd("Error: Invalid arg", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstrn_fd("Error: Unable to open file", 2), 1);
	if (check_all(ac, &map_struct, fd))
		return (close(fd), free_all(&map_struct, 0), 1);
	close(fd);
	free_all(&map_struct, 1);
	player_position(&map_struct, 0, 0);
	check_map(&map_struct);
	map_struct.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	mlx_loop_hook(map_struct.mlx, &start_drawing, &map_struct);
	mlx_loop_hook(map_struct.mlx, &start_key_hook, &map_struct);
	mlx_loop(map_struct.mlx);
	free_all(&map_struct, 0);
	return (0);
}
