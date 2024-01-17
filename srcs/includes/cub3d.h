/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keopsfenks <keopsfenks@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:28:38 by segurbuz          #+#    #+#             */
/*   Updated: 2023/12/09 04:03:23 by keopsfenks       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_X 1400
# define WINDOW_Y 800
#define DR 0.0174532925
#define PI  3.14159265
#define S 115
#define W 119
#define A 97
#define D 100
#define RIGHT_ARROW 65361
#define LEFT_ARROW 65363
#define ESC 65307

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libarys/mlx/mlx.h"
# include "../libarys/libft/libft.h"
# include "../libarys/get_next_line/get_next_line.h"

enum	e_map
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	MAP,
};

typedef struct s_map
{
	char			*line;
	int				type;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct s_attr
{
	t_map	*map;
	char	**arr_map;
	int 	map_y;
	t_map	*texture;
	t_map	*color;
}			t_attr;

typedef struct s_texture
{
	void	*image;
	char	*data;
	int		use;
	int		w;
	int		h;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_texture;

typedef struct s_image
{
	void	*window;
	int		*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_image;

typedef struct s_var
{
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
}				t_var;

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
	int windowWidth;
	int windowHeight;
	void *enemy_img;
	float currentAngle;
	void *floor_img;
	float 	*wall_X;
	bool	w_check;
	bool	a_check;
	bool	d_check;
	bool	s_check;
	float 	*wall_Y;
	float p_x; // player x;
	float p_y; // player y;
	t_image image;
	t_texture	textures[4];
	int	skyc;
	int floorc;
	char	*map_arg;
	t_map	*map_cub;
	t_var	var;
	t_attr	*attr;
}	t_data;

void	ft_parse(t_data *data);
t_map	*ms_lstnew(int type, void *content);
void	ms_lstadd_back(t_map **lst, t_map *new);
int	ms_lstsize(t_map *lst);
t_map	*ms_lstlast(t_map *lst);
void	ft_error(void);
void	map_attr_add_data(t_data *data);
bool	map_find_attr(char *line, char *find);
void	read_map(t_data *data);
void	map_invalid_char(char *line, bool **flag);
void	parse_with_color(char *line, bool *flag, int *rule);
void	parse_with_map_content(char *line, bool *flag, int *check);
bool	map_find_attr(char *line, char *find);
bool	is_check(char c);
void	found_and_implement(t_map *map, int i, bool **flag);
void	map_find_space_in_content(t_map *map, bool **flag);
void	find_tab_in_map(t_map *map, bool *flag);
void	parse_with_color2(char *line, int *check, int *rule, bool *flag);
void	parse_with_color3(char *line, int *digit_check, bool *flag, int *i);
void	read_map_2(t_data *data, t_map *map, enum e_map type);
void	xpm_to_textures(t_data *data);
void	start_img(t_data *data);
unsigned int	get_pixel_in_texture(t_texture *texture, int x, int y);
void	img_pix_put(t_image *image, int x, int y, int color);



#endif