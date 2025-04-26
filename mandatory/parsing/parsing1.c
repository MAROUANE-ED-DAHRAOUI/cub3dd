/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:27:54 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 18:27:56 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_file_access(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putstrn_fd("Error\nInvalid path\n", 2), 1);
	close(fd);
	return (0);
}

int	check_file_extension(char *str, int len)
{
	if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
		&& str[len - 4] == '.')
		return (1);
	return (0);
}

int	check_av_path(char *str, int len, int index)
{
	if (index == 0)
		return (check_file_extension(str, len));
	else if (index == 1)
		return (check_file_access(str));
	return (0);
}

int	final_processing(char *joined_path, char **path, char **split)
{
	if (check_av_path(joined_path, 0, 1) == 1)
	{
		free(joined_path);
		free_2d_array(split);
		return (1);
	}
	free(*path);
	*path = joined_path;
	free_2d_array(split);
	return (0);
}

char	*join_path_components(char **split)
{
	char	*joined_path;
	char	*temp;
	int		j;

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
	return (joined_path);
}

int	initial_processing(char **str, int i, char *name, char ***split_ptr)
{
	char	**split;

	split = ft_split(str[i], " \t\v\f\r");
	*split_ptr = split;
	if (split[0] && ft_strcmp(split[0], name) != 0)
	{
		free_2d_array(split);
		ft_putstrn_fd("Error\nYOU HAVE TO SET ALL THE PATHS", 2);
		return (1);
	}
	return (0);
}

int	process_path(char **str, int i, char *name, char **path)
{
	char	**split;
	char	*joined_path;
	int		result;

	if (initial_processing(str, i, name, &split))
		return (1);
	joined_path = join_path_components(split);
	result = final_processing(joined_path, path, split);
	return (result);
}

static int	load_textures(t_data *data)
{
	data->textur[0] = mlx_load_png(data->no);
	data->textur[1] = mlx_load_png(data->so);
	data->textur[2] = mlx_load_png(data->we);
	data->textur[3] = mlx_load_png(data->ea);
	if (!data->textur[0] || !data->textur[1] || !data->textur[2] || !data->textur[3])
		return (1);
	return (0);
}

static void	cleanup_textures(t_data *data)
{
	int	i;

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
}

static int	load_img(t_data *data)
{
	if (load_textures(data))
	{
		cleanup_textures(data);
		return (ft_putstrn_fd("Error\nUnable to load texture\n", 2), 1);
	}
	return (0);
}

int	init_and_read(int fd, t_data *data_struct)
{
	t_helper	helper;

	if (init_struct(data_struct, &helper, fd))
		return (1);
	if (read_file(fd, &helper, 0))
		return (1);
	if (read_map(helper.line, fd, data_struct, helper.ptr_line))
		return (free(helper.ptr_line), free(helper.line), 1);
	free(helper.ptr_line);
	return (0);
}

int	validate_data(t_data *data_struct)
{
	int	ac;

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
	return (0);
}

int	check_all(int ac, t_data *data_struct, int fd)
{
	(void)ac;
	if (init_and_read(fd, data_struct))
		return (1);
	if (validate_data(data_struct))
		return (1);
	if (load_img(data_struct))
		return (1);
	return (0);
}
