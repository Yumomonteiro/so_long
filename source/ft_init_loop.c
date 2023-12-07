#include "../so_long.h"

void custom_delay(int microseconds) {
	volatile int i = 0;
	while (i < microseconds * 100) {
		i++;
	}
}

void start_animation(t_map *map)
{
	map->animation_on = 1;  // Set the animation flag to true
}

void stop_animation(t_map *map) {
	map->animation_on = 0;
}

int key_release(int keycode, t_map *map)
{
	if (keycode == RIGHT || keycode == LEFT || keycode == UP || keycode == DOWN) {
		stop_animation(map);
		map->player_moving = 0;
	}
	return (0);
}