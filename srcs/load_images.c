/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 04:25:36 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_load_images(t_cub *cub, t_image *image, int *x, int *y);


int get_textures(t_cub *cub)
{
	int x = TILE_SIZE;
	int y = TILE_SIZE;
	//while i < 4
		//ft_load_images(cub, cub->textures[i]); /// < trocar para isso;
		// dps fazer a ft_free_load_images;
	if (!ft_load_images(cub, &cub->textures[NORTH], &x, &y))
	{
		printf("error loading image north texture\n");
		//FREE ONLY map
		return (0);
	}
	if (!ft_load_images(cub, &cub->textures[SOUTH], &x, &y))
	{
		printf("error loading image south texture\n");

		//ft_free textures
		return (0);
	}
	if (!ft_load_images(cub, &cub->textures[EAST], &x, &y))
	{
		printf("error loading image east texture\n");

		//ft_free textures
		return (0);
	}
	if (!ft_load_images(cub, &cub->textures[WEST], &x, &y))
	{
		printf("error loading image west texture\n");

		//ft_free textures
		return (0);
	}

	return (1);
}
int	ft_load_images(t_cub *cub, t_image *image, int *x, int *y)
{
	if (!image->path)
		return (0);
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			image->path, x, y);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, \
			&image->bits_per_pixel, &image->line_length, \
			&image->endian);
	return (1);
}
