/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/28 19:16:20 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_load_images(t_cub *cub, t_image *image, char *name, int *x, int *y);

void get_textures(t_cub *cub)
{
	int x = 16;
	int y = 16;

	(*cub).background.img = mlx_new_image((*cub).mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	(*cub).background.addr = mlx_get_data_addr((*cub).background.img, &(*cub).background.bits_per_pixel, &(*cub).background.line_length, &(*cub).background.endian);
	drawrect(&cub->background, (t_point){0, 0}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y}, 0x5c94fc);

	(*cub).image.img = mlx_new_image((*cub).mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	(*cub).image.addr = mlx_get_data_addr((*cub).image.img, &(*cub).image.bits_per_pixel, &(*cub).image.line_length, &(*cub).image.endian);

	ft_load_images(cub, &cub->ground, "./assets/ground.xpm", &x, &y);
	ft_load_images(cub, &cub->mario, "./assets/mario.xpm", &x, &y);
	ft_load_images(cub, &cub->brick, "./assets/brick.xpm", &x, &y);
	ft_load_images(cub, &cub->powerup[0], "./assets/powerup0.xpm", &x, &y);
	ft_load_images(cub, &cub->powerup[1], "./assets/powerup1.xpm", &x, &y);
	ft_load_images(cub, &cub->powerup[2], "./assets/powerup2.xpm", &x, &y);
}
int	ft_load_images(t_cub *cub, t_image *image, char *name, int *x, int *y)
{
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			name, x, y);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, \
			&image->bits_per_pixel, &image->line_length, \
			&image->endian);
	return (1);
}
