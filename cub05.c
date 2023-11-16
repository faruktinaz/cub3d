#include<stdlib.h>
#include <stdio.h>
#include "./mlx/mlx.h"
#include <math.h>

#define PI  3.141592
#define S 115
#define W 119
#define A 97
#define D 100

float px,py,pdx,pdy,pa; // player position

int mapX=16, mapY=16, mapS=256;
int map[]=
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};


typedef struct s_data
{
	void *mlx;
	void *mlx_win;
	void *img;
	void *wall_img;
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
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall_img, (x*32), (y*32));
			else if (map[y*mapX+x] == 0)
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->floor_img, (x*32), (y*32));
			x++;
		}
		y++;
	}
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
		pa-= 0.4;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 10;
		pdy = sin(pa) * 10;

	}
	else if (keycode == D)
	{
		pa+= 0.4;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 10;
		pdy = sin(pa) * 10;
	}
	else if (keycode == 34)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	draw2Dmap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, data->p_x, data->p_y);
	for (int i = 10; i < 20; i++)
	{
		mlx_pixel_put(data->mlx, data->mlx_win, data->p_x + (pdx * 2) + i, data->p_y + (pdy * 2) + i, 0xFFFF);
		for (int x = 10; x < 20; x++)
			mlx_pixel_put(data->mlx, data->mlx_win, data->p_x + (pdx * 2) + i, data->p_y + (pdy * 2) + x, 0x00000);
		
	}
	return (0);
}

void ft_init(t_data *data)
{
	int w = 0;
	data->p_x = 32;
	data->p_y = 32;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	data->mlx = mlx_init();
	data->img = mlx_xpm_file_to_image(data->mlx, "./img/player.xpm", &w, &w);
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./img/wall.xpm", &w, &w);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "./img/floor.xpm", &w, &w);
	data->mlx_win = mlx_new_window(data->mlx, 1024, 528, "raycasting");

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 32, 32);
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



// gcc main.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz  ** for Linux **