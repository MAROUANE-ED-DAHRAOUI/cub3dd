/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/06 10:54:49 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *save)
{
	char	*buffer;
	int		byte;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (byte != 0 && chr_n(save) == -1)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buffer);
			buffer = NULL;
			free(save);
			save = NULL;
			return (buffer);
		}
		buffer[byte] = '\0';
		save = _strjoin(save, buffer);
	}
	free(buffer);
	buffer = NULL;
	return (save);
}

char	*ft_line(char *save)
{
	char	*line;
	int		i;
	int		index;

	if (ft_strlen(save) == 0)
		return (NULL);
	index = chr_n(save);
	if (index == -1)
		return (ft_strdup(save));
	line = malloc(index + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (i < index)
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	char	*str;
	int		index;

	index = chr_n(save);
	if (index != -1)
	{
		str = ft_strdup(save + index + 1);
		free(save);
		save = NULL;
		return (str);
	}
	free(save);
	save = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (BUFFER_SIZE <= 0 || (fd <= 2 && fd == -1))
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = ft_line(save);
	save = ft_save(save);
	return (line);
}
