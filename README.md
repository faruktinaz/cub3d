# cub3D
### Wolfenstein 3D inspired Raycasting project

The goal of ``cub3d`` is to make *something* using raycasting (like [Wolfenstein 3D](https://fr.wikipedia.org/wiki/Wolfenstein_3D)).

### How to run it on linux and macOS ?

When you clone the files, by default the linux version of the MLX library is included. If you want to run it on macOS, you need to download the macOS version of MLX and place it in the srcs/library/ file path. 
then just type `"make linux"` or `"make macos"`.

![Screenshot from 2024-01-20 01-31-46](https://github.com/faruktinaz/cub3d/assets/114104599/1982bfa9-1ded-4c93-9bab-779af13ec365)

<p align="center">
![cub3dd](https://github.com/faruktinaz/cub3d/assets/114104599/704855c2-95f6-4305-99d9-6b2c7e2b333f)

</p>

- WASD to move 
- Left-Right directional keys to rotate camera
- ESC to quit

### map

you can change the map according to the rules.

```
NO srcs/texture/north.xpm
SO srcs/texture/south.xpm
WE srcs/texture/west.xpm
EA srcs/texture/east.xpm

C 81, 176, 219
F 64, 41, 10

        11111111111 11111111111111
        10000000011100000000000011111
        1011000001110000011100001001
        1100100000000000000100000111
111111110110000011100000111000011
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
100000000E0000011000000100001
10000000000000001101010010001
11000001110101011111011110001
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- NO, SO, WE, EA texture of the direction of the wall.
- C, F is ceiling and floor rgb colors.

When creating the rays using the DDA algorithm and mlx_put_pixel, for each step I divided the current position of the ray by 64 and checked if there is 1 (i.e. wall) in the map. If there is a wall, I subtracted the x and y coordinates of the last pixel of the line from the x and y coordinates of the character and used a simple Pythagorean theorem to store the lengths of the ray in an array.

<img src="https://github.com/faruktinaz/cub3d/assets/114104599/07bce3cd-95df-4a71-ad68-c3d2e40a4728" width="600" height="500">

---

<img src="https://github.com/faruktinaz/cub3d/assets/114104599/86f1f843-ec5c-46e0-8a79-ce774430a5f9" width="600" height="500">

```c
data->distances[data->jd] = (sqrt(pow(data->p_x + 8 - data->var.x_d, 2) + pow(data->p_y + 8 - data->var.y_d, 2)) * cos(data->current_angle - data->var.pa));
```

