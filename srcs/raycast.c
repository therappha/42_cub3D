/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 20:49:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	debug_raycast(t_cub *cub, t_point rays)
{
	drawline(cub, (t_point){ SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 4}, (t_point){ SCREEN_SIZE_X / 2 + rays.x * CIRCLE_SIZE, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 4 + rays.y * CIRCLE_SIZE});

}
void	raycast(t_cub *cub)
{
	float	camerax;
	float	rayX;
	float	rayY;
	float	delta_X;
	float	delta_Y;
	int		size = 90;
	bool	hit = false;
	t_point	map = cube->player.pos;
	t_point	ray_pos;
	t_point	step;
	//circleBres(cub, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 4, CIRCLE_SIZE);
	for (int x = 0; x < SCREEN_SIZE_X; x++)
	{

		camerax = 2 * x / (double)SCREEN_SIZE_X - 1;
		rayX = cub->player.camera.x + cub->player.plane.x * camerax;
		rayY = cub->player.camera.y + cub->player.plane.y * camerax;

		delta_X = sqrt(1 + (rayY / rayX) * (rayY / rayX));
		delta_Y = sqrt(1 + (rayX / rayY) * (rayX / rayY));

		if (rayX < 0)
		{
			step.x = -1;
			ray_pos.x = (cube->player.pos.x - map.x) * delta_X;
		}
		else
		{
			step.x = 1;
			ray_pos.x = (map.x + 1.0 - cube->player.pos.x) * delta_X;
		}
		if (rayY < 0)
		{
			step.y = -1;
			ray_pos.y = (cube->player.pos.y - map.y) * delta_Y;
		}
		else
		{
			step.y = 1;
			ray_pos.y = (map.y + 1.0 - cube->player.pos.y) * delta_Y;
		}
		//size = distancia perpendicular do player ate onde o raio bateu;
		drawrect(&cub->image, (t_point){x, SCREEN_SIZE_Y / 2 - size / 2}, (t_point){1, size}, 0xFFFF00);
		//debug_raycast(cub, normalize((t_point){rayX, rayY}));
	}
}
