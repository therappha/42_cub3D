/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawcricle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:39 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 13:27:38 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void circlebres(t_cub *cub, int xc, int yc, t_point pos)
{
	int	x;
	int	y;

	x = (int)pos.x;
	y = (int)pos.y;
	ft_pixelput(&cub->image, xc+x, yc+y, 0x000000);
	ft_pixelput(&cub->image, xc-x, yc+y, 0x000000);
	ft_pixelput(&cub->image, xc+x, yc-y, 0x000000);
	ft_pixelput(&cub->image, xc-x, yc-y, 0x000000);
	ft_pixelput(&cub->image, xc+y, yc+x, 0x000000);
	ft_pixelput(&cub->image, xc-y, yc+x, 0x000000);
	ft_pixelput(&cub->image, xc+y, yc-x, 0x000000);
	ft_pixelput(&cub->image, xc-y, yc-x, 0x000000);
}

void drawcircle(t_cub *cub, int xc, int yc, int r)
{
	int	x;
	int	y;
	int	d;
	t_point	drawpos;

	x = 0;
	y = r;
	d = 3 - 2 * r;
	drawpos = (t_point){x, y};
	circlebres(cub, xc, yc, drawpos);
	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		x++;
		drawpos = (t_point){x, y};
		circlebres(cub, xc, yc, drawpos);
	}
}
