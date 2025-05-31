/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 11:58:27 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_load_images(t_cub *cub, t_image *image);

int get_textures(t_cub *cub)
{
	int	i;

	i = 0;

	while (i < 4)
	{
		if (!ft_load_images(cub, &cub->textures[i]))
		{
			ft_printf("Error loading texture %d\n", i);
			free_displays(cub);
		}
		i++;
	}


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
