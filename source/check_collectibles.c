/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collectibles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/21 14:55:31 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	flood_fill(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height
		|| map->array[y][x] == '1' || map->accessible[y][x])
		return ;
	map->accessible[y][x] = 1;
        if (map->array[y][x] == 'E')
                return;
	flood_fill(x + 1, y, map);
	flood_fill(x - 1, y, map);
	flood_fill(x, y + 1, map);
	flood_fill(x, y - 1, map);
}

int	collectibles_not_accessible(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < map->height)
	{
		j = 0;
		while (++j < map->width)
		{
			if (map->array[i][j] == 'C' && !map->accessible[i][j])
				return (1);
		}
	}
	return (0);
}
int	gate_not_accessible(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < map->height)
	{
		j = 0;
		while (++j < map->width)
		{
			if (map->array[i][j] == 'E' && !map->accessible[i][j])
				return (1);
		}
	}
	return (0);
}

void	initialize_accessible_array(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < map->height)
	{
		map->accessible[i] = malloc(map->width * sizeof(int));
		j = 0;
		while (++j < map->width)
			map->accessible[i][j] = 0;
	}
}

int	all_c_accessible(char **array, int height, int width, t_player player)
{
	t_map	map;
	int		i;
	int		k;

	map.array = array;
	map.height = height;
	map.width = width;
	map.accessible = malloc(height * sizeof(int *));
	if (!map.accessible)
		return (0);
	initialize_accessible_array(&map);
	flood_fill(player.x, player.y, &map);
	if (collectibles_not_accessible(&map) || gate_not_accessible(&map))
	{
		k = 0;
		while (++k < map.height)
			free(map.accessible[k]);
		free(map.accessible);
		return (0);
	}
	i = 0;
	while (++i < height)
		free(map.accessible[i]);
	free(map.accessible);
	return (1);
}
