/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/27 18:12:50 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_load_images(t_cub *cub, t_image *image, char *name, int *x, int *y);

void get_textures(t_cub *cub)
{
	int x = 16;
	int y = 16;

	ft_load_images(cub, &cub->ground, "./assets/ground.xpm", &x, &y);
	ft_load_images(cub, &cub->mario, "./assets/mario.xpm", &x, &y);
	ft_load_images(cub, &cub->brick, "./assets/brick.xpm", &x, &y);
	ft_load_images(cub, &cub->powerup, "./assets/powerup.xpm", &x, &y);



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
