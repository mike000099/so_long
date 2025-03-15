/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:23:00 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/13 00:33:17 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char	**copy_map(char **map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_copy[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (!map_copy[i])
		{
			free_map(map_copy);
			return (NULL);
		}
		ft_strlcpy(map_copy[i], map[i], ft_strlen(map[i]) + 1);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	flood_fill(char **map, int x, int y, t_flood_fill_data *data)
{
	if (x < 0 || y < 0 || !map[y] || map[y][x] == '\0' || map[y][x] == '1')
		return ;
	if (map[y][x] == 'C')
		(*data->collectibles_found)++;
	else if (map[y][x] == 'E')
		(*data->exit_found)++;
	map[y][x] = '1';
	flood_fill(map, x + 1, y, data);
	flood_fill(map, x - 1, y, data);
	flood_fill(map, x, y + 1, data);
	flood_fill(map, x, y - 1, data);
}

int	is_position_surrounded_by_walls(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return (1);
	if ((y > 0 && map[y - 1][x] != '1') || (map[y + 1] && map[y + 1][x] != '1')
		|| (x > 0 && map[y][x - 1] != '1') || (map[y][x + 1] != '1'))
		return (0);
	return (1);
}

int	check_positions_surrounded(char **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((map[y][x] == 'P' || map[y][x] == 'E' || map[y][x] == 'C')
				&& is_position_surrounded_by_walls(map, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
