/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player_and_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/20 12:56:38 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	read_player_and_collectibles(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->array[y][x] == 'P')
			{
				map->player.x = x;
				map->player.y = y;
			}
			else if (map->array[y][x] == 'C')
				map->collectibles_remaining++;
			x++;
		}
		y++;
	}
}

void	display_c_and_moves(t_map *map)
{
	ft_printf("Collectibles remaining: %d\n", map->collectibles_remaining);
	ft_printf("Moves: %d\n", map->moves);
}
