/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 13:00:30 by gde-la-r         ###   ########.fr       */
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

# define WIDTH 1024
# define HEIGHT 768
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

typedef struct s_ray
{
	float	camerax;
	float	rayX;
	float	rayY;
	float	delta_X;
	float	delta_Y;
	bool	hit;
	bool	ray_side;
	float	delta_hit;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	float	wall_hit;
	int		textX;
	t_point	map;
	t_point	ray_pos;
	t_point	step;
	t_image	*texture;
}	t_ray;

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
	float			running;
	char			*fps_string;
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
int		ft_load_map(char *map, t_cub *cub, int checker, char *line);
void	flood_fill(t_cub *cub, int x, int y);
void	flood_fill_caller(t_cub *cub);
int		extract_number(char *str);

//render utils
void		drawrect(t_image *image, t_point pos, t_point size, int color);

void		ft_pixelput(t_image *data, int x, int y, int color);
void		drawline(t_cub *cub, t_point start, t_point dest);
void		drawtexture(t_cub *cub, t_point pos, t_point size, t_ray *ray);
void		circleBres(t_cub *cub, int xc, int yc, int r);

//raycast logic
void		raycast(t_cub *cub);
void		init_ray_start(t_cub *cub, t_ray *ray);
void		ray_init(t_cub *cub, t_ray *ray, int x);
void		get_hit(t_cub *cub, t_ray *ray);
void		get_ray_size(t_cub *cub, t_ray *ray);
void		get_ray_texture(t_cub *cub, t_ray *ray);
t_image		*get_wall_text_from_direction(t_cub *cub, t_ray *ray);

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

//checks
int			check_args(char *str);
int			check_map_line(t_cub *cub, char *line, int i);
int			checkline(t_cub *cub, char *line);
int			check_assets(t_cub *cub, char *line);

//load_map
int			is_space(char c);
int			is_map(char *line);
int			extract_path(t_cub *cub, t_image *image, char *line);
int			handle_color(t_cub *cub, char *line, char which);

//load_map_utils
int			ft_open(char *map, t_cub *cub);
char		*ft_remove_nl(char *line);
char		**append_cmd(char **cmd, char *newcmd);
int			is_space(char c);
int			is_map(char *line);

//colors
bool		ft_load_map_loop(t_cub *cub, char *line, char **temp);
int			handle_color(t_cub *cub, char *line, char which);

#endif
