/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/20 12:56:24 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	draw_player(t_map *map, int x, int y)
{
	if (map->player_moving == 1)
		mlx_put_image_to_window(map->mlx, map->wnd, 
			map->player_frames[map->current_frame], x, y);
	else if (map->player_moving == 2)
		mlx_put_image_to_window(map->mlx, map->wnd,
			map->img.player_left1, x, y);
	else
		mlx_put_image_to_window(map->mlx, map->wnd, 
			map->player_frames[1], x, y);
}

void	draw_wall(t_map *map, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->wnd, 
		map->img.wall, x, y);
}

void	draw_collectible(t_map *map, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->wnd, 
		map->img.collectible, x, y);
}

void	draw_exit(t_map *map, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->wnd, 
		map->img.exit, x, y);
}

void	draw_map(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->array[y][x] == '1')
				draw_wall(map, x * IMG_PXL, y * IMG_PXL);
			else if (map->array[y][x] == 'P')
				draw_player(map, x * IMG_PXL, y * IMG_PXL);
			else if (map->array[y][x] == 'C')
				draw_collectible(map, x * IMG_PXL, y * IMG_PXL);
			else if (map->array[y][x] == 'E')
				draw_exit(map, x * IMG_PXL, y * IMG_PXL);
			else if (map->array[y][x] == '0')
				mlx_put_image_to_window(map->mlx, map->wnd, 
					map->img.empty, x * IMG_PXL, y * IMG_PXL);
			x++;
		}
		y++;
	}
	display_c_and_moves(map);
}
