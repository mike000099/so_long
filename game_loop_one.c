/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:52:48 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/13 22:01:30 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	is_within_bounds(t_data *data, int new_x, int new_y)
{
	return (new_x >= 0 && new_x < data->map->width && new_y >= 0
		&& new_y < data->map->height);
}

static void	handle_collectibles(t_data *data, int new_x, int new_y)
{
	if (data->map->layout[new_y][new_x] == 'C')
	{
		data->collected++;
		data->map->layout[new_y][new_x] = '0';
	}
}

static void	update_player_position(t_data *data, int new_x, int new_y)
{
	data->map->layout[data->player_y][data->player_x] = '0';
	data->player_x = new_x;
	data->player_y = new_y;
	data->map->layout[data->player_y][data->player_x] = 'P';
}

static void	handle_exit(t_data *data, int new_x, int new_y)
{
	if (data->map->layout[new_y][new_x] == 'E')
	{
		if (data->collected == data->map->collectibles_count)
		{
			close_window(data);
			exit(0);
		}
		else
			return ;
	}
	else
		return ;
}

void	move_player(t_data *data, char direction)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (direction == 'W')
		new_y--;
	else if (direction == 'S')
		new_y++;
	else if (direction == 'A')
		new_x--;
	else if (direction == 'D')
		new_x++;
	if (!is_within_bounds(data, new_x, new_y)
		|| data->map->layout[new_y][new_x] == '1')
		return ;
	if (data->map->layout[new_y][new_x] == 'E'
		&& data->collected != data->map->collectibles_count)
		return ;
	handle_collectibles(data, new_x, new_y);
	handle_exit(data, new_x, new_y);
	update_player_position(data, new_x, new_y);
	data->move_counter++;
	print_move_counter(data);
	render_map(data);
}
