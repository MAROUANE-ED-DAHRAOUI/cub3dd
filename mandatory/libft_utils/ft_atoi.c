/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:25:16 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 20:46:46 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_sign(const char *str, int *i)
{
	if (str[*i] == '-')
		return (-1);
	if (str[*i] == '+')
	{
		if (str[*i + 1] && (str[*i + 1] == '-' || str[*i + 1] == '+'))
			return (-1);
		(*i)++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	old;
	int	i;

	result = 0;
	old = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (handle_sign(str, &i) == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		old = result;
		result = result * 10 + str[i] - '0';
		if (old != (result / 10))
			return (-1);
		i++;
	}
	return (result);
}
