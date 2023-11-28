#include<stdlib.h>
#include <stdio.h>
#include "./mlx/mlx.h"
#include <math.h>
#define DR 0.0174532925
#define PI  3.1415926535
#define P2  PI/2
#define P3  3*PI/2
#define S 115
#define W 119
#define A 97
#define D 100

float px,py,pdx,pdy,pa; // player position

int i_color = 0;

int mapX=8, mapY=8, mapS=64;
int map[]=
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};


typedef struct s_data
{
	void *mlx;
	void *mlx_win;
	void *img;
	void *wall_img;
	float pl_a;
	void *floor_img;
	float p_x; // player x;
	float p_y; // player y;

}		t_data;

void draw2Dmap(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y*mapX+x] == 1)
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall_img, (x*64), (y*64)); // warn
			else if (map[y*mapX+x] == 0)
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->floor_img, (x*64), (y*64)); // warn
			x++;
		}
		y++;
	}
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 
  
void DDA(int X0, int Y0, int X1, int Y1, t_data *data)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
		if (map[(((int)(Y+20) / 64) * mapY) + (int)((X+20) / 64)] != 1)
        	mlx_pixel_put(data->mlx, data->mlx_win, X + 20, Y + 20, 0xFF0000);
		else
		{
			printf("\n\n\n *** x-> %f y-> %f\n", X, Y);
			// EUYVAH
			// printf("x in karesi + y nin karesinin karekoku -> %d \n",(int)sqrt(pow(data->p_x, 2) + pow((int)Y, 2)));
			break;
		}
		printf("X -> %f Y -> %d\n", X+20, ((int)((Y+20) / 64 + mapY)));
		printf("X / 64 -> %d Y -> %f\n", (int)(X+20) / 64, (Y+20) / 64);
        X += Xinc;
        Y += Yinc;
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}


int	key_event(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->p_y += pdy;
		data->p_x += pdx;
	}
	else if (keycode == S)
	{
		data->p_y -= pdy;
		data->p_x -= pdx;	
	}
	else if (keycode == A)
	{
		pa-= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a -= pa * 5 ;
	}
	else if (keycode == D)
	{
		pa+= 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a += pa * 5;
	}
	else if (keycode == 34)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	draw2Dmap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, data->p_x, data->p_y);
	DDA(data->p_x - 12 , data->p_y - 12, data->p_x + pdx * 100, data->p_y + pdy * 100, data);
	DDA(data->p_x - 12 , data->p_y - 12, data->p_x + 50+pdx * 100, (data->p_y + 50 + pdy * 100), data);
	return (0);
}

void ft_init(t_data *data)
{
	int w = 0;
	data->p_x = 64;
	data->p_y = 64;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	data->pl_a = 0;
	data->mlx = mlx_init();
	data->img = mlx_xpm_file_to_image(data->mlx, "./img/player.xpm", &w, &w);
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./img/wall.xpm", &w, &w);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "./img/floor.xpm", &w, &w);
	data->mlx_win = mlx_new_window(data->mlx, 1024, 512, "raycasting");

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 16, 16);
}


int main()
{
	t_data *data = malloc(sizeof(t_data));
	ft_init(data);
	draw2Dmap(data);
	// while (y++ < 100)
	// {
	// 	x = 0;
	// 	while (x++ < 100)
	// 		mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFFFFFF);
	// }
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_event, data);
	mlx_loop(data->mlx);
}




//gcc main.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz