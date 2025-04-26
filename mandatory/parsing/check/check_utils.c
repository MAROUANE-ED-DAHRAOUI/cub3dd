/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:10:05 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 21:32:56 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**copy_arr(char **array)
{
	int		i;
	int		y;
	char	**arr;

	i = 0;
	y = array_length(array);
	arr = malloc((y + 1) * sizeof(char *));
	while (array[i])
	{
		arr[i] = ft_strdup(array[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	put_err(char *str, t_data *s_map)
{
	free_all(s_map, 0);
	print_str_fd(str, 2);
	exit(EXIT_FAILURE);
}
