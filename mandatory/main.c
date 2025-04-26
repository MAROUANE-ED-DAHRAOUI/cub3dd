/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:16:17 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 21:32:56 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	set_player_direction(t_data *data, char direction)
{
	if (direction == 'N')
		data->player.angle = 3 * M_PI_2;
	else if (direction == 'E')
		data->player.angle = M_PI;
	else if (direction == 'S')
		data->player.angle = M_PI_2;
	else if (direction == 'W')
		data->player.angle = 0;
}

static void	set_player_position(t_data *data, int x, int y)
{
	data->player.px = (x * SIZE) + SIZE / 2;
	data->player.py = (y * SIZE) + SIZE / 2;
	data->player.x = x;
	data->player.y = y;
}

static void	player_position(t_data *data, int x, int y)
{
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("WESN", data->map[y][x]))
			{
				set_player_direction(data, data->map[y][x]);
				set_player_position(data, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
}

void	safe_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	free_paths(t_data *data_struct)
{
	safe_free((void **)&data_struct->no);
	safe_free((void **)&data_struct->so);
	safe_free((void **)&data_struct->we);
	safe_free((void **)&data_struct->ea);
}

static void	free_textures(t_data *data_struct, int i)
{
	int	j;

	if (i == 0)
	{
		j = 0;
		while (j < 4)
		{
			if (data_struct->textur[j])
				mlx_delete_texture(data_struct->textur[j]);
			j++;
		}
	}
}

void	free_all(t_data *data_struct, int i)
{
	free_paths(data_struct);
	free_textures(data_struct, i);
	if (i == 0 && data_struct->map)
		free_array_2d(data_struct->map);
}

static int	handle_arguments_and_open_file(int ac, char **av, int *fd)
{
	if (ac != 2 || (ac == 2 && av[1] && !check_av_path(av[1], ft_strlen(av[1]), 0)))
		return (print_str_fd("Error: Invalid arg", 2), 1);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
		return (print_str_fd("Error: Unable to open file", 2), 1);
	return (0);
}

static int	validate_and_init_map(int fd, t_data *map_struct)
{
	if (check_all(2, map_struct, fd))
		return (close(fd), free_all(map_struct, 0), 1);
	close(fd);
	free_all(map_struct, 1);
	player_position(map_struct, 0, 0);
	check_map(map_struct);
	return (0);
}

static int	run_game(t_data *map_struct)
{
	map_struct->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	mlx_loop_hook(map_struct->mlx, &start_drawing, map_struct);
	mlx_loop_hook(map_struct->mlx, &start_key_hook, map_struct);
	mlx_loop(map_struct->mlx);
	free_all(map_struct, 0);
	return (0);
}


int	main(int ac, char **av)
{
	t_data	map_struct;
	int		fd;

	if (handle_arguments_and_open_file(ac, av, &fd))
		return (1);
	if (validate_and_init_map(fd, &map_struct))
		return (1);
	return (run_game(&map_struct));
}
