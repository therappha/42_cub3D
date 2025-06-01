/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 16:02:23 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_image	*get_wall_text_from_direction(t_cub *cub, t_ray *ray)
{
	if (ray->ray_side == 0)
	{
		if (ray->rayX > 0)
			return (&cub->textures[WEST]);
		else
			return (&cub->textures[EAST]);
	}
	else
	{
		if (ray->rayY > 0)
			return (&cub->textures[NORTH]);
		else
			return (&cub->textures[SOUTH]);
	}
}

unsigned int	get_color(t_ray *ray, t_point texture)
{
	return (*(int *)((*ray->texture).addr + ((int)texture.y
			*(*ray->texture).line_length + ray->textX
			*((*ray->texture).bits_per_pixel / 8))));
}

void	drawtexture(t_cub *cub, t_point pos, t_point size, t_ray *ray)
{
	int		x;
	int		y;
	float	step;
	t_point	texture;

	x = 0;
	y = 0;
	texture.x = ray->textX;
	step = (float)ray->texture->y / (float)ray->wall_height;
	texture.y = (pos.y - HEIGHT / 2 + ray->wall_height / 2) * step;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			texture.y += step;
			texture.x = clamp(texture.x, 0, ray->texture->x - 1);
			texture.y = clamp(texture.y, 0, ray->texture->y - 1);
			ft_pixelput(&cub->image, pos.x + x, pos.y + y++,
				get_color(ray, texture));
		}
		x++;
	}
}

void	drawrect(t_image *image, t_point pos, t_point size, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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

void	drawbackground(t_cub *cub)
{
	t_point	size;

	size.x = WIDTH;
	size.y = HEIGHT / 2;
	drawrect(&cub->image, (t_point){0, 0}, (t_point){WIDTH, HEIGHT / 2},cub->ceiling_color);
	drawrect(&cub->image, (t_point){0, HEIGHT / 2}, (t_point){WIDTH, HEIGHT / 2}, cub->floor_color);

}
