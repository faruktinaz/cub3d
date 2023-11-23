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

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);

		if (x0 == x1 && y0 == y1)
		{
			break;
		}
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}
int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 
  
void DDA(int X0, int Y0, int X1, int Y1, t_data *data, int is3D)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        if (is3D == 1) {
            for (int j = 20 - 1; j <= 20 + 15; j++) { // Kalınlık için her yöne 1 piksel kaydırma
                for (int k = 20 - 1; k <= 20 + 1; k++) {
                    if (i_color == 0)
                        mlx_pixel_put(data->mlx, data->mlx_win, X + j, Y + k, 0xFF0000); // #960000
                    else if (i_color == 1)
                        mlx_pixel_put(data->mlx, data->mlx_win, X + j, Y + k, 0x960000); // #960000
                }
            }
        } else {
            mlx_pixel_put(data->mlx, data->mlx_win, X + 20, Y + 20, 0xFF0000);
        }
        X += Xinc;
        Y += Yinc;
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void drawRays2D(t_data *data)
{
    int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH, disT;

    ra = pa - DR*30;
    if (ra < 0)
    {
        ra+=2*PI;
    }
    if (ra > 2*PI)
    {
        ra-=2*PI;
    }
    for (r = 0; r < 30; r++)
    {
		// HORIZONTAL
        dof = 0;
		disH = 1000000;
		float hx = data->p_x;
		float hy = data->p_y;
        float aTan = -1/tan(ra);
        if (ra > PI)
        {
            ry = (((int)data->p_y >> 6) << 6) - 0.0001;
            rx = (data->p_y - ry) * aTan + data->p_x;
            yo = -64;
            xo = -yo*aTan;
        }
        if (ra < PI)
        {
            ry = (((int)data->p_y >> 6) << 6) + 64;
            rx = (data->p_y - ry) * aTan + data->p_x;
            yo = 64;
            xo = -yo*aTan;
        }
        if (ra == 0 || ra == PI)
        {
            rx = data->p_x;
            ry = data->p_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my *mapX + mx;
            if (mp > 0 && mp < mapX *mapY && map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				disH = dist(data->p_x, data->p_y, hx, hy, ra);
                dof = 8;
			}
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        ra+= DR;
        if (ra < 0)
            ra+=2*PI;
        if (ra > 2*PI)
            ra-=2*PI;
		// VERTICAL
        dof = 0;
		disV = 1000000;
		float vx = data->p_x;
		float vy = data->p_y;
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3)
        {
            rx = (((int)data->p_x >> 6) << 6) - 0.0001;
            ry = (data->p_x - rx) * nTan + data->p_y;
            xo = -64;
            yo = -xo*nTan;
        }
        if (ra < P2 || ra > P3)
        {
            rx = (((int)data->p_x >> 6) << 6) + 64;
            ry = (data->p_x - rx) * nTan + data->p_y;
            xo = 64;
            yo = -xo*nTan;
        }
        if (ra == 0 || ra == PI)
        {
            rx = data->p_x;
            ry = data->p_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my *mapX + mx;
            if (mp>0 && mp < mapX *mapY && map[mp] == 1)
			{
				vx =rx;
				vy = ry;
				disV = dist(data->p_x, data->p_y, vx, vy, ra);
                dof = 8;
			}
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			i_color = 1;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			i_color = 0;
		}
        DDA(data->p_x - 12, data->p_y - 12, rx, ry, data, 0);
        DDA(data->p_x - 12, data->p_y - 12, rx , ry, data, 0);
		// -----DRAW 3D WALLS-----
		float ca=pa-ra;
		if (ca < 0)
            ca+=2*PI;
        if (ca > 2*PI)
            ca-=2*PI;
		disT = disT*cos(ca);
		float lineH=(mapS* 320) / disT;
		if (lineH>320)
			lineH = 320;
		float lineO = 200-lineH/2;
		DDA(r*15 + 530, lineO, r*15+530, lineH+lineO, data, 1);
		DDA(r*15 + 530, lineO + 50, r*15+530, lineH+lineO, data, 1);
        ra+= DR;
        if (ra < 0)
            ra+=2*PI;
        if (ra > 2*PI)
            ra-=2*PI;
    }
}

void	draw_rays(t_data *data)
{
	int end_x;
	int end_y;

	for (int i = data->pl_a; i < (data->pl_a + 60); i += 5)
	{
		double angle = i * 6.28319 / 360;
		int line_length = 200;
		end_x = data->p_x + line_length * cos(angle);
		end_y = data->p_y + line_length * sin(angle);

		draw_line(data->mlx, data->mlx_win, data->p_x + 32, data->p_y + 32, end_x, end_y);
	}
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->p_y += pdy;
		data->p_x += pdx;
	mlx_clear_window(data->mlx, data->mlx_win);
	}
	else if (keycode == S)
	{
		data->p_y -= pdy;
		data->p_x -= pdx;	
	mlx_clear_window(data->mlx, data->mlx_win);
	}
	else if (keycode == A)
	{
		pa-= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a -= pa * 5 ;

	mlx_clear_window(data->mlx, data->mlx_win);
	}
	else if (keycode == D)
	{
		pa+= 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a += pa * 5;
	mlx_clear_window(data->mlx, data->mlx_win);
	}
	else if (keycode == 34)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	draw2Dmap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, data->p_x, data->p_y);
	// for (int i = 10; i < 20; i++)
	// {
	// 	mlx_pixel_put(data->mlx, data->mlx_win, data->p_x + (pdx * 2) + i, data->p_y + (pdy * 2) + i, 0xFFFF);
	// 	for (int x = 10; x < 20; x++)
	// 		mlx_pixel_put(data->mlx, data->mlx_win, data->p_x + (pdx * 2) + i, data->p_y + (pdy * 2) + x, 0x00000);
		
	// }
    // DDA(data->p_x, data->p_y, data->p_x + pdx * 5, data->p_y + pdy * 5, data);
	// draw_rays(data); yanlis caisiyo
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

int draw_map_3(t_data *data)
{
	drawRays2D(data);
	return 0;
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
	mlx_loop_hook(data->mlx, draw_map_3, data);
	mlx_loop(data->mlx);
}




//gcc main.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz