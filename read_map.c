/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:12:11 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/14 21:30:40 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	count_lines(int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	**fill_map(int fd, int lines)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
		{
			free(map);
			return (NULL);
		}
		trim_newline(map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**read_map(char *file, t_data *data)
{
	int		fd;
	int		lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: couldn't open map\n");
	lines = count_lines(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: couldn't open map\n");
	map = fill_map(fd, lines);
	close(fd);
	if (!map)
		exit_with_error("Error: failed to read map\n");
	find_player_position(map, &data->player_x, &data->player_y);
	if (data->player_x == -1 || data->player_y == -1)
		exit_with_error("Error: Player starting position not  found in map!\n");
	return (map);
}
