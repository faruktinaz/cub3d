all:
	gcc main.c -framework AppKit -framework OpenGL -L./mlx -lmlx -o 2dcub -g #-fsanitize=address -g