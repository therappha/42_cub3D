/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/26 13:00:32 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void get_textures(t_cub *cub)
{
	int x = 64;
	int y = 64;


	cub->north_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/north.xpm", &x, &y);
	cub->north_texture.addr = mlx_get_data_addr(cub->north_texture.img, \
			&cub->north_texture.bits_per_pixel, &cub->north_texture.line_length, \
			&cub->north_texture.endian);
	cub->east_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/east.xpm", &x, &y);
	cub->east_texture.addr = mlx_get_data_addr(cub->east_texture.img, \
			&cub->east_texture.bits_per_pixel, &cub->east_texture.line_length, \
			&cub->east_texture.endian);
	cub->west_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/west.xpm", &x, &y);
	cub->west_texture.addr = mlx_get_data_addr(cub->west_texture.img, \
			&cub->west_texture.bits_per_pixel, &cub->west_texture.line_length, \
			&cub->west_texture.endian);
	cub->south_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/south.xpm", &x, &y);
	cub->south_texture.addr = mlx_get_data_addr(cub->south_texture.img, \
			&cub->south_texture.bits_per_pixel, &cub->south_texture.line_length, \
			&cub->south_texture.endian);

}
