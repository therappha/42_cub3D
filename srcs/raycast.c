/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 12:20:10 by rafaelfe         ###   ########.fr       */
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
	bool	hit;
	bool	ray_side = 0;;
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

	for (int x = 0; x < SCREEN_SIZE_X; x++)
	{
		texture = NULL;
		map.x = (int)cub->player.pos.x;
		map.y = (int)cub->player.pos.y;
		hit = false;
		camerax = 2 * x / (double)SCREEN_SIZE_X - 1;
		rayX = cub->player.camera.x + cub->player.plane.x * camerax;
		rayY = cub->player.camera.y + cub->player.plane.y * camerax;

		delta_X = sqrt(1 + (rayY / rayX) * (rayY / rayX));
		delta_Y = sqrt(1 + (rayX / rayY) * (rayX / rayY));

		if (rayX < 0)
		{
			step.x = -1;
			ray_pos.x = (cub->player.pos.x - map.x) * delta_X;
		}
		else
		{
			step.x = 1;
			ray_pos.x = (map.x + 1.0 - cub->player.pos.x) * delta_X;
		}
		if (rayY < 0)
		{
			step.y = -1;
			ray_pos.y = (cub->player.pos.y - map.y) * delta_Y;
		}
		else
		{
			step.y = 1;
			ray_pos.y = (map.y + 1.0 - cub->player.pos.y) * delta_Y;
		}
		while (!hit) // get_hit(t_ray *);
		{
			if (ray_pos.x < ray_pos.y)
			{
				ray_pos.x += delta_X;
				map.x += step.x;
				ray_side = 0;
			}
			else
			{
				ray_pos.y += delta_Y;
				map.y += step.y;
				ray_side = 1;
			}
			if (map.y < 0 || map.x < 0 )
				break;
			if (cub->map[(int)map.y][(int)map.x] == '1')
				hit = true;
		}
		if (ray_side == 0)
			delta_hit = ((int)map.x - cub->player.pos.x + (1 - step.x) / 2) / rayX;
		else
			delta_hit = ((int)map.y - cub->player.pos.y + (1 - step.y) / 2) / rayY;

		wall_height = (int)(SCREEN_SIZE_Y / delta_hit);
		wall_start = -wall_height / 2 + SCREEN_SIZE_Y / 2;
		if (wall_start < 0)
			wall_start = 0;
		wall_end = wall_height / 2 + SCREEN_SIZE_Y / 2;
		if (wall_end >= SCREEN_SIZE_Y)
			wall_end = SCREEN_SIZE_Y - 1;
		if (ray_side)
			wall_hit = cub->player.pos.x + delta_hit * rayX;
		else
			wall_hit = cub->player.pos.y + delta_hit * rayY;
		texture = get_wall_color_from_direction(cub, ray_side, rayX, rayY);
		wall_hit -= floor(wall_hit);
		textX =  (int)(texture->x * wall_hit);
		if (ray_side && rayY > 0)
			textX = texture->x - textX - 1;
		if (!ray_side && rayX < 0)
			textX = texture->x - textX -1;
		drawtexture(cub, (t_point){x, wall_start}, (t_point){1, wall_end - wall_start}, textX, wall_height, texture);
	}
}
