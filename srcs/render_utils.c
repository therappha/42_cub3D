/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 12:01:35 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


t_image  *get_wall_color_from_direction(t_cub *cub, int side, float ray_x, float ray_y)
{
	if (side == 0)
	{
		if (ray_x > 0)
			return &cub->textures[WEST];
		else
			return &cub->textures[EAST];
	}
	else
	{
		if (ray_y > 0)
			return &cub->textures[NORTH];
		else
			return &cub->textures[SOUTH];
	}
}

void	drawtexture(t_cub *cub, t_point pos, t_point size, int textX, float wall_heigth, t_image *text)
{
	int	x = 0;
	int y = 0;
	int	color;
	float	step;
	t_point texture;

	texture.x = textX;
	step = text->y / wall_heigth;
	texture.y = (pos.y - SCREEN_SIZE_Y / 2 + wall_heigth / 2) * step;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			texture.y += step;
			texture.x = clamp(texture.x, 0, text->x - 1);
			texture.y = clamp(texture.y, 0, text->y - 1);
			color = *(int *)((*text).addr + ((int)texture.y * (*text).line_length + textX * ((*text).bits_per_pixel / 8)));
			ft_pixelput(&cub->image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

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
