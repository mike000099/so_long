/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:58:18 by yseddouk          #+#    #+#             */
/*   Updated: 2025/01/02 15:20:33 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static void	free_stored_data(char **stored_data)
{
	if (*stored_data != NULL)
	{
		free(*stored_data);
		*stored_data = NULL;
	}
}

static char	*read_and_append(int fd, char *buffer, char *stored_data)
{
	int		read_bytes;
	char	*new_stored_data;

	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (stored_data == NULL)
			stored_data = ft_strdup("");
		if (stored_data == NULL)
			return (NULL);
		new_stored_data = ft_strjoin(stored_data, buffer);
		free_stored_data(&stored_data);
		if (new_stored_data == NULL)
			return (NULL);
		stored_data = new_stored_data;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stored_data);
}

static char	*extract_line(char *stored_data, int *next_line_start)
{
	int		i;
	char	*line;

	i = 0;
	if (stored_data == NULL || stored_data[0] == '\0')
		return (NULL);
	while (stored_data[i] != '\0' && stored_data[i] != '\n')
		i++;
	if (stored_data[i] == '\n')
		*next_line_start = i + 1;
	else
		*next_line_start = i;
	line = ft_substr(stored_data, 0, *next_line_start);
	return (line);
}

static char	*extract_remaining_data(char *stored_data, int next_line_start)
{
	char	*remaining_data;
	int		len;

	len = ft_strlen(stored_data) - next_line_start;
	if (len <= 0)
	{
		free(stored_data);
		return (NULL);
	}
	remaining_data = ft_substr(stored_data, next_line_start, len);
	if (remaining_data == NULL)
	{
		free(stored_data);
		return (NULL);
	}
	free(stored_data);
	return (remaining_data);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stored_data;
	int			next_line_start;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_stored_data(&stored_data);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	stored_data = read_and_append(fd, buffer, stored_data);
	free(buffer);
	if (stored_data == NULL)
		return (NULL);
	line = extract_line(stored_data, &next_line_start);
	if (line == NULL)
	{
		free_stored_data(&stored_data);
		return (NULL);
	}
	stored_data = extract_remaining_data(stored_data, next_line_start);
	return (line);
}
