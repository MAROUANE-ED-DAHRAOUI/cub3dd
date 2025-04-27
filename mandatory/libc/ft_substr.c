/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:40:24 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/27 08:40:32 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*dest;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start >= (size_t)ft_strlen(s))
		return (dest = ft_strdup(""), dest);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[start++];
	dest[len] = '\0';
	return (dest);
}
