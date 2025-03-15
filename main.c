/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:52:24 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/15 00:49:37 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	cleanup_data(t_data *data)
{
	if (data->map && data->map->layout)
	{
		free_map(data->map->layout);
		data->map->layout = NULL;
	}
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
		data->win = NULL;
	}
	if (data->map)
	{
		free(data->map);
		data->map = NULL;
	}
}

int	close_window(t_data *data)
{
	if (data)
	{
		cleanup_images(data);
		cleanup_data(data);
	}
	exit(0);
}

int	create_window(t_data *data)
{
	int	window_width;
	int	window_height;

	window_width = data->map->width * TILE_SIZE;
	window_height = data->map->height * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, window_width, window_height,
			"so_long");
	if (!data->win)
	{
		ft_printf("Error: Failed to create window.\n");
		return (1);
	}
	return (0);
}

int	setup_game(t_data *data)
{
	load_images(data);
	render_map(data);
	game_loop(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (argc != 2)
	{
		ft_printf("Usage: %s <map.ber>\n", argv[0]);
		return (1);
	}
	if (initialize_data(&data))
		return (1);
	if (read_and_validate_map(&data, argv[1]))
		return (1);
	if (!validate_path(&data))
	{
		cleanup_data(&data);
		return (1);
	}
	if (create_window(&data))
		return (1);
	data.move_counter = 0;
	setup_game(&data);
	cleanup_images(&data);
	cleanup_data(&data);
	return (0);
}
