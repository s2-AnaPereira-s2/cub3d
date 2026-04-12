
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
	$(SRC_DIR)/startup_parsing.c \
	$(SRC_DIR)/map_parsing_utils.c \
	$(SRC_DIR)/map_parsing_utils2.c \
	$(SRC_DIR)/texture_parsing.c \
	$(SRC_DIR)/start_map.c \
	$(SRC_DIR)/parsing_map.c \
	$(SRC_DIR)/parsing_texture_color.c \
	$(SRC_DIR)/path_checks.c \
	$(SRC_DIR)/move_player.c \
	$(SRC_DIR)/map_checks.c \
	$(SRC_DIR)/format_checks.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/draw_wall.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/minimap.c \
	$(SRC_DIR)/key_hooks.c \
	$(SRC_DIR)/clean.c


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


.PHONY: clean fclean re


all: $(NAME)

$(LIBFT_LIB):
	@$(MAKE) --no-print-directory -s -C $(LIBFT_DIR)
	@echo "built: libft"

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "compiled: object files"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_LIB) $(MLX_LIBS) -o $(NAME)
	@echo "built: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/cub3d.h $(LIBFT_DIR)/libft.h | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "created: $(OBJ_DIR)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -s clean -C $(LIBFT_DIR)
	@echo "cleaned: object files"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -s fclean -C $(LIBFT_DIR)
	@echo "cleaned: $(NAME)"

re: fclean all
	@echo "rebuilt: $(NAME)"
