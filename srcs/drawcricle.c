/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawcricle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:39 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 19:09:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void drawCircle(t_cub *cub, int xc, int yc, int x, int y)
{
	ft_pixelput(&cub->image, xc+x, yc+y, 0x000000);
	ft_pixelput(&cub->image, xc-x, yc+y, 0x000000);
	ft_pixelput(&cub->image, xc+x, yc-y, 0x000000);
	ft_pixelput(&cub->image, xc-x, yc-y, 0x000000);
	ft_pixelput(&cub->image, xc+y, yc+x, 0x000000);
	ft_pixelput(&cub->image, xc-y, yc+x, 0x000000);
	ft_pixelput(&cub->image, xc+y, yc-x, 0x000000);
	ft_pixelput(&cub->image, xc-y, yc-x, 0x000000);
}

void circleBres(t_cub *cub, int xc, int yc, int r)
{

	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(cub, xc, yc, x, y);
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
		drawCircle(cub, xc, yc, x, y);
	}
}
