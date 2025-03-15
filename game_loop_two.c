/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:44:16 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/13 21:27:36 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	check_win_condition(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	print_move_counter(t_data *data)
{
	ft_printf("Number of move_counter: %d\n", data->move_counter);
}

int	handle_destroy(t_data *data)
{
	close_window(data);
	return (0);
}

void	game_loop(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 17, 0, handle_destroy, data);
	mlx_loop(data->mlx);
}
