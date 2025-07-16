# ---------------------------------------------------------------- Project name
NAME        := cub3D

# ---------------------------------------------------------------- Compiler / tools
CC          := gcc
AR          := ar rcs

# ---------------------------------------------------------------- Directories
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := includes
LIBFT_DIR   := libft

# ---------------------------------------------------------------- Includes / flags
INCLUDES    := -I $(INC_DIR) -I $(LIBFT_DIR) -I ./assets/minilibx-linux
CFLAGS      := -Wall -Wextra -Werror -g $(INCLUDES)

# ---------------------------------------------------------------- Libraries
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_FLAGS   := -L ./minilibx-linux -L /usr/lib/X11 \
               -lmlx -lX11 -lXext -lXrender -lm

# ---------------------------------------------------------------- Source files (explicit list, no wildcard)
SRCS        := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/parse_utils.c \
	$(SRC_DIR)/texture.c \
	$(SRC_DIR)/raycast.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/cleanup.c

# ---------------------------------------------------------------- Object files
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ---------------------------------------------------------------- Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Compile .c → .o into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ---------------------------------------------------------------- Libft
$(LIBFT):
	$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# ---------------------------------------------------------------- House-keeping
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
