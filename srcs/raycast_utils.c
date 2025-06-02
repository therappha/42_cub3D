/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:48:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 16:48:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_ray_start(t_cub *cub, t_ray *ray)
{
	if (ray->rayx < 0)
	{
		ray->step.x = -1;
		ray->ray_pos.x = (cub->player.pos.x - ray->map.x) * ray->delta_x;
	}
	else
	{
		ray->step.x = 1;
		ray->ray_pos.x = (ray->map.x + 1.0 - cub->player.pos.x) * ray->delta_x;
	}
	if (ray->rayy < 0)
	{
		ray->step.y = -1;
		ray->ray_pos.y = (cub->player.pos.y - ray->map.y) * ray->delta_y;
	}
	else
	{
		ray->step.y = 1;
		ray->ray_pos.y = (ray->map.y + 1.0 - cub->player.pos.y) * ray->delta_y;
	}
}

void	ray_init(t_cub *cub, t_ray *ray, int x)
{
	ray->texture = NULL;
	ray->map.x = (int)cub->player.pos.x;
	ray->map.y = (int)cub->player.pos.y;
	ray->hit = false;
	ray->camerax = 2 * x / (double)WIDTH - 1;
	ray->rayx = cub->player.camera.x + cub->player.plane.x * ray->camerax;
	ray->rayy = cub->player.camera.y + cub->player.plane.y * ray->camerax;
	ray->delta_x = sqrt(1 + (ray->rayy / ray->rayx) * (ray->rayy / ray->rayx));
	ray->delta_y = sqrt(1 + (ray->rayx / ray->rayy) * (ray->rayx / ray->rayy));
	ray->ray_side = false;
	init_ray_start(cub, ray);
}

void	get_hit(t_cub *cub, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->ray_pos.x < ray->ray_pos.y)
		{
			ray->ray_pos.x += ray->delta_x;
			ray->map.x += ray->step.x;
			ray->ray_side = 0;
		}
		else
		{
			ray->ray_pos.y += ray->delta_y;
			ray->map.y += ray->step.y;
			ray->ray_side = 1;
		}
		if (ray->map.y < 0 || ray->map.x < 0 || ray->map.x >= cub->map_width + 2
			|| ray->map.y >= cub->map_height + 2)
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
				+ (1 - ray->step.x) / 2) / ray->rayx;
	}
	else
	{
		ray->delta_hit = ((int)ray->map.y - cub->player.pos.y
				+ (1 - ray->step.y) / 2) / ray->rayy;
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
		ray->wall_hit = cub->player.pos.x + ray->delta_hit * ray->rayx;
	}
	else
	{
		ray->wall_hit = cub->player.pos.y + ray->delta_hit * ray->rayy;
	}
	ray->texture = get_wall_text_from_direction(cub, ray);
	ray->wall_hit -= floor(ray->wall_hit);
	ray->textx = (int)(ray->texture->x * ray->wall_hit);
	if (ray->ray_side && ray->rayy > 0)
		ray->textx = ray->texture->x - ray->textx - 1;
	if (!ray->ray_side && ray->rayx < 0)
		ray->textx = ray->texture->x - ray->textx -1;
}
