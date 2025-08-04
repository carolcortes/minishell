/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:16:51 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/20 14:40:22 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *b)
{
	char	*block;
	int		bytes;

	block = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!block)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, block, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(block);
			return (NULL);
		}
		block[bytes] = '\0';
		b = ft_joinstr(b, block);
		if (ft_strchr(block, '\n'))
			break ;
	}
	free(block);
	return (b);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1 + (buffer[i] == '\n')));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = update_line(buffer);
	return (line);
}
