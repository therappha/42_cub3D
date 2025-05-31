/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 18:43:01 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"
# include <strings.h>
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>

# define SCREEN_SIZE_X 1024
# define SCREEN_SIZE_Y 768
# define LINE_COLOR 0xFFFF00
# define MOVE_SPEED 4.0
# define TILE_SIZE 64
# define CIRCLE_SIZE 60
# define FOV 66
# define CAMERA_SPEED 4.0
# define F 0.1

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point		pos;
	t_point		direction;
	t_point		plane;
	t_point		camera;
	float		camerax;
}	t_player;

typedef struct s_drawline
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
	int	color;
}	t_drawline;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
	bool	found;
	int		x;
	int		y;
}	t_image;

typedef struct s_found
{
	bool	player;
	bool	floor;
	bool	ceiling;
	bool	map;
}	t_found;

/*NO assets/textures/ice.xpm
SO assets/textures/lava.xpm
WE assets/textures/bricks.xpm
EA assets/textures/leaves.xpm

F 101,183,65
C 123,211,234
*/

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**map;
	char			**parsed_map;
	int				fd;
	int				map_height;
	int				map_width;
	t_image			textures[4];
	long long		last_frame_time;
	float			delta;
	t_player		player;
	t_image			image;
	t_found			found;
	int				ceiling_color;
	int				floor_color;
	bool			error;
	bool			debug;
	int				fps;
	char			*fps_string;
	float			running;
}	t_cub;

typedef enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_texture;

int			free_displays(t_cub *cub);
void		init_window(t_cub *cub);

//gameloop
int			game_loop(t_cub *cub);
void		calculate_Delta(t_cub *cub);

//init
void		cub_init(t_cub *cub);
int			get_textures(t_cub *cub);
t_point		get_camera(t_cub *cub, char c);
void		get_player_pos(t_cub *cub);

//input
int			key_pressed(int keysym, t_cub *cub);
int			key_released(int keysym, t_cub *cub);

//map
int			ft_load_map(char *map, t_cub *cub);

//render utils
void		drawrect(t_image *image, t_point pos, t_point size, int color);
//LINE TOO LONG
t_image		*get_wall_color_from_direction(t_cub *cub, int side, float ray_x, float ray_y);
void		ft_pixelput(t_image *data, int x, int y, int color);
//LINE TOO LONG
void		drawline(t_cub *cub, t_point start, t_point dest);
void		drawtexture(t_cub *cub, t_point pos, t_point size, int textX, float wall_heigth, t_image *text);
void		circleBres(t_cub *cub, int xc, int yc, int r);
void		raycast(t_cub *cub);
t_image		*get_wall_color_from_direction(t_cub *cub, int side, float ray_x, float ray_y);

//struct utils
int			check_args(char *str);

//math
int			ft_abs(int num);
long long	get_time(void);
float		clamp(float value, float min, float max);
t_point		normalize(t_point point);

//free utils
void		ft_free_arr(char **arr);
t_point		get_mouse_position(t_cub *cub);

//move
void		move_camera(t_cub *cub);
void		move(t_cub *cub);

//colision.c
void	get_colision(t_point move, t_cub *cub);

//debug
void		debug_directions(t_cub *cub);
#endif
