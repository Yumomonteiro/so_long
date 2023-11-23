/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:14:23 by yude-oli          #+#    #+#             */
/*   Updated: 2023/11/23 19:28:06 by yude-oli         ###   ########.fr       */
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
#include <X11/X.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif


#define INITIAL_BLOCK_SIZE 150
#define WIDTH 10
#define HEIGHT 5
#define NUM_IMAGES 11


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
    void * player_current_image;
        //moves
    int movies;
    char *moves_str;
    int moves_x_position;  
    int moves_y_position;  
    int moves_font_size;
} Game;



/* UTILS */

char	*get_next_line(int fd);
char	*buffer_total_clear(int fd, char **buffer, char *line);
int	    line_updater(char **line, char buffer[]);
int	    ft_strlenm(char const *s1);
char	*ft_strjoinm(char const *s1, char const *s2);
void	buffer_clear(char *buffer);
// qfafaa
int validate_map(Game *game);
void inicialize_map(Game *game, const char *line, int count);
void custom_delay(int iterations);
void clear_player_area(Game *game);
void draw_map(Game *game);
void initialize_player_images(Game *game);
int animate_player(Game *game);
int handle_key(int key, Game *game);
void calculate_window_size(Game *game);
void handle_movement(int new_x, int new_y, Game *game);
void clear_previous_position(Game *game, int x, int y);
void draw_player(Game *player, void *mlx, void *win);


/* END OF UTILS */

#endif 