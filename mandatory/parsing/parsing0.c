/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:28:22 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 21:32:56 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_file(int fd, t_helper *helper, int isgood)
{
	while (helper->line != NULL)
	{
		helper->trim_line = ft_strtrim(helper->line, " \t\v\f\r");
		if (!ft_strcmp(helper->trim_line, "\n"))
		{
			free(helper->trim_line);
			helper->trim_line = NULL;
		}
		else
		{
			isgood = 1;
			helper->res = process_line(helper->trim_line, &helper->ptr_line,
					helper->find);
			free(helper->trim_line);
			if (helper->res == 0)
				break ;
			else if (helper->res == 1)
				return (free(helper->line), free(helper->ptr_line), 1);
		}
		free(helper->line);
		helper->line = get_next_line(fd);
	}
	if (isgood == 0)
		return (free(helper->line), print_str_fd("Error: Empty file", 2), 1);
	return (0);
}
