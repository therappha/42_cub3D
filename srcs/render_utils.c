/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 17:11:38 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	drawrect(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			ft_pixelput(image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

t_image  *get_wall_color_from_direction(t_cub *cub, int side, float ray_x, float ray_y)
{
	if (side == 0)
	{
		if (ray_x > 0)
			return &cub->west_texture;
		else
			return &cub->east_texture;
	}
	else
	{
		if (ray_y > 0)
			return &cub->north_texture;
		else
			return &cub->south_texture;
	}
}
