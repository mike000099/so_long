/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:04:56 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/15 00:06:30 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_player_position(t_data *data)
{
	if (!data->map || !data->map->layout)
	{
		return (0);
	}
	find_player_position(data->map->layout, &data->map->x, &data->map->y);
	if (data->map->x == -1 || data->map->y == -1)
	{
		ft_printf("Error: Player (P) not found in the map.\n");
		return (0);
	}
	return (1);
}

static int	validate_map_copy(t_data *data, char ***map_copy)
{
	*map_copy = copy_map(data->map->layout, data->map->height);
	if (!*map_copy)
		return (0);
	return (1);
}

static int	validate_flood_fill(t_data *data, char **map_copy)
{
	t_flood_fill_data	flood_data;
	int					collectibles_found;
	int					exit_found;

	collectibles_found = 0;
	exit_found = 0;
	flood_data.collectibles_found = &collectibles_found;
	flood_data.exit_found = &exit_found;
	if (check_positions_surrounded(map_copy, data->map->height,
			data->map->width))
	{
		ft_printf("Error: P, E, or C is surrounded by walls.\n");
		free_map(map_copy);
		return (0);
	}
	flood_fill(map_copy, data->map->x, data->map->y, &flood_data);
	if (exit_found == 0 || collectibles_found != data->map->collectibles_count)
	{
		ft_printf("Error: Invalid path.\n");
		free_map(map_copy);
		map_copy = NULL;
		return (0);
	}
	free_map(map_copy);
	return (1);
}

int	validate_path(t_data *data)
{
	char	**map_copy;

	if (!validate_player_position(data))
		return (0);
	if (!validate_map_copy(data, &map_copy))
		return (0);
	if (!validate_flood_fill(data, map_copy))
		return (0);
	return (1);
}
