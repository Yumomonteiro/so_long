#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <X11/keysym.h>

// Tamanho inicial do bloco
#define INITIAL_BLOCK_SIZE 130
#define WIDTH 20
#define HEIGHT 10
#define NUM_IMAGES 9




// void draw_background(Game *game, char *image_path) {
//     int width, height;

//     // Carregar a imagem
//     game->background_map = mlx_xpm_file_to_image(game->mlx, image_path, &width, &height);
//     // Desenhar a imagem na janela
//     mlx_put_image_to_window(game->mlx, game->win, game->background_map, 0, 0);
// }

// Função para desenhar o mapa
void draw_map(Game *game) {
    mlx_clear_window(game->mlx, game->win); // Limpa a janela

    int block_size = game->width / WIDTH;

    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            int x = i * block_size + 30;
            int y = j * block_size + 30;

            if (game->map[j][i] == '1') {
                mlx_pixel_put(game->mlx, game->win, x, y, 0xFFFFFF); // Parede
            } else if (game->map[j][i] == '0') {
                mlx_pixel_put(game->mlx, game->win, x, y, 0x00FF00); // Espaço Livre
            } else if (game->map[j][i] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x, y);
            } else if (game->map[j][i] == 'C') {
                mlx_pixel_put(game->mlx, game->win, x, y, 0xFFD700); // Coletável
            } else if (game->map[j][i] == 'E') {
                mlx_pixel_put(game->mlx, game->win, x, y, 0x8A2BE2); // Portal
            }
        }
    }
}
void animate_and_move_right(Game *game) {
    if (!game->is_key_pressed) {
        game->is_key_pressed = 1;

        // Limpar a posição anterior do jogador
        game->map[game->player_y][game->player_x] = '0';

        int initial_x = game->player_x * (game->width / WIDTH) + 30;
        int initial_y = game->player_y * (game->width / WIDTH) + 30;

        // Atualizar a posição do jogador
        int target_x = game->player_x + 1;
        int final_x = target_x * (game->width / WIDTH) + 30;
        int final_y = game->player_y * (game->width / WIDTH) + 30;

        float progress = 0;
        float step = 0.18;

        // Realizar a animação enquanto o jogador se move para a direita
        while (progress <= 1.0) {
            int intermediate_x = (1 - progress) * initial_x + progress * final_x;
            int intermediate_y = (1 - progress) * initial_y + progress * final_y;

            // Limpar a janela antes de desenhar a nova posição do jogador
            mlx_clear_window(game->mlx, game->win);

            // Atualizar a imagem do jogador com a próxima imagem no loop
            mlx_put_image_to_window(game->mlx, game->win, game->player_R_images[game->current_image_index], intermediate_x, intermediate_y);

            mlx_do_sync(game->mlx);  // Forçar sincronização

            progress += step;
            usleep(30000);  // Adicionar um pequeno atraso para controlar a velocidade da transição
            animate_player(game);  // Chamar a função para animar o jogador durante o movimento
        }

        // Definir a nova posição do jogador como 'P'
        game->map[game->player_y][target_x] = 'P';

        // Atualizar a posição do jogador
        game->player_x = target_x;

        // Redesenha o mapa com a nova posição do jogador
        draw_map(game);

        // Realizar a animação
        game->is_key_pressed = 0;
    }
}
// Função para inicializar as imagens do jogador
void initialize_player_images(Game *game) {
    char image_path[50];
    int width, height;

    for (int i = 0; i < NUM_IMAGES; i++) {
        snprintf(image_path, sizeof(image_path), "images/loop_walking_right/viking%d.xpm", i);
        game->player_R_images[i] = mlx_xpm_file_to_image(game->mlx, image_path, &width, &height);
    }
    game->current_image_index = 0;
    game->is_key_pressed = 0;
}

// Função para animar o jogador
// Função para animar o jogador
int animate_player(Game *game) {
    if (game->is_key_pressed) {
        // Atualizar o índice da imagem do jogador para criar um loop
        game->current_image_index = (game->current_image_index + 1) % NUM_IMAGES;

        // Limpar a janela
        mlx_clear_window(game->mlx, game->win);

        // Atualizar a imagem do jogador com a próxima imagem no loop
        int x = game->player_x * (game->width / WIDTH) + 30;
        int y = game->player_y * (game->width / WIDTH) + 30;

        // Atualizar a imagem do jogador com a próxima imagem no loop
        mlx_put_image_to_window(game->mlx, game->win, game->player_R_images[game->current_image_index], x, y);

        // Adicionar um pequeno atraso entre cada imagem
        usleep(25000);

        // reset se for a última imagem
        if (game->current_image_index == NUM_IMAGES - 1) {
            game->is_key_pressed = 0;
        }
    }

    return 1; // Retorna 1 para continuar chamando a função no loop
}




// Função para manipular teclas
int handle_key(int key, Game *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (key == XK_Escape) {
        exit(0);
    } else if (key == XK_Up) {
        new_y--;
    } else if (key == XK_Down) {
        new_y++;
    } else if (key == XK_Left) {
        new_x--;
    } else if (key == XK_Right) {
        
        animate_and_move_right(game);
        new_x++;
    }else {
        game->is_key_pressed = 0;
        return 0;
    }

    // Verificar se a nova posição é válida (não é uma parede)
    if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT && game->map[new_y][new_x] != '1') {
        // Limpar a posição anterior do jogador
        game->map[game->player_y][game->player_x] = '0';

        // Atualizar a posição do jogador
        game->player_x = new_x;
        game->player_y = new_y;

        // Verificar se o jogador coletou um item
        if (game->map[new_y][new_x] == 'C') {
            game->collectibles--;
            if (game->collectibles == 0) {
                // Se todos os itens foram coletados, substituir 'E' por '0'
                for (int j = 0; j < HEIGHT; j++) {
                    for (int i = 0; i < WIDTH; i++) {
                        if (game->map[j][i] == 'E') {
                            game->map[j][i] = '0';
                        }
                    }
                }
            }
        }

        // Definir a nova posição do jogador como 'P'
        game->map[new_y][new_x] = 'P';

        // Redesenha o mapa com a nova posição do jogador
        draw_map(game);
    }

    // Verificar se o jogador chegou ao portal
    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) {
        printf("Parabéns! Você chegou ao portal!\n");
        exit(0);
    }

    return 0;
}


// Função para calcular as dimensões da janela com base no tamanho do mapa
void calculate_window_size(Game *game) {
    int block_size = game->width / WIDTH;
    int window_width = block_size * WIDTH;
    int window_height = block_size * HEIGHT;

    mlx_clear_window(game->mlx, game->win);
    mlx_destroy_window(game->mlx, game->win);

    game->win = mlx_new_window(game->mlx, window_width, window_height, "Collectibles Game");
}
int main(void) {
    int fd = open("map.ber", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Game game;
    game.mlx = mlx_init();
    game.width = WIDTH * INITIAL_BLOCK_SIZE;
    game.height = HEIGHT * INITIAL_BLOCK_SIZE;
    game.win = mlx_new_window(game.mlx, game.width, game.height, "Collectibles Game");

    int width, height;
    game.player_img = mlx_xpm_file_to_image(game.mlx, "images/viking000.xpm", &width, &height);

    // Alocar dinamicamente o mapa
    game.map = (char **)malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        game.map[i] = (char *)malloc(WIDTH * sizeof(char));
    }

    // Inicializar o mapa
    for (int j = 0; j < HEIGHT; j++) {
        char buffer[WIDTH + 1];
        read(fd, buffer, WIDTH + 1);
        for (int i = 0; i < WIDTH; i++) {
            game.map[j][i] = buffer[i];
            if (buffer[i] == 'P') {
                if (j >= 0 && j < HEIGHT && i >= 0 && i < WIDTH) {
                    game.player_x = i;
                    game.player_y = j;
                } else {
                    fprintf(stderr, "Erro: Coordenadas iniciais do jogador fora dos limites do mapa.\n");
                    exit(EXIT_FAILURE);
                }
            } else if (buffer[i] == 'C') {
                game.collectibles++;
            }
        }
    }

    close(fd);

    // Desenhar o mapa inicial
    draw_map(&game);

    // Desenhar a imagem background
    //draw_background(&game, "images/backgroundwindown.xpm");

    // Inicializar as imagens do loop pra direita do player
    initialize_player_images(&game);
    mlx_loop_hook(game.mlx, (int (*)(void *))animate_player, &game);

    // Registrar a função de tratamento de teclas
    mlx_key_hook(game.win, handle_key, &game);

    // Registrar a função de animação do jogador
    mlx_loop_hook(game.mlx, animate_player, &game);

    // Iniciar o loop de eventos
    mlx_loop(game.mlx);

    return 0;
}