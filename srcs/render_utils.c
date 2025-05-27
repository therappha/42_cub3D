/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/27 22:10:23 by rafaelfe         ###   ########.fr       */
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

void	drawtexture(t_cub *cub, t_point pos, t_point size, t_image *text, float scale)
{
	int	x = 0;
	int y = 0;
	unsigned int	color;
	t_point step = (t_point){0, 0};
	t_point texture;
	t_point original_size;

	original_size.x = size.x;
	original_size.y = size.y;
	size.x *= scale;
	size.y *= scale;
	texture.x = 0;
	texture.y = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			texture.x = x / scale;
			texture.y = y / scale;

			if (texture.x < 0 || texture.x > original_size.x || texture.y < 0 || texture.y > original_size.y)
				continue;
			color = *(int *)((*text).addr + ((int)texture.y * (*text).line_length + (int)texture.x * ((*text).bits_per_pixel / 8)));
			if (color == 0xFF000000)
			{
				y++;
				continue;
			}
			ft_pixelput(&cub->image, pos.x + x, pos.y + y++, color);
		}
		texture.x += step.x;
		x++;
	}
}

void	drawplayer(t_cub *cub, t_point pos, t_point size, t_image *text, float scale)
{
	int	x = 0;
	int y = 0;
	unsigned int	color;
	t_point texture;
	t_point original_size;
	int flip_h;
	original_size.x = size.x;
	original_size.y = size.y;
	size.x *= scale;
	size.y *= scale;
	if (cub->player.direction.x == -1)
	{
		flip_h = 1;
	}
	else
		flip_h = 0;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			if (flip_h)
				texture.x = (original_size.x - 1) - (x / scale);
			else
				texture.x = x / scale;
			texture.y = y / scale;

			if (texture.x < 0 || texture.x >= original_size.x || texture.y < 0 || texture.y >= original_size.y)
			{
				y++;
				continue;
			}
			color = *(int *)((text->addr) + ((int)texture.y * text->line_length + (int)texture.x * (text->bits_per_pixel / 8)));
			if (color == 0xFF000000)
			{
				y++;
				continue;
			}
			ft_pixelput(&cub->image, pos.x + x, pos.y + y, color);
			y++;
		}
		x++;
	}
}


