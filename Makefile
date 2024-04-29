NAME = so_long
FLAGS = -Wall -Wextra -Werror -Ofast -g -fsanitize=address
HEADER = so_long.h
LIBMLX	= ./MLX42

LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS = \
map_start.c \
valid_map.c \
valid_path.c \
map_render.c \
so_long_main.c \
images.c \
game_logic.c \
free_error.c


OBJS = $(SRCS:.c=.o)
LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft.a
MLX42 = $(LIBMLX)/build/libmlx42.a


all: $(MLX42) $(NAME)
$(MLX42):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	cc $(OBJS) $(FLAGS) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	cc $(FLAGS) -I./MLX42/include/MLX42 -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

# test: all
# 	./$(NAME)


.PHONY: all clean fclean re test libmlx