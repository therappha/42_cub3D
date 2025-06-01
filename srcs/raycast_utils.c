/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:48:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 13:00:30 by gde-la-r         ###   ########.fr       */
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
	ray->camerax = 2 * x / (double)WIDTH - 1;
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
		if (ray->ray_pos.x < ray->ray_pos.y)
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
		{
			break ;
		}
		if (cub->map[(int)ray->map.y][(int)ray->map.x] == '1')
		{
			ray->hit = true;
		}
	}
}

void	get_ray_size(t_cub *cub, t_ray *ray)
{
	if (ray->ray_side == 0)
	{
		ray->delta_hit = ((int)ray->map.x - cub->player.pos.x
				+ (1 - ray->step.x) / 2) / ray->rayX;
	}
	else
	{
		ray->delta_hit = ((int)ray->map.y - cub->player.pos.y
				+ (1 - ray->step.y) / 2) / ray->rayY;
	}
	ray->wall_height = (int)(HEIGHT / ray->delta_hit);
	ray->wall_start = -ray->wall_height / 2 + HEIGHT / 2;
	if (ray->wall_start < 0)
	{
		ray->wall_start = 0;
	}
	ray->wall_end = ray->wall_height / 2 + HEIGHT / 2;
	if (ray->wall_end >= HEIGHT)
	{
		ray->wall_end = HEIGHT - 1;
	}
}

void	get_ray_texture(t_cub *cub, t_ray *ray)
{
	if (ray->ray_side)
	{
		ray->wall_hit = cub->player.pos.x + ray->delta_hit * ray->rayX;
	}
	else
	{
		ray->wall_hit = cub->player.pos.y + ray->delta_hit * ray->rayY;
	}
	ray->texture = get_wall_text_from_direction(cub, ray);
	ray->wall_hit -= floor(ray->wall_hit);
	ray->textX = (int)(ray->texture->x * ray->wall_hit);
	if (ray->ray_side && ray->rayY > 0)
		ray->textX = ray->texture->x - ray->textX - 1;
	if (!ray->ray_side && ray->rayX < 0)
		ray->textX = ray->texture->x - ray->textX -1;
}
