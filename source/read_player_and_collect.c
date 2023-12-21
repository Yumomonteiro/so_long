/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player_and_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/21 16:18:58 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	read_player_and_collectibles(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (map->array[y])
	{
		x = 0;
		while (map->array[y][x])
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
                if(x != map->x)
                        error_map(map);
		y++;
	}
        if(y != map->y)
                error_map(map);
}

void	display_c_and_moves(t_map *map)
{
	ft_printf("Collectibles remaining: %d\n", map->collectibles_remaining);
	ft_printf("Moves: %d\n", map->moves);
}
