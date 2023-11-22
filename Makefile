all:
	gcc test.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz -o 2dcub