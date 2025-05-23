/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/22 16:00:33 by rafaelfe         ###   ########.fr       */
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
# include <pthread.h>

# define SCREEN_SIZE_X 1280
# define SCREEN_SIZE_Y 720
# define LINE_COLOR 0xFFFFFF
# define TILE_SIZE 32
# define CAMERA_SPEED 2
# define FOV 90

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point pos;
	t_point direction;
	t_point plane;
	t_point camera;
	int		camerax;
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
}	t_image;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	char		**map;
	int			fd;
	int			map_height;
	int			map_width;
	t_image		north_texture;
	t_image		south_texture;
	t_image		east_texture;
	t_image		west_texture;
	t_image	image;
	t_image game;
	t_image	background;
	pthread_mutex_t draw_mutex;
}	t_cub;

typedef struct s_data
{
	int from;
	int to;
	t_cub *cub;
	t_player player;
} t_data;

void	drawline(t_cub *cub, t_point start, t_point dest);
int		free_displays(t_cub *cub);
void	ft_pixelput(t_image *data, int x, int y, int color);
int		input_handler(int keysym, t_cub *cub);
void	init_window(t_cub *cub);
void	ft_pixelput(t_image *data, int x, int y, int color);

//struct utils
int		check_args(char *str);

//math
int	ft_abs(int num);
long long	get_time(void);

#endif
