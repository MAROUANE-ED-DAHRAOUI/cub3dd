/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:38:45 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/27 08:38:58 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (ft_strlen(s2) == 1 && s2[0] == '\n')
	{
		free(s2);
		free(s1);
		return (NULL);
	}
	dlen = ft_strlen(s1);
	slen = ft_strlen(s2);
	str = malloc((dlen + slen + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	ft_cpy(str, s1, dlen);
	ft_cpy(str + dlen, s2, slen);
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}
