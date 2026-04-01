
NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_DIR = minilibx-linux
LIBFT_DIR = libft
INCLUDE_DIR = include
INCLUDES = -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
MLX_LIBS = $(MLX_DIR)/libmlx.a -lX11 -lXext -lm
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/cub3d_utils1.c \
	$(SRC_DIR)/start_map.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/move_player.c \
	$(SRC_DIR)/checks.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/clean.c


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


.PHONY: all clean fclean re 


all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_LIB) $(MLX_LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/cub3d.h $(LIBFT_DIR)/libft.h | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
