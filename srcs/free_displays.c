/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_displays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:41:42 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 15:44:43 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_freesplit(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
}

void	free_images(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->textures[i].img);
		if (cub->textures[i].path)
			free(cub->textures[i].path);
		i++;
	}
	if (cub->image.img)
		mlx_destroy_image(cub->mlx_ptr, cub->image.img);
}

int	free_displays(t_cub *cub)
{
	mlx_loop_end((*cub).mlx_ptr);
	free_images(cub);
	if (cub->win_ptr)
		mlx_destroy_window((*cub).mlx_ptr, (*cub).win_ptr);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display((*cub).mlx_ptr);
		free((*cub).mlx_ptr);
	}
	if (cub->found.map)
		ft_freesplit((*cub).map);
	exit(1);
	return (0);
}
