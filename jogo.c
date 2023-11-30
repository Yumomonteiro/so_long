#include "so_long.h"


// Função para desenhar o mapa
void draw_map(Game *game) 
{
    mlx_clear_window(game->mlx, game->win); // Limpa a janela

    int block_size = game->width / WIDTH;

    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            int x = i * block_size + 30;
            int y = j * block_size + 30;

            if (game->map[j][i] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->obstaculo_img, x, y);
                //mlx_pixel_put(game->mlx, game->win, x, y, 0xFFFFFF); // Parede
            } else if (game->map[j][i] == '0') {
                mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x, y);

                //mlx_pixel_put(game->mlx, game->win, x + 50, y + 50, 0x0000FF); // Espaço Livre
            } else if (game->map[j][i] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x, y);
            } else if (game->map[j][i] == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->coletavel_img, x, y);
                //mlx_pixel_put(game->mlx, game->win, x, y, 0xFFD700); // Coletável
            } else if (game->map[j][i] == 'E') {
                mlx_put_image_to_window(game->mlx, game->win, game->gate_img, x, y);
                //mlx_pixel_put(game->mlx, game->win, x, y, 0x8A2BE2); // Portal
            }
        }
    }
    if (game->moves_str != NULL) {
        mlx_string_put(game->mlx, game->win, game->moves_x_position, game->moves_y_position, 0xFFFFFF, game->moves_str);
    }
     mlx_do_sync(game->mlx);  // Forçar sincronização
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
    game->movies = 0;
    game->moves_str = NULL;
    game->moves_x_position = 10 * 70;
    game->moves_y_position = 10;
    game->moves_font_size = 10 * 10;
}
void update_moves_string(Game *game) {
    // Libere a string anterior se existir
    if (game->moves_str != NULL) {
        free(game->moves_str);
        game->moves_str = NULL;
    }

    // Aloque espaço para a nova string
    game->moves_str = (char *)malloc(50 * sizeof(char));  // Ajuste o tamanho conforme necessário

    // Construa a nova string de movimentos
    sprintf(game->moves_str, "MOVIMENTOS: %d", game->movies);
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
        //usleep(1000000);

        // reset se for a última imagem
        if (game->current_image_index == NUM_IMAGES - 1) {
            game->is_key_pressed = 0;
        }
    }

    return 1; // Retorna 1 para continuar chamando a função no loop
}


void check_collectibles(Game *game) {
    if (game->collectibles == 0) {
        int width, height;
        mlx_destroy_image(game->mlx, game->gate_img);  // Liberar a imagem anterior
        game->gate_img = mlx_xpm_file_to_image(game->mlx, "images/items/gate_open.xpm", &width, &height);
        // Atualizar a imagem do portão para a versão "aberta"
        // Certifique-se de ter a imagem correspondente ("gate_open.xpm") disponível no seu diretório de imagens.
        draw_map(game);  // Redesenha o mapa com a nova imagem do portão
    }
}

// Função para manipular teclas
int handle_key(int key, Game *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;
        if (key == XK_Escape) {
            exit(0);
        } 
        else if (key == XK_Up) 
        {
            new_y--;

        } else if (key == XK_Down) {
            new_y++;
        } else if (key == XK_Left) {
            new_x--;
        } else if (key == XK_Right) {
            new_x++;
        } else {
            game->is_key_pressed = 0;
            return 0;
        }
    // Verificar se a nova posição é válida (não é uma parede)
    if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT && game->map[new_y][new_x] != '1' && game->map[new_y][new_x] != 'E') 
    {
        game->movies++;
        // Limpar a posição anterior do jogador
        game->map[game->player_y][game->player_x] = '0';

        // Atualizar a posição do jogador
        game->player_x = new_x;
        game->player_y = new_y;

        // Verificar se o jogador coletou um item
        if (game->map[game->player_y][game->player_x] == 'C') {
            
            game->collectibles--;
            check_collectibles(game);
        }
        update_moves_string(game);
    

        // Definir a nova posição do jogador como 'P'
        game->map[new_y][new_x] = 'P';

        // Redesenha o mapa com a nova posição do jogador
        draw_map(game);
    }
    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) {
        printf("Parabéns! Você chegou ao portal!\n");
        exit(0);
    } else if (game->map[new_y][new_x] == 'E') {
        printf("Você não pode interagir com o portal até coletar todos os itens!\n");
        // Adicione qualquer lógica adicional que você queira executar quando o jogador tentar interagir sem coletar todos os itens.
    }
    //printf("MOVES: %d\n", game->movies);
    return 0;
}

void inicialize_map(Game *game, const char *line, int count)
{
        for (int i = 0; i < WIDTH; i++) {
            game->map[count][i] = line[i];
            if (game->map[count][i] == 'P') {
                    game->player_x = i;
                    game->player_y = count;
            } 
            else if (game->map[count][i] == 'C') {
                    game->collectibles++;
            }
        }
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
int validate_map(Game *game) {
    // Check if the map is surrounded by walls
    int collectibles = 0;
    int player = 0;
    int gate = 0;
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (game->map[j][i] == 'C') {
                collectibles++;
            } else if (game->map[j][i] == 'P') {
                player++;
            } else if (game->map[j][i] == 'E') {
                gate++;
            }
        }
    }
    if (player != 1 || gate != 1 || collectibles < 1) {
        return 0; // Invalid map
    }
    for (int i = 0; i < WIDTH; i++) {
        if (game->map[0][i] != '1' || game->map[HEIGHT - 1][i] != '1') {
            fprintf(stderr, "Error: Map must be surrounded by walls.\n");
            return 0; // Invalid map
        }
    }

    for (int j = 0; j < HEIGHT; j++) {
        if (game->map[j][0] != '1' || game->map[j][WIDTH - 1] != '1') {
            fprintf(stderr, "Error: Map must be surrounded by walls.\n");
            return 0; // Invalid map
        }
    }

    // Add other rules if needed...

    return 1; // Valid map
}

void flood_fill(char map[HEIGHT][WIDTH], int x, int y, int accessible[HEIGHT][WIDTH]) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || map[y][x] == '1' || accessible[y][x]) {
        return; // Base case: out of bounds or wall or already visited
    }    // Mark the current position as visited
    accessible[y][x] = 1;    // Recursive flood fill in all four directions
    flood_fill(map, x + 1, y, accessible);
    flood_fill(map, x - 1, y, accessible);
    flood_fill(map, x, y + 1, accessible);
    flood_fill(map, x, y - 1, accessible);
}
int all_collectibles_accessible(char map[HEIGHT][WIDTH]) {
    int accessible[HEIGHT][WIDTH] = {0}; // 0 means not accessible, 1 means accessible
    int player_x = -1, player_y = -1;

    // Find the player ('P') position
    int i = 0;
    while (i < HEIGHT && player_x == -1) {
        int j = 0;
        while (j < WIDTH && player_x == -1) {
            if (map[i][j] == 'P') {
                player_x = j;
                player_y = i;
            }
            j++;
        }
        i++;
    }

    // Perform flood fill starting from the player position
    flood_fill(map, player_x, player_y, accessible);

    // Check if any collectibles ('C') are not accessible
    i = 0;
    while (i < HEIGHT) {
        int j = 0;
        while (j < WIDTH) {
            if (map[i][j] == 'C' && !accessible[i][j]) {
                return 0; // Not all collectibles are accessible
            }
            j++;
        }
        i++;
    }

    return 1; // All collectibles are accessible
}

int main(void) {
    int fd = open("map5x10.ber", O_RDONLY);
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
    // Imagem portao aberto / fechado //
    game.gate_img = mlx_xpm_file_to_image(game.mlx, "images/items/gate_close.xpm", &width, &height);
    game.obstaculo_img = mlx_xpm_file_to_image(game.mlx, "images/items/obstaculo.xpm", &width, &height);
    game.coletavel_img = mlx_xpm_file_to_image(game.mlx, "images/items/coletavel00.xpm", &width, &height);
    game.player_img = mlx_xpm_file_to_image(game.mlx, "images/floor_player00.xpm", &width, &height);
    game.floor_img = mlx_xpm_file_to_image(game.mlx, "images/items/floor.xpm", &width, &height);

    game.collectibles = 0;
    
    fd = open("map5x10.ber", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    int count = 0;
    while ((line = get_next_line(fd)) != NULL && count < HEIGHT) {
        inicialize_map(&game, line, count);
        count++;
        free(line);
    }

    if (!validate_map(&game)) {
        fprintf(stderr, "Erro ao gerar mapa, algo está faltando...\n");
        return EXIT_FAILURE;
    }

    if (!all_collectibles_accessible(game.map)) {
        fprintf(stderr, "Erro ao gerar mapa, algo está faltando...\n");
        return EXIT_FAILURE;
    }

    printf("Coletáveis restantes: %d\n", game.collectibles);

    // Desenhar o mapa inicial
    draw_map(&game);

    // Inicializar as imagens do loop pra direita do player
    initialize_player_images(&game);

    // Registrar a função de tratamento de teclas
    mlx_hook(game.win, 2, 1L << 0, handle_key, &game);

    // Registrar a função de animação do jogador
    mlx_loop_hook(game.mlx, animate_player, &game);

    // Iniciar o loop de eventos
    mlx_loop(game.mlx);

    return 0;
}
