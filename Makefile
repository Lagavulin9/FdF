NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(LIBFT) -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

LIB_DIR = lib/
LIBFT_DIR = $(LIB_DIR)libft/
GNL_DIR = $(LIB_DIR)get_next_line/
MLX_DIR = $(LIB_DIR)minilibx_opengl/
SRC_DIR = src/
SRC_BONUS_DIR = src_bonus/

LIBFT_NAME = libft.a
MLX_NAME = libmlx.a

LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)
MLX = $(MLX_DIR)$(MLX_NAME)

SRC = fdf.c \
	create_map.c \
	err_check.c \
	key_press.c \
	transform.c \
	render.c utils.c
SRC_BONUS = fdf_bonus.c \
			create_map_bonus.c \
			err_check_bonus.c \
			key_press_bonus.c \
			transform_bonus.c \
			render_bonus.c \
			utils_bonus.c
GNL_SRC = get_next_line.c \
		get_next_line_utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(GNL_DIR), $(GNL_SRC))
OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o)) $(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o))
OBJ_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS:.c=.o)) $(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o))

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

ifdef BONUS
	SRCS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS)) $(addprefix $(GNL_DIR), $(GNL_SRC))
	OBJS = $(OBJ_BONUS)
endif

all : $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus -j6

$(MLX):
	@$(MAKE) -C $(MLX_DIR) all -j6

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIB_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

bonus :
	make BONUS=1 all

re : fclean all

.PHONY: all clean fclean re libft bonus
