/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:20:39 by kadam             #+#    #+#             */
/*   Updated: 2024/11/15 20:50:53 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_av_path(char *str, int len, int index)
{
	int	fd;

	if (index == 0)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
			&& str[len - 4] == '.')
			return (1);
	}
	else if (index == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_putstrn_fd("Error\nInvalid path\n", 2), 1);
		close(fd);
	}
	return (0);
}

int	process_path(char **str, int i, char *name, char **path)
{
	char	**split;
	char	*joined_path;
	int		j;
	char	*temp;

	split = ft_split(str[i], " \t\v\f\r");
	if (split[0] && ft_strcmp(split[0], name) != 0)
		return (free_2d_array(split),
			ft_putstrn_fd("Error\nYOU HAVE TO SET ALL THE PATHS", 2),
			1);
	joined_path = ft_strdup(split[1]);
	j = 2;
	while (split[j] != NULL)
	{
		temp = ft_strjoin(joined_path, " ");
		free(joined_path);
		joined_path = ft_strjoin(temp, split[j]);
		free(temp);
		j++;
	}
	if (check_av_path(joined_path, 0, 1) == 1)
		return (free(joined_path), free_2d_array(split), 1);
	free(*path);
	return (*path = joined_path, free_2d_array(split), 0);
}

static int	load_img(t_data *data)
{
	int	i;

	data->textur[0] = mlx_load_png(data->no);
	data->textur[1] = mlx_load_png(data->so);
	data->textur[2] = mlx_load_png(data->we);
	data->textur[3] = mlx_load_png(data->ea);
	if (!data->textur[0] || !data->textur[1] || !data->textur[2]
		|| !data->textur[3])
	{
		i = 0;
		while (i < 4)
		{
			if (data->textur[i])
			{
				mlx_delete_texture(data->textur[i]);
				data->textur[i] = NULL;
			}
			i++;
		}
		return (ft_putstrn_fd("Error\nUnable to load texture\n", 2), 1);
	}
	return (0);
}

int	check_all(int ac, t_data *data_struct, int fd)
{
	t_helper	helper;

	if (init_struct(data_struct, &helper, fd))
		return (1);
	if (read_file(fd, &helper, 0))
		return (1);
	if (read_map(helper.line, fd, data_struct, helper.ptr_line))
		return (free(helper.ptr_line), free(helper.line), 1);
	free(helper.ptr_line);
	ac = 0;
	while (ac < 3)
	{
		if (data_struct->f[ac] < 0 || data_struct->f[ac] > 255
			|| data_struct->c[ac] < 0 || data_struct->c[ac] > 255)
			return (ft_putstrn_fd("Error\nInvalid color\n", 2), 1);
		ac++;
	}
	if (data_struct->map == NULL)
		return (ft_putstrn_fd("Error\n: The map is empty", 2), 1);
	if (load_img(data_struct))
		return (1);
	return (0);
}
