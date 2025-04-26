/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:47:58 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 22:07:49 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_textures_and_colors(t_data *data_struct, int i)
{
	data_struct->no = NULL;
	data_struct->so = NULL;
	data_struct->we = NULL;
	data_struct->ea = NULL;
	while (i < 4)
		data_struct->textur[i++] = NULL;
}

static void	init_remaining_data(t_data *data_struct, int i)
{
	i = 0;
	while (i < 3)
	{
		data_struct->f[i] = -1;
		data_struct->c[i] = -1;
		i++;
	}
	data_struct->map = NULL;
}

static void	init_data_struct(t_data *data_struct, int i)
{
	init_textures_and_colors(data_struct, i);
	init_remaining_data(data_struct, i);
}

int	init_helper(t_helper *helper, int fd)
{
	int	i;

	helper->res = 0;
	helper->ptr_line = NULL;
	helper->trim_line = NULL;
	i = 0;
	while (i < 6)
		helper->find[i++] = 0;
	helper->line = get_next_line(fd);
	if (helper->line == NULL)
		return (print_str_fd("Error: Empty file", 2), 1);
	return (0);
}

int	 initialize_data(t_data *data_struct, t_helper *helper, int fd)
{
	init_data_struct(data_struct, 0);
	return (init_helper(helper, fd));
}
