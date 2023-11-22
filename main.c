#include"./mlx/mlx.h"
#include<stdio.h>
#define PI 3.141592


int x;
int y;

int main()
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1024, 528, "test");
	mlx_string_put(mlx, mlx_win, 50, 50, 0xfffff, "faruktinaz");

	mlx_loop(mlx);
}