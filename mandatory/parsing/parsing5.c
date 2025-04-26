/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:07:56 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 21:07:56 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_data_struct(t_data *data_struct, int i)
{
	data_struct->no = NULL;
	data_struct->so = NULL;
	data_struct->we = NULL;
	data_struct->ea = NULL;
	while (i < 4)
		data_struct->textur[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		data_struct->f[i] = -1;
		data_struct->c[i] = -1;
		i++;
	}
	data_struct->map = NULL;
}

int	init_struct(t_data *data_struct, t_helper *helper, int fd)
{
	int	i;

	init_data_struct(data_struct, 0);
	helper->res = 0;
	helper->ptr_line = NULL;
	helper->trim_line = NULL;
	i = 0;
	while (i < 6)
		helper->find[i++] = 0;
	helper->line = get_next_line(fd);
	if (helper->line == NULL)
		return (ft_putstrn_fd("Error: Empty file", 2), 1);
	return (0);
}
