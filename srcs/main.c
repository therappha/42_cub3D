/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
/* ************************************************************************** */

#include "../includes/cub.h"

t_player player;
float	speed = 1;
float delta = 0;
long long last_frame_time = 0;

void	drawrect(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			ft_pixelput(image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

float clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}


int	key_press(int keysym, t_cub *cub)
{
	(void)cub;
	if (keysym == XK_Escape)
	{
		free_displays(cub);
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		player.direction.x += -1;
		player.direction.x = clamp(player.direction.x, -1, 1);
	}
	if (keysym == XK_D || keysym == XK_d)
	{
		player.direction.x += 1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	if (keysym == XK_W || keysym == XK_w)
	{
		player.direction.y += -1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	if (keysym == XK_S || keysym == XK_s)
	{
		player.direction.y += 1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	return (0);
}


int	key_release(int keysym, t_cub *cub)
{
	(void)cub;
	if (keysym == XK_Escape)
	{
		free_displays(cub);
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		player.direction.x += 1;
		player.direction.x = clamp(player.direction.x, -1, 1);
	}
	if (keysym == XK_D || keysym == XK_d)
	{
		player.direction.x += -1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	if (keysym == XK_W || keysym == XK_w)
	{
		player.direction.y += 1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	if (keysym == XK_S || keysym == XK_s)
	{
		player.direction.y += -1;
		player.direction.x = clamp(player.direction.x, -1, 1);

	}
	return (0);
}

void	calculate_Delta(void)
{
	delta = (get_time() - last_frame_time) / 1000.0f;
	last_frame_time = get_time();
}
int update(t_cub *cub);

int	main(int ac, char **av)
{
	t_cub	cub;
	(void)av; (void) ac;

	init_window(&cub);
	player.pos = (t_point){SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2};
	player.direction = (t_point){0, 0};
	mlx_loop_hook(cub.mlx_ptr, &update, &cub);
	mlx_hook(cub.win_ptr, 2, 1L << 0, &key_press, &cub);
	mlx_hook(cub.win_ptr, 3, 1L << 1, &key_release, &cub);
	mlx_loop(cub.mlx_ptr);
}
void	move()
{
	if (player.direction.x != 0)
	{
		player.pos.x += player.direction.x * speed * delta;
	}
	if (player.direction.y != 0)
	{
		player.pos.y += player.direction.y * speed * delta;
	}

}

int update(t_cub *cub)
{
	calculate_Delta();
	cub->image.img = mlx_new_image(cub->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bits_per_pixel,
			&cub->image.line_length, &cub->image.endian);

	drawrect(&cub->image, player.pos, (t_point){30, 30}, 0xFF0000);
	move();
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	return (0);
}
