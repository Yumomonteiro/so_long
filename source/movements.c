/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/20 12:56:35 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	move_player_and_check(t_map *map, int new_x, int new_y)
{
	if (map->array[new_y][new_x] == 'C')
		check_collectibles(map, new_x, new_y);
	if (map->array[new_y][new_x] == '0' || map->array[new_y][new_x] == 'C')
		move_player(map, new_x, new_y);
	if (map->collectibles_remaining == 0 && map->array[new_y][new_x] == 'E')
		exit_game(map, new_x, new_y);
	else if (map->collectibles_remaining != 0 && 
		map->array[new_y][new_x] == 'E')
		error_opendoor();
	return (0);
}

int	handle_player_movement(int keycode, t_map *map)
{
	int		new_x;
	int		new_y;

	new_x = map->player.x;
	new_y = map->player.y;
	if (keycode == UP)
		new_y--;
	else if (keycode == DOWN)
		new_y++;
	else if (keycode == LEFT)
	{
		new_x--;
		start_animation(map);
		map->player_moving = 2;
	}
	else if (keycode == RIGHT)
	{
		new_x++;
		start_animation(map);
		map->player_moving = 1;
	}
	else if (keycode == ESC)
		ft_close(map);
	return (move_player_and_check(map, new_x, new_y));
}

int	movement(int keycode, t_map *map)
{
	mlx_clear_window(map->mlx, map->wnd);
	if (handle_player_movement(keycode, map) == 1)
		return (1);
	draw_map(map);
	return (0);
}
