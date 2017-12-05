CC=gcc
CFLAGS=-Wall -Wextra -Werror
ZADANIE=main fdf_handler fdf_read fdf_operations fdf_draw fdf_rotations fdf_lines fdf_center
OBJ=$(addprefix obj/, $(addsuffix .o, $(ZADANIE)))
NAME=fdf

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lm -lmlx -framework OpenGL -framework AppKit libft/libft.a
libft/libft.a:
	make -C libft/
obj/%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	rm -f $(OBJ)
	make -C libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
re: fclean all
	
