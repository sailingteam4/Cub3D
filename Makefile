NAME = cub3D

CLANG = clang
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = src/libft
LIBFT_LIB = $(LIBFT)/libft.a

MLX = src/mlx_linux
MLX_LIB = $(MLX)/libmlx.a

MLX_LFLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm

SRC_DIR = src/parsing
SRC =   $(addprefix $(SRC_DIR)/, cub3D.c parsing.c utils.c init_struct.c free.c is_valid.c check_map.c get_texture.c line.c get_player.c map_utils.c check_color_text.c mlx_make.c)

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC = -I$(LIBFT) -I$(MLX) -I includes

RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CLANG) $(CFLAGS) $(INC) $(OBJ) $(LIBFT_LIB) $(MLX_LFLAGS) -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT)

$(MLX_LIB):
	make -C $(MLX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CLANG) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT) clean
	# make -C $(MLX) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git src/mlx_linux
	make -C $(MLX)

re: fclean all

.PHONY: all clean fclean re mlx
