SRCS = $(SRC_DIR)/parse/ft_parse.c \
		$(SRC_DIR)/parse/utilslibft.c \
		$(SRC_DIR)/parse/ft_parse_2.c \
		$(SRC_DIR)/parse/ft_parse_3.c \
		$(SRC_DIR)/parse/ft_parse_4.c \
		$(SRC_DIR)/parse/map_attr_add_data.c \
		$(SRC_DIR)/parse/utils.c \
		$(SRC_DIR)/main.c
NAME = cub3d
SRC_DIR = srcs
OBJ_DIR = srcs/obj
CC = gcc
RM = rm -rf
CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror
LFLAGS = -L./srcs/librarys/mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz -O2
OBJS =  $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT = $(SRC_DIR)/librarys/libft/libft.a
MLX = $(SRC_DIR)/librarys/mlx/libmlx.a
GNL = $(SRC_DIR)/librarys/get_next_line/get_next_line.c \
		$(SRC_DIR)/librarys/get_next_line/get_next_line_utils.c

all: $(NAME)

vg:		all
		valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d a

$(NAME): $(MLX) $(OBJ_DIR) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) $(MLX) -o $(NAME) $(LFLAGS)
	@echo "\033[5m\033[32mBuild successfull !\033[25m\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parse

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\033[33mGenerating Cub3D objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

$(LIBFT):
	@make -C ./srcs/librarys/libft
	@make bonus -C ./srcs/librarys/libft

$(MLX):
	@make -C ./srcs/librarys/mlx

clean:
	$(RM) $(OBJ_DIR)
	@make clean -C ./srcs/librarys/libft
	@make clean -C ./srcs/librarys/mlx	

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(MLX)
		
re:	fclean all

.PHONY: all re clean fclean