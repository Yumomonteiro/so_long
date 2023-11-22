/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:14:23 by yude-oli          #+#    #+#             */
/*   Updated: 2023/11/22 16:04:54 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <X11/keysym.h>

#define INITIAL_BLOCK_SIZE 150
#define WIDTH 20
#define HEIGHT 10
#define NUM_IMAGES 1

typedef struct {
    char **map;
    int player_x;
    int player_y;
    int collectibles;
    int width;
    int height;
    void *mlx;
    void *win;
    void *player_img;
    void *obstaculo_img;
    void *coletavel_img;
    void *background_map;
    void *floor_img;
    void *gate_img;
    void *player_R_images[NUM_IMAGES];
    int current_image_index;
    int is_key_pressed;
} Game;


/* UTILS */
void clear_player_area(Game *game);
void draw_map(Game *game);
void initialize_player_images(Game *game);
int animate_player(Game *game);
int handle_key(int key, Game *game);
void calculate_window_size(Game *game);
void handle_movement(int new_x, int new_y, Game *game);
void clear_previous_position(Game *game, int x, int y);


/* END OF UTILS */

#endif 