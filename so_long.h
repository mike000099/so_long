/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseddouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:41 by yseddouk          #+#    #+#             */
/*   Updated: 2025/03/13 21:28:09 by yseddouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./ft_printf/ft_printf.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64
# define WINDOW_WIDTH 2048
# define WINDOW_HEIGHT 2048

# define MAX_LINES 1000
# define ESC 65307

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_map
{
	char	**layout;
	void	*object;
	int		width;
	int		height;
	int		collectibles_count;
	int		x;
	int		y;
	int		diamonds;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	int		player_x;
	int		player_y;
	int		move_counter;
	int		collected;
	t_map	*map;
	void	*img_wall;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
	void	*img_floor;

}			t_data;

typedef struct s_flood_fill_data
{
	int		*collectibles_found;
	int		*exit_found;
}			t_flood_fill_data;

void		exit_with_error(char *message);
void		free_map(char **map);
char		**read_map(char *file, t_data *data);
int			validate_map(char **map);
void		print_map(char **map);
void		trim_newline(char *str);
void		game_loop(t_data *data);
int			check_win_condition(char **map);
int			has_valid_components(char **map, int *collectible_count);
void		render_map(t_data *data);
void		load_images(t_data *data);
int			handle_keypress(int keycode, t_data *data, int total_collectibles);
int			close_window(t_data *data);
void		move_player(t_data *data, char direction);
void		find_player_position(char **map, int *x, int *y);
int			count_collectibles(char **map);
int			read_and_validate_map(t_data *data, char *map_file);
int			initialize_data(t_data *data);
int			count_player_exit_collectibles(char **map, int *collectible_count);
void		print_move_counter(t_data *data);
int			validate_path(t_data *data);
int			check_positions_surrounded(char **map, int height, int width);
int			is_position_surrounded_by_walls(char **map, int x, int y);
void		flood_fill(char **map, int x, int y, t_flood_fill_data *data);
char		**copy_map(char **map, int height);
void		cleanup_images(t_data *data);
void		cleanup_data(t_data *data);
int			handle_destroy(t_data *data);
#endif
