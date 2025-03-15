/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:21:45 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/13 21:45:27 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	cleanup_images(t_data *data)
{
	if (data->img_floor)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_player)
		mlx_destroy_image(data->mlx, data->img_player);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	data->img_floor = NULL;
	data->img_wall = NULL;
	data->img_player = NULL;
	data->img_collectible = NULL;
	data->img_exit = NULL;
}

void	load_images(t_data *data)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	data->img_floor = mlx_xpm_file_to_image(data->mlx, "images/floor.xpm",
			&img_width, &img_height);
	if (!data->img_floor)
		exit_with_error("Error: Failed to load floor image.\n");
	data->img_wall = mlx_xpm_file_to_image(data->mlx, "images/wall.xpm",
			&img_width, &img_height);
	if (!data->img_wall)
		exit_with_error("Error: Failed to load wall image.\n");
	data->img_player = mlx_xpm_file_to_image(data->mlx, "images/player.xpm",
			&img_width, &img_height);
	if (!data->img_player)
		exit_with_error("Error: Failed to load player image.\n");
	data->img_collectible = mlx_xpm_file_to_image(data->mlx, "images/ball.xpm",
			&img_width, &img_height);
	if (!data->img_collectible)
		exit_with_error("Error: Failed to load collectible image.\n");
	data->img_exit = mlx_xpm_file_to_image(data->mlx, "images/door.xpm",
			&img_width, &img_height);
	if (!data->img_exit)
		exit_with_error("Error: Failed to load exit image.\n");
}

void	render_tile(t_data *data, int x, int y)
{
	void	*img;

	mlx_put_image_to_window(data->mlx, data->win, data->img_floor, x
		* TILE_SIZE, y * TILE_SIZE);
	img = NULL;
	if (data->map->layout[y][x] == '1')
		img = data->img_wall;
	else if (data->map->layout[y][x] == 'P')
		img = data->img_player;
	else if (data->map->layout[y][x] == 'C')
		img = data->img_collectible;
	else if (data->map->layout[y][x] == 'E')
		img = data->img_exit;
	if (img)
		mlx_put_image_to_window(data->mlx, data->win, img, x * TILE_SIZE, y
			* TILE_SIZE);
}

void	render_map(t_data *data)
{
	int	y;
	int	x;

	if (!data->map || !data->map->layout)
		exit_with_error("Error: Map not loaded or invalid.\n");
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			render_tile(data, x, y);
			x++;
		}
		y++;
	}
}
