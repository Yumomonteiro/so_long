/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/20 12:56:29 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	open_door(t_map *map)
{
	int		width;
	int		height;

	if (map->collectibles_remaining == 0)
	{
		mlx_destroy_image(map->mlx, map->img.exit);
		map->img.exit = mlx_xpm_file_to_image(map->mlx, 
				"images/door-open.xpm", &width, &height);
		draw_map(map);
	}
}

void	move_player(t_map *map, int new_x, int new_y)
{
	map->array[map->player.y][map->player.x] = '0';
	map->array[new_y][new_x] = 'P';
	map->player.x = new_x;
	map->player.y = new_y;
	map->moves++;
}

void	exit_game(t_map *map, int new_x, int new_y)
{
	map->array[map->player.y][map->player.x] = '0';
	map->array[new_y][new_x] = 'P';
	map->player.x = new_x;
	map->player.y = new_y;
	ft_win(map);
	exit(0);
}

void	check_collectibles(t_map *map, int new_x, int new_y)
{
	map->collectibles_remaining--;
	map->array[new_y][new_x] = '0';
	open_door(map);
}
