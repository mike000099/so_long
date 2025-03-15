/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:43:33 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/14 22:13:40 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	is_rectangular(char **map)
{
	int		i;
	size_t	width;
	int		rows;

	width = ft_strlen(map[0]);
	i = 1;
	rows = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			return (0);
		rows++;
		i++;
	}
	if (rows == (int)width)
		return (0);
	return (1);
}

static int	is_surrounded_by_walls(char **map)
{
	int	i;
	int	j;
	int	height;
	int	width;

	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

static int	has_invalid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C'
				&& map[i][j] != '0' && map[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	has_valid_components(char **map, int *collectible_count)
{
	int	invalid;

	invalid = has_invalid_characters(map);
	if (invalid)
		return (0);
	return (!count_player_exit_collectibles(map, collectible_count));
}

int	validate_map(char **map)
{
	int	total_collectibles;

	if (!is_rectangular(map))
		return (0);
	if (!is_surrounded_by_walls(map))
		return (0);
	if (!has_valid_components(map, &total_collectibles))
		return (0);
	return (1);
}
