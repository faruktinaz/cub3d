#include<stdlib.h>
#include <stdio.h>
#include "./mlx/mlx.h"
#include <math.h>
#define DR 0.0174532925
#define PI  3.14159265
#define S 115
#define W 119
#define A 97
#define D 100

float px,py,pdx,pdy; // player position

float pa = 1.3;

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
	void *c_img;
	int *wall_direction;
	float *distances;
	float currentAngle;
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

void drawFloor(t_data *data) {
    int windowWidth = 1024;
    int windowHeight = 512;

    for (int i = 512 / 2; i < 512; i+=64) {
        for (int j = 512; j < 1060; j+= 64) {
            mlx_put_image_to_window(data->mlx, data->mlx_win, data->floor_img, j, i);
        }
    }
}

void drawCeiling(t_data *data) {
    int windowWidth = 1024;
    int windowHeight = 512;

    for (int i = 0; i < 512 / 2; i+=64) {
        for (int j = 512; j < 1060; j+= 64) {
            mlx_put_image_to_window(data->mlx, data->mlx_win, data->c_img, j, i);
        }
    }
}

void draw3DView(t_data *data, int numRays) {
    float wallHeight = 5000;
    float wallWidth = 1;

    int windowWidth = 1024; // upd from data 
    int windowHeight = 512; // upd from data

    for (int i = 0; i < numRays; i++) {
        float distanceToWall = data->distances[i]  ;
		// printf("orta cizgi uzunluk -> %f en sağ çizgi uzunluk -> %f en sol --> %f \n", data->distances[29], data->distances[59], data->distances[0]);

        float wallSize = (1 / distanceToWall) * wallHeight;
        float wallThickness = (1 / distanceToWall) * wallWidth;

        int wallCenter = windowHeight / 2;

        int wallStart = wallCenter - (wallSize / 2) * 2;
        int wallEnd = wallCenter + (wallSize / 2) * 2;

        int wallThicknessStart = i - (wallThickness / 2);
        int wallThicknessEnd = i + (wallThickness / 2);

        int wallColor = 0x402414;

        for (int j = wallStart; j <= wallEnd; j++)
		{
            for (int k = wallThicknessStart*10; k <= wallThicknessEnd*10; k++)
			{
                mlx_pixel_put(data->mlx, data->mlx_win, k + (windowWidth / 2), j, wallColor);
            }
        }
    }
}

int jd = 0;

int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 

void DDA(int X0, int Y0, int X1, int Y1, t_data *data)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
	int num = -1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

	float x1;
	float y1;

//  +20 for player pos
    float X = X0 + 20; // starting position of the line X
    float Y = Y0 + 20; // starting position of the line Y
    for (int i = 0; i <= steps; i++) {
		if (map[(((int)(Y) / 64) * mapY) + (int)((X) / 64)] != 1) // !wall
			mlx_pixel_put(data->mlx, data->mlx_win, X, Y, 0xFF0000);
		else // wall
		{
			// printf("\n\n\n player x -> %f player y -> %f\n", data->p_x + 8 , data->p_y + 8);
			// printf(" *** x-> %f y-> %f\n", X + 20, Y + 20);
			// printf("\n çizginin uzunluğu ---->>> %f \n", sqrt(pow(data->p_x + 8 - X + 20, 2) + pow(data->p_y + 8 - Y + 20, 2)) );
			// printf("pdx-> %f pdy-> %f\n", pdx, pdy);
			// mlx_pixel_put(data->mlx, data->mlx_win, X, Y, 0xFFFFFF);
			// printf("x in karesi + y nin karesinin karekoku -> %d \n",(int)sqrt(pow(data->p_x, 2) + pow((int)Y, 2)));
			break;
		}
        X += Xinc;
        Y += Yinc;
    }
	data->distances[jd] = (sqrt(pow(data->p_x + 8 - X, 2) + pow(data->p_y + 8 - Y, 2))* cos(data->currentAngle - pa));
	jd++;
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
	else if (keycode == 53)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	draw2Dmap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, data->p_x, data->p_y);
	jd = 0;
	for (int i = -30; i <= 30; i++) {
		data->currentAngle = pa + (i * DR); // pov
		float endX = data->p_x - 12 + cos(data->currentAngle) * 1024;
		float endY = data->p_y - 12 + sin(data->currentAngle) * 1024;
		DDA(data->p_x - 12 , data->p_y - 12, (int)endX, (int)endY, data);
	}
	drawCeiling(data);
	drawFloor(data);
	draw3DView(data, 60);
	return (0);
}

void ft_init(t_data *data)
{
	int w = 0;
	data->p_x = 64;
	data->p_y = 64;
	data->distances = malloc(sizeof(float) * 100);
	data->wall_direction = malloc(sizeof(int) * 100);
	pdx = 0;
	pdy = 0;
	data->pl_a = 0;
	data->mlx = mlx_init();
	data->img = mlx_xpm_file_to_image(data->mlx, "./img/player.xpm", &w, &w);
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./img/wall.xpm", &w, &w);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "./img/floor.xpm", &w, &w);
	data->currentAngle = 0.0;
	data->c_img = mlx_xpm_file_to_image(data->mlx, "./img/c.xpm", &w, &w);
	data->mlx_win = mlx_new_window(data->mlx, 1400, 800, "faruktinaz raycasting");

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



// ** For Linux **
// gcc main.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz
// ** For macOS **
// gcc test.c -framework AppKit -framework OpenGL -L./mlx -lmlx -o 2dcub