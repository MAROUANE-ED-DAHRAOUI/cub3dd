/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:50:23 by kadam             #+#    #+#             */
/*   Updated: 2024/09/04 18:30:41 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static size_t	check_rep(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static size_t	find_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (check_rep(s1[i], set) == 1)
		i++;
	return (i);
}

static size_t	find_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	len;

	len = ft_strlen(s1);
	if (len == 0)
		return (0);
	end = len - 1;
	while (check_rep(s1[end], set) == 1 && end > 0)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	n;
	size_t	i;
	size_t	start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	start = find_start(s1, set);
	if ((s1[0] == '\0' && set[0] == '\0') || s1[0] == '\0'
		|| start > find_end(s1, set))
	{
		dest = ft_strdup("");
		return (dest);
	}
	n = find_end(s1, set) - start + 1;
	dest = malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (dest);
	while (i < n)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}
