/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/07 20:34:17 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	raycast(t_cub *cub)
{
	t_ray	ray;
	int		i;
	t_point	draw_size;
	t_point	draw_pos;
	float x;
	float y;
	float z;
	float rx;
	float ry;
	int color;

	t_point p;
	t_point texture;

	i = 0;
	while (i < WIDTH)
	{
		ray_init(cub, &ray, i);
		int j = HEIGHT >> 1;
		while (j < HEIGHT)
		{
			x = (WIDTH / 2 - i);
			y = j + FOCAL_LEN;
			z = j - HEIGHT / 2 + 0.01;
			rx = (y * cub->player.camera.x + x * -cub->player.plane.x);
			ry = (y * cub->player.camera.y + x * -cub->player.plane.y);
			p.x = (rx / z + cub->player.pos.x ) * SCALE;
			p.y = (ry / z  +cub->player.pos.y ) * SCALE;
			texture.x = clamp((int)p.x % cub->floor_texture.x, 0, cub->floor_texture.x -1);
			texture.y = clamp((int)p.y % cub->floor_texture.y, 0, cub->floor_texture.y -1);
			color = *(int *)((cub->floor_texture.addr + ((int)texture.y * cub->floor_texture.line_length + (int)texture.x * ((cub->floor_texture).bits_per_pixel / 8))));
			ft_pixelput(&cub->image, i, j, color);
			j++;
		}

		get_hit(cub, &ray);
		get_ray_size(cub, &ray);
		get_ray_texture(cub, &ray);
		draw_pos = (t_point){i, ray.wall_start};
		draw_size = (t_point){1, ray.wall_end - ray.wall_start};
		drawtexture(cub, draw_pos, draw_size, &ray);
		i++;
	}
}
