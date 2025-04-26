/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:23:08 by kadam             #+#    #+#             */
/*   Updated: 2024/11/15 21:03:10 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check(char **split, int i, int j)
{
	if (!split)
		return (1);
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if ((split[i][0] >= '0' && split[i][0] <= '9') && (split[i + 1]
				&& ((split[i + 1][0] >= '0' && split[i + 1][0] <= '9') 
				|| split[i + 1][0] == ',')))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static char	*process_split(char *str, char *name)
{
	char	**split;
	char	*tmp;
	char	*ptr;
	int		i;

	split = ft_split(str, "  \t\v\f\r");
	if (ft_lenarray(split) < 2 || (split[0] && ft_strcmp(split[0], name) != 0))
		return (free_2d_array(split), ft_putstrn_fd("Error\nColor is invalid",
				2), NULL);
	if (check(split, 0, 0))
		return (free_2d_array(split), ft_putstrn_fd("Error\nColor is invalid",
				2), NULL);
	tmp = NULL;
	ptr = NULL;
	i = 1;
	while (split[i])
	{
		tmp = ft_strjoin(ptr, split[i]);
		free(ptr);
		ptr = tmp;
		i++;
	}
	free_2d_array(split);
	return (ptr);
}

static int	validate_commas(char *ptr)
{
	int	i;
	int	commas;

	if (!ptr)
		return (1);
	i = 0;
	commas = 0;
	while (ptr[i])
	{
		if (ptr[i] == ',' && ptr[i + 1] != ',' && ptr[i + 1] != '\0' && ptr[i
				- 1] && ptr[i - 1] != ',')
			commas++;
		else if (ptr[i] == ',' && (ptr[i + 1] == ',' || ptr[i + 1] == '\0'
				|| (ptr[i - 1] && ptr[i - 1] == ',')))
			return (free(ptr), ft_putstrn_fd("Error\nToo many commas", 2), 1);
		i++;
	}
	if (commas != 2)
		return (free(ptr), ft_putstrn_fd("Error\nToo many commas", 2), 1);
	return (0);
}

int	process_color(int *map_color, char *str, char *name)
{
	char	*ptr;
	int		i;
	char	**split;

	ptr = process_split(str, name);
	if (validate_commas(ptr))
		return (1);
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] != ',' && (ptr[i] < '0' || ptr[i] > '9'))
			return (free(ptr), ft_putstrn_fd("Error\nColor is invalid", 2), 1);
		i++;
	}
	split = ft_split(ptr, ",");
	free(ptr);
	i = 0;
	while (i < 3)
	{
		map_color[i] = ft_atoi(split[i]);
		i++;
	}
	return (free_2d_array(split), 0);
}
