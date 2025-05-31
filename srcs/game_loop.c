/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 11:25:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	update(t_cub *cub)
{
	calculate_Delta(cub);
	move_camera(cub);
	move(cub);
	return (1);
}

int	renderer(t_cub *cub)
{
	(*cub).image.img = mlx_new_image((*cub).mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	(*cub).image.addr = mlx_get_data_addr((*cub).image.img, &(*cub).image.bits_per_pixel, &(*cub).image.line_length, &(*cub).image.endian);
	drawrect(&cub->image, (t_point){0, 0}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y / 2}, cub->ceiling_color);
	drawrect(&cub->image, (t_point){0, SCREEN_SIZE_Y / 2}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y / 2}, cub->floor_color);

	raycast(cub);

	//debug_directions(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	return (1);
}

int	game_loop(t_cub *cub)
{
	update(cub);
	renderer(cub);
	return (1);
}
