NAME = cub3D
NAME_BONUS = cub3D_bonus

CLANG = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3

LIBFT = src/libft
LIBFT_LIB = $(LIBFT)/libft.a

MLX = src/mlx_linux
MLX_LIB = $(MLX)/libmlx.a

MLX_LFLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm

SRC_DIRS = src/Cub3D/parsing src/Cub3D/window src/Cub3D/raycasting
SRC_PARSING = $(addprefix src/Cub3D/parsing/, cub3D.c parsing.c utils.c init_struct.c free.c is_valid.c check_map.c get_texture.c line.c get_player.c map_utils.c check_color_text.c)
SRC_WINDOW = $(addprefix src/Cub3D/window/, mlx_make.c keybinds.c mlx_utils.c draw_screen.c handle_collision.c handle_movement.c)
SRC_RAYCASTING = $(addprefix src/Cub3D/raycasting/, draw_utils.c draw_3d.c rc_utils.c)
SRC = $(SRC_PARSING) $(SRC_WINDOW) $(SRC_RAYCASTING)

SRC_BONUS_WINDOW = $(addprefix src/Cub3D/window/, mlx_make.c keybinds_bonus.c mlx_utils.c draw_screen_bonus.c handle_collision.c handle_movement.c draw_player_bonus.c)
SRC_BONUS = $(SRC_PARSING) $(SRC_BONUS_WINDOW) $(SRC_RAYCASTING)

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:src/%.c=$(OBJ_DIR)/%.o)

INC = -I$(LIBFT) -I$(MLX) -I includes

RM = rm -f

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CLANG) $(CFLAGS) $(INC) $(OBJ) $(LIBFT_LIB) $(MLX_LFLAGS) -o $(NAME)

$(NAME_BONUS): $(LIBFT_LIB) $(MLX_LIB) $(OBJ_BONUS)
	$(CLANG) $(CFLAGS) $(INC) $(OBJ_BONUS) $(LIBFT_LIB) $(MLX_LFLAGS) -o $(NAME_BONUS)

$(LIBFT_LIB):
	make -C $(LIBFT)

$(MLX_LIB):
	make -C $(MLX)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CLANG) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	make -C $(LIBFT) clean
	# make -C $(MLX) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT) fclean

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git src/mlx_linux
	make -C $(MLX)

norm:
	norminette $(SRC_DIRS)

re: fclean all

.PHONY: all clean fclean re mlx norm