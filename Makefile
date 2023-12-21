NAME 	= so_long.a

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror -g #-fsanitize=address

SRCS 	= ./source/check_collectibles.c ./source/end_screen.c ./source/check_border.c ./source/generate_map_array.c ./source/map_printer.c ./source/movements.c ./source/movements_utils.c ./source/get_next_line.c ./source/get_next_line_utils.c ./source/errors.c ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strjoinfree.c ./utils/ft_strstr.c ./utils/ft_strnstr.c ./utils/ft_putchar_lenght.c ./utils/ft_strncmp.c ./utils/ft_memcpy.c ./source/map_initializer.c ./source/read_player_and_collect.c ./utils/ft_printf.c ./utils/ft_numbers.c ./utils/ft_words.c

OBJS    = $(SRCS:.c=.o)
PROGRAM = so_long

all: $(NAME) program

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

program: $(NAME)
	$(CC) $(CFLAGS) -o $(PROGRAM) main.c $(NAME) .minilibx-linux/libmlx.a -lXext -lX11

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(PROGRAM)

re: fclean all

.PHONY: all clean fclean re program

.SILENT:
