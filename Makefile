NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC_DIR = src/
SRC = fdf.c create_map.c err_check.c key_press.c transform.c render.c utils.c
SRC_BONUS_DIR = src_bonus/
SRC_BONUS = fdf_bonus.c create_map_bonus.c err_check_bonus.c key_press_bonus.c \
			transform_bonus.c render_bonus.c utils_bonus.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRCS_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS))
OBJS = $(SRCS:.c=.o) $(GNL_SRC:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

ifdef BONUS
	OBJS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)
endif

all : $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft all

%.o: %.c
	$(CC) $(CFLAGS) -I mlx -I get_next_line -I libft -I $(SRC_DIR) -I $(SRC_BONUS_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I get_next_line -L mlx -l mlx -framework OpenGL -framework AppKit -o $(NAME)

clean : 
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

bonus :
	make BONUS=1 all

re : fclean all

.PHONY: all clean fclean re libft bonus
