# cub3d

 This project aims at reproducing a basic FPS game by using the raycasting method.

When creating the rays using the DDA algorithm and mlx_put_pixel, for each step I divided the current position of the ray by 64 and checked if there is 1 (i.e. wall) in the map.
If there is a wall, I subtracted the x and y coordinates of the last pixel of the line from the x and y coordinates of the character and used a simple Pythagorean theorem to store the lengths of the ray in an array.


<img src="https://github.com/faruktinaz/cub3d/assets/114104599/86f1f843-ec5c-46e0-8a79-ce774430a5f9" width="600" height="500">
