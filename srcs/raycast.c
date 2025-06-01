/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 12:48:11 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	raycast(t_cub *cub)
{
	t_ray	ray;
	int		x;
	t_point	draw_size;
	t_point	draw_pos;

	x = 0;
	while (x < SCREEN_SIZE_X)
	{
		ray_init(cub, &ray, x);
		get_hit(cub, &ray);
		get_ray_size(cub, &ray);
		get_ray_texture(cub, &ray);
		draw_pos = (t_point){x, ray.wall_start};
		draw_size = (t_point){1, ray.wall_end - ray.wall_start};
		drawtexture(cub, draw_pos, draw_size, &ray);
		x++;
	}
}
