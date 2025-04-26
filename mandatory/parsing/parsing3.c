/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:53:07 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/26 22:05:54 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_null(char **split)
{
	if (!split)
		return (1);
	return (0);
}

static int	check_first_char(char **split, int i)
{
	if ((split[i][0] >= '0' && split[i][0] <= '9') && (split[i + 1]
		&& ((split[i + 1][0] >= '0' && split[i + 1][0] <= '9') 
		|| split[i + 1][0] == ',')))
		return (1);
	return (0);
}

static int	check(char **split, int i, int j)
{
	if (check_null(split))
		return (1);
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (check_first_char(split, i))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static char	*join_split_strings(char **split)
{
	char	*tmp;
	char	*ptr;
	int		i;

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
	return (ptr);
}

static char	*validate_split(char **split, char *name)
{
	if (array_length(split) < 2 || (split[0] && ft_strcmp(split[0], name) != 0))
		return (free_array_2d(split), print_str_fd("Error\nColor is invalid",
				2), NULL);
	if (check(split, 0, 0))
		return (free_array_2d(split), print_str_fd("Error\nColor is invalid",
				2), NULL);
	return (*split);
}

static char	*process_split(char *str, char *name)
{
	char	**split;
	char	*result;

	split = ft_split(str, "  \t\v\f\r");
	if (!validate_split(split, name))
		return (NULL);
	result = join_split_strings(split);
	free_array_2d(split);
	return (result);
}

static int	validate_commas_final(int commas)
{
	if (commas != 2)
		return (1);
	return (0);
}

static int	validate_commas_check(char *ptr, int *i, int *commas)
{
	while (ptr[*i])
	{
		if (ptr[*i] == ',' && ptr[*i + 1] != ',' && ptr[*i + 1] != '\0' 
			&& ptr[*i - 1] && ptr[*i - 1] != ',')
			(*commas)++;
		else if (ptr[*i] == ',' && (ptr[*i + 1] == ',' || ptr[*i + 1] == '\0'
				|| (ptr[*i - 1] && ptr[*i - 1] == ',')))
			return (1);
		(*i)++;
	}
	return (0);
}

static int	validate_commas_init(char *ptr, int *i, int *commas)
{
	if (!ptr)
		return (1);
	*i = 0;
	*commas = 0;
	return (0);
}

static int	validate_commas(char *ptr)
{
	int	i;
	int	commas;
	int	error;

	if (validate_commas_init(ptr, &i, &commas))
		return (1);
	
	error = validate_commas_check(ptr, &i, &commas);
	if (error)
		return (free(ptr), print_str_fd("Error\nToo many commas", 2), 1);
	
	if (validate_commas_final(commas))
		return (free(ptr), print_str_fd("Error\nToo many commas", 2), 1);
	
	return (0);
}

int	validate_color_string(char *ptr, char *name)
{
	int		i;
	char	*str;

	str = process_split(ptr, name);
	if (!str)
		return (1);
	if (validate_commas(str))
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ',' && (str[i] < '0' || str[i] > '9'))
			return (free(str), print_str_fd("Error\nColor is invalid", 2), 1);
		i++;
	}
	return (0);
}

char	**split_color_string(char *str)
{
	char	*ptr;
	char	**split;

	ptr = process_split(str, NULL);
	split = ft_split(ptr, ",");
	free(ptr);
	return (split);
}

int	store_color_values(int *map_color, char **split)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		map_color[i] = ft_atoi(split[i]);
		i++;
	}
	return (free_array_2d(split), 0);
}

int	parse_color(int *map_color, char *str, char *name)
{
	char	**split;

	if (validate_color_string(str, name))
		return (1);
	split = split_color_string(str);
	return (store_color_values(map_color, split));
}