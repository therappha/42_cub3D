/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 11:58:29 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_ray_start(t_cub *cub, t_ray *ray)
{
	if (ray->rayX < 0)
	{
		ray->step.x = -1;
		ray->ray_pos.x = (cub->player.pos.x - ray->map.x) * ray->delta_X;
	}
	else
	{
		ray->step.x = 1;
		ray->ray_pos.x = (ray->map.x + 1.0 - cub->player.pos.x) * ray->delta_X;
	}
	if (ray->rayY < 0)
	{
		ray->step.y = -1;
		ray->ray_pos.y = (cub->player.pos.y - ray->map.y) * ray->delta_Y;
	}
	else
	{
		ray->step.y = 1;
		ray->ray_pos.y = (ray->map.y + 1.0 - cub->player.pos.y) * ray->delta_Y;
	}
}

void	ray_init(t_cub *cub, t_ray *ray, int x)
{
	ray->texture = NULL;
	ray->map.x = (int)cub->player.pos.x;
	ray->map.y = (int)cub->player.pos.y;
	ray->hit = false;
	ray->camerax = 2 * x / (double)SCREEN_SIZE_X - 1;
	ray->rayX = cub->player.camera.x + cub->player.plane.x * ray->camerax;
	ray->rayY = cub->player.camera.y + cub->player.plane.y * ray->camerax;
	ray->delta_X = sqrt(1 + (ray->rayY / ray->rayX) * (ray->rayY / ray->rayX));
	ray->delta_Y = sqrt(1 + (ray->rayX / ray->rayY) * (ray->rayX / ray->rayY));
	ray->ray_side = false;
	init_ray_start(cub, ray);
}

void	get_hit(t_cub *cub, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->ray_pos.x < ray_pos.y)
		{
			ray->ray_pos.x += ray->delta_X;
			ray->map.x += ray->step.x;
			ray->ray_side = 0;
		}
		else
		{
			ray->ray_pos.y += ray->delta_Y;
			ray->map.y += ray->step.y;
			ray->ray_side = 1;
		}
		if (ray->map.y < 0 || ray->map.x < 0 || ray->map.x >= cub->map_width
			|| ray->map.y >= cub->map_height)
			break;
		if (cub->map[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = true;
	}
}

void	raycast(t_cub *cub)
{
	t_ray	ray;
	int		x;

	x = 0;

	while (x < SCREEN_SIZE_X)
	{
		ray_init(cub, &ray, x);
		get_hit(cub, ray);

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
		x++;
	}
}
