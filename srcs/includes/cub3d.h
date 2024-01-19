/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaz <tinaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:28:38 by segurbuz          #+#    #+#             */
/*   Updated: 2024/01/20 00:14:37 by tinaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DR 0.0174532925
# define PI  3.14159265



// *-*-*- FOR LINUX -*-*-*
# ifdef __linux__
#  define S 115
#  define W 119
#  define A 97
#  define D 100
#  define RIGHT_ARROW 65363
#  define LEFT_ARROW 65361
#  define ESC 65307

// *-*-*- FOR MACOS -*-*-*
# elif __APPLE__
#  define S 1
#  define W 13
#  define A 0
#  define D 2
#  define RIGHT_ARROW 124
#  define LEFT_ARROW 123
#  define ESC 53
# endif


# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../librarys/mlx/mlx.h"
# include "../librarys/libft/libft.h"
# include "../librarys/get_next_line/get_next_line.h"

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
	int		map_y;
	t_map	*texture;
	t_map	*color;
}			t_attr;

typedef struct s_texture
{
	void	*image;
	char	*data;
	int		use;
	int		type;
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
	int			dx;	
	int			dy;
	int			steps;
	float		xinc;
	float		yinc;	
	float		x_d;
	float		y_d;
	int			wallcolor;
	float		walltes;
	float		wall_x;
	float		wall_y;
	int			k;
	float		pdx;
	float		pdy;
	float		pa;
	bool		flag;
}				t_var;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	float		pl_a;
	void		*c_img;
	int			*wall_direction;
	float		*distances;
	int			window_width;
	int			window_height;
	int			end;
	int			end_i;
	int			end_j;
	int			direction;
	int			jd;
	int			height;
	int			start;
	float		current_angle;
	float		*wall_x;
	bool		w_check;
	bool		a_check;
	bool		d_check;
	bool		s_check;
	float		*wall_y;
	float		p_x;
	float		p_y;
	t_image		image;
	t_texture	textures[4];
	int			skyc;
	int			floorc;
	char		*map_arg;
	t_map		*map_cub;
	t_var		var;
	t_attr		*attr;
}	t_data;

void			set_player_angle(t_data *data);
int				key_event(int keycode, t_data *data);
void			check_keyevent_ud(t_data *data, int keycode);
void			check_keyevent_lr(t_data *data, int keycode);
int				check_action_s(t_data *data);
int				check_action_w(t_data *data);
int				check_action_d(t_data *data, float t_pdy, float t_pdx);
int				check_action_a(t_data *data, float t_pdy, float t_pdx);
void			ft_exit(char *str);
int				raycasting(t_data *data);
void			img_pix_put(t_image *image, int x, int y, int color);
unsigned int	get_pixel_in_texture(t_texture *texture, int x, int y);
void			put_background(t_data *data);
void			draw3d_view(t_data *data, int numRays);
int				raycasting(t_data *data);
void			draw3d_view_wallsize(t_data *data, \
	int walltstart, int walltend, int i);
void			dda(int x1, int y1, t_data *data);
void			check_wall_dir(t_data *data, int i);
void			set_raycasting_dir(t_data *data, int *i);
void			set_directions(t_data *data);
void			ray_sending(t_data *data);
void			set_raycasting_dir(t_data *data, int *i);
void			set_raycasting_dir2(t_data *data, int *i);
int				abs(int n);
void			ft_init(t_data *data);
void			create_rgb(char *line, enum e_map type, t_data *data);
void			ft_parse(t_data *data);
t_map			*ms_lstnew(int type, void *content);
void			ms_lstadd_back(t_map **lst, t_map *new);
int				ms_lstsize(t_map *lst);
t_map			*ms_lstlast(t_map *lst);
void			ft_error(void);
void			map_attr_add_data(t_data *data);
bool			map_find_attr(char *line, char *find);
void			read_map(t_data *data);
void			map_invalid_char(char *line, bool **flag);
void			parse_with_color(char *line, bool *flag, int *rule);
void			parse_with_map_content(char *line, bool *flag, int *check);
bool			map_find_attr(char *line, char *find);
bool			is_check(char c);
void			found_and_implement(t_map *map, int i, bool **flag);
void			map_find_space_in_content(t_map *map, bool **flag);
void			find_tab_in_map(t_map *map, bool *flag);
void			parse_with_color2(char *line, int *check, \
				int *rule, bool *flag);
void			parse_with_color3(char *line, int *digit_check, \
				bool *flag, int *i);
void			read_map_2(t_data *data, t_map *map, enum e_map type);
void			xpm_to_textures(t_data *data);
void			start_img(t_data *data);
unsigned int	get_pixel_in_texture(t_texture *texture, int x, int y);
void			img_pix_put(t_image *image, int x, int y, int color);
void			check_file_name(char *name);
void			map_left_wall_check(t_map *map, bool **flag);
void			attr_add_data2(enum e_map type, char *line, int *i);
void			attr_add_data(char *line \
				, t_map **texture, enum e_map type, int *check);
void			num_limit_check(int *color);
int				x_button(t_data *data);
void			invalid_char2(t_map *tmp, bool *flag);

#endif