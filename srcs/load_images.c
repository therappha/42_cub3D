/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 16:01:46 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_load_images(t_cub *cub, t_image *image);

int	get_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!ft_load_images(cub, &cub->textures[i]))
		{
			ft_putstr_fd("Error\nFailed to load textures\n", 2);
			free_displays(cub);
		}
		i++;
	}
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	if (!cub->image.img)
	{
		ft_putstr_fd("Error\nCould not start game image\n", 2);
		free_displays(cub);
	}
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bits_per_pixel,
			&cub->image.line_length, &(cub->image.endian));
	return (1);
}

int	ft_load_images(t_cub *cub, t_image *image)
{
	if (!image->path)
		return (0);
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			image->path, &image->x, &image->y);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, \
			&image->bits_per_pixel, &image->line_length, \
			&image->endian);
	return (1);
}
