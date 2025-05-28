/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/28 19:22:30 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub_H
# define cub_H
# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"
# include <strings.h>
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

# define SCREEN_SIZE_X 1280
# define SCREEN_SIZE_Y 720
# define LINE_COLOR 0xFFFF00
# define MOVE_SPEED 4.0
# define TILE_SIZE 16
# define SCALE 3
# define ACCEL 10
# define FRICTION 50
# define MAX_SPEED 10
# define JUMP_SPEED 8
# define GRAVITY 10

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef enum	s_state
{
	WALKING,
	IDLE,
	RUNNING,
	JUMPING,
	FALLING
} t_state;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_collision
{
	bool	left;
	bool	right;
	bool	down;
	bool	up;
	bool	is_colliding;
} t_collision;

typedef struct s_player
{
	t_point		pos;
	t_point		direction;
	t_point		velocity;
	t_collision collision;
	bool		jump;
	bool		is_on_ground;
	bool		big;
	bool		left;
}	t_player;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			fd;
	int			map_height;
	int			map_width;
	t_image		ground;
	t_image		mario;
	t_image		brick;
	t_image		background;
	t_image		powerup[3];
	long long	last_frame_time;
	float		delta;
	t_player	player;
	float		cameraX;
	t_image		image;
	int			power_up_frames;
}	t_cub;

int			free_displays(t_cub *cub);
void		init_window(t_cub *cub);

//gameloop
int			game_loop(t_cub *cub);
void		calculate_Delta(t_cub *cub);

//init
void		cub_init(t_cub *cub);
void		get_textures(t_cub *cub);

//input
int			key_pressed(int keysym, t_cub *cub);
int			key_released(int keysym, t_cub *cub);


//animations
void	animation_times(t_cub *cub);
//map
int			ft_load_map(char *map, t_cub *cub);
void		drawmap(t_cub *cub);

//render utils
void		drawrect(t_image *image, t_point pos, t_point size, int color);
void		ft_pixelput(t_image *data, int x, int y, int color);
void	drawtexture(t_cub *cub, t_point pos, t_point size, t_image *text, float scale);


//struct utils
int			check_args(char *str);
void	get_player_pos(t_cub *cub);

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


//debug
void		debug_directions(t_cub *cub);
#endif
