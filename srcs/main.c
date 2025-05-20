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
t_player player2;
t_player ball;
t_point padsize = {20, 100};
t_point ballsize = {15, 15};
float	ball_speed = 300;
float	ball_accel = 500;
bool	started = false;
float	speed = 500;
float delta = 0;
float gravity = 10;
float accel = 500;
float friction = 500;
long long last_frame_time = 0;


int	game_loop(t_cub *cub);
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
	if (keysym ==  XK_Up)
	{
		player2.direction.y += -1;
		player2.direction.x = clamp(player2.direction.x, -1, 1);

	}
	if (keysym == XK_Down)
	{
		player2.direction.y += 1;
		player2.direction.x = clamp(player2.direction.x, -1, 1);
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

	if (keysym == XK_Up)
	{
		player2.direction.y += 1;
		player2.direction.x = clamp(player2.direction.x, -1, 1);

	}
	if (keysym == XK_Down)
	{
		player2.direction.y += -1;
		player2.direction.x = clamp(player2.direction.x, -1, 1);

	}
	return (0);
}

void	calculate_Delta(void)
{
	delta = (get_time() - last_frame_time) / 1000.0f;
	last_frame_time = get_time();
}
int update(t_cub *cub);


void init_players()
{
	player.pos = (t_point){ 20, SCREEN_SIZE_Y / 2 };
	player.direction = (t_point){0, 0};
	player2.pos = (t_point){SCREEN_SIZE_X - 40, SCREEN_SIZE_Y / 2};
	player2.direction = (t_point){0, 0};
	ball.pos = (t_point){SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2};
	ball.direction = (t_point){-1, 0.76};
	ball.velocity.x = ball.direction.x * ball_speed;
	ball.velocity.y = ball.direction.y * ball_speed;
}
int	main(int ac, char **av)
{
	t_cub	cub;
	(void)av; (void) ac;
	srand(time(NULL));
	init_window(&cub);


	init_players();
	mlx_loop_hook(cub.mlx_ptr, &game_loop, &cub);
	mlx_hook(cub.win_ptr, 2, 1L << 0, &key_press, &cub);
	mlx_hook(cub.win_ptr, 3, 1L << 1, &key_release, &cub);
	mlx_loop(cub.mlx_ptr);
}

void	move()
{
	if (player.direction.y != 0)
	{
		player.velocity.y += player.direction.y * accel * delta;
		player.velocity.y = clamp(player.velocity.y, -speed, speed);
	}
	if (player.direction.y == 0)
	{
		if (player.velocity.y > 0)
			player.velocity.y -= friction * delta;
		else if (player.velocity.y < 0)
			player.velocity.y += friction * delta;
		else
			player.velocity.y = 0;
	}
	player.pos.y += player.velocity.y * delta;
	if (player.pos.y < 0)
	{
		player.velocity.y = 0;
		player.pos.y = 0;
	}
	if (player.pos.y > SCREEN_SIZE_Y - padsize.y)
	{
		player.velocity.y = 0;
		player.pos.y = SCREEN_SIZE_Y - padsize.y;
	}

	if (player2.direction.y != 0)
	{
		player2.velocity.y += player2.direction.y * accel * delta;
		player2.velocity.y = clamp(player2.velocity.y, -speed, speed);
	}
	if (player2.direction.y == 0)
	{
		if (player2.velocity.y > 0)
			player2.velocity.y -= friction * delta;
		else if (player2.velocity.y < 0)
			player2.velocity.y += friction * delta;
		else
			player2.velocity.y = 0;
	}
	player2.pos.y += player2.velocity.y * delta;
	if (player2.pos.y < 0)
	{
		player2.velocity.y = 0;
		player2.pos.y = 0;
	}
	if (player2.pos.y > SCREEN_SIZE_Y - padsize.y)
	{
		player2.pos.y = SCREEN_SIZE_Y - padsize.y;
		player2.velocity.y = 0;
	}

}

int renderer(t_cub *cub)
{
	calculate_Delta();
	cub->image.img = mlx_new_image(cub->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bits_per_pixel,
			&cub->image.line_length, &cub->image.endian);

	drawline(cub, (t_point){SCREEN_SIZE_X / 2, 0}, (t_point){SCREEN_SIZE_X / 2, SCREEN_SIZE_Y});
	drawrect(&cub->image, player.pos, padsize, 0xFF0000);
	drawrect(&cub->image, player2.pos, padsize, 0x00FF00);
	drawrect(&cub->image, ball.pos, ballsize, 0xFFFFFF);


	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	return (0);
}

void	move_ball()
{
	if (ball.pos.x < 0)
	{
		ball.direction.x = -ball.direction.x;
	}
	if (ball.pos.x > SCREEN_SIZE_X - ballsize.x)
	{
		ball.direction.x = -ball.direction.x;
		ball.pos.x = SCREEN_SIZE_X - ballsize.x;
	}
	if (ball.pos.y < 0)
	{
		ball.direction.y = -ball.direction.y;
	}
	if (ball.pos.y > SCREEN_SIZE_Y - ballsize.y)
	{
		ball.direction.y = -ball.direction.y;
		ball.pos.y = SCREEN_SIZE_Y - ballsize.y;
	}


	ball.pos.x += ball.direction.x * ball_speed *  delta;
	ball.pos.y += ball.direction.y * ball_speed * delta;

}

int update(t_cub *cub)
{
	(void)cub;
	calculate_Delta();
	if (started)
	{
		move();
		move_ball();
	}
	return (0);
}
int	game_loop(t_cub *cub)
{
	update(cub);
	renderer(cub);
	started = true;
	return (0);
}
