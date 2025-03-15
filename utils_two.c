/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:41:09 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/15 00:51:47 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	read_and_validate_map(t_data *data, char *map_file)
{
	data->map->layout = read_map(map_file, data);
	if (!data->map->layout)
	{
		cleanup_data(data);
		return (0);
	}
	data->map->height = 0;
	while (data->map->layout[data->map->height])
		data->map->height++;
	data->map->width = ft_strlen(data->map->layout[0]);
	if (!validate_map(data->map->layout))
	{
		ft_printf("Error: invalid map.\n");
		cleanup_data(data);
		return (0);
	}
	data->collected = 0;
	data->map->collectibles_count = count_collectibles(data->map->layout);
	return (0);
}

int	count_player_exit_collectibles(char **map, int *collectible_count)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	*collectible_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				player_count++;
			else if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'C')
				(*collectible_count)++;
			j++;
		}
		i++;
	}
	return (player_count != 1 || exit_count != 1 || *collectible_count < 1);
}

int	initialize_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_printf("Error: Failed to initialize MiniLibX.\n");
		return (1);
	}
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		ft_printf("Error: failed to allocate memory for map.\n");
		return (1);
	}
	return (0);
}

void	find_player_position(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	*x = -1;
	*y = -1;
}

int	handle_keypress(int keycode, t_data *data, int total_collectibles)
{
	(void)total_collectibles;
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(data, 'W');
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(data, 'S');
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(data, 'A');
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(data, 'D');
	else if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}
