# ──────────────────────────────────────────────────────────────────────────────
# PROJECT DIRECTORIES
# ──────────────────────────────────────────────────────────────────────────────

SRC_DIR                 := src
LIBFT_DIR               := lib/libft
MLX_DIR                 := assets/minilibx-linux
SUPPRESS_X11			:= lib/x11.supp
# ──────────────────────────────────────────────────────────────────────────────
# PROJECT SETTINGS
# ──────────────────────────────────────────────────────────────────────────────

NAME                    := cub3D
CC                      := gcc
AR                      := @ar rcs
RM                      := @rm -rf
CFLAGS                  := -g -O0 -I lib -I $(LIBFT_DIR) -I $(MLX_DIR)
OBJDIR                  := objs

# ──────────────────────────────────────────────────────────────────────────────
# LIBRARIES (libft, MiniLibX)
# ──────────────────────────────────────────────────────────────────────────────

LIBFT                   := $(LIBFT_DIR)/libft.a

MLX_FLAGS               := -L $(MLX_DIR) -lmlx -lX11 -lXext -lXrender -lm

# ──────────────────────────────────────────────────────────────────────────────
# DIRECTORY LAYOUT  (group sources into logical buckets)
# ──────────────────────────────────────────────────────────────────────────────

DIR						:= $(SRC_DIR)

# ──────────────────────────────────────────────────────────────────────────────
# SOURCE FILES   (just filenames; they get prefixed later)
# ──────────────────────────────────────────────────────────────────────────────

TOP_SRCS                := main.c movements.c utils.c

PARSING_SRCS            := map_validator.c parser.c parser_utils.c parser_helpers.c parser_helpers2.c parse_sprite.c

RENDERING_SRCS          := raycast_dda.c raycast_draw.c render.c events.c cleanup.c minimap.c sprites.c door.c

# ──────────────────────────────────────────────────────────────────────────────
# PREFIX each group with its directory
# ──────────────────────────────────────────────────────────────────────────────

TOP                     := $(addprefix $(DIR)/,$(TOP_SRCS))
PARSING                 := $(addprefix $(DIR)/,$(PARSING_SRCS))
RENDERING               := $(addprefix $(DIR)/,$(RENDERING_SRCS))

# ──────────────────────────────────────────────────────────────────────────────
# ALL SOURCE FILES & OBJECTS
# ──────────────────────────────────────────────────────────────────────────────

SRCS                    := $(TOP) $(PARSING) $(RENDERING)
OBJS                    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

# ──────────────────────────────────────────────────────────────────────────────
# DEFAULT TARGET
# ──────────────────────────────────────────────────────────────────────────────

all:                    $(NAME)

# ──────────────────────────────────────────────────────────────────────────────
# LINKING
# ──────────────────────────────────────────────────────────────────────────────

$(NAME):                $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

# ──────────────────────────────────────────────────────────────────────────────
# build libft automatically if missing
# ──────────────────────────────────────────────────────────────────────────────

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# ──────────────────────────────────────────────────────────────────────────────
# PATTERN RULE  (.c → .o)
# ──────────────────────────────────────────────────────────────────────────────

$(OBJDIR)/%.o:          %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ──────────────────────────────────────────────────────────────────────────────
# CLEAN TARGETS
# ──────────────────────────────────────────────────────────────────────────────

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:                 clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:                     fclean all

# ──────────────────────────────────────────────────────────────────────────────
# OPTIONAL VALGRIND / NORM TARGETS
# ──────────────────────────────────────────────────────────────────────────────

leaks:
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESS_X11) ./$(NAME) assets/maps/bad/color_none.cub
# 	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESS_X11) ./$(NAME) assets/maps/good/cheese_maze.cub
	
qleaks:
	@valgrind --leak-check=full -q --suppressions=$(SUPPRESS_X11) ./$(NAME) assets/maps/good/cheese_maze.cub

norm:
	@norminette | grep Error || true
