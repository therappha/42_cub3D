/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:32:57 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/27 20:32:34 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	drawmap(t_cub *cub)
{
	float	drawx;
	for (int y = 0; cub->map[y]; y++)
	{
		for (int x = 0; cub->map[y][x]; x++)
		{
			drawx = x * (TILE_SIZE  * SCALE) -  cub->player.pos.x * (TILE_SIZE * SCALE) + SCREEN_SIZE_X / 2;
			if (cub->map[y][x] == '1')
				drawtexture(cub, (t_point){drawx, y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->ground, SCALE);
			if (cub->map[y][x] == 'B')
				drawtexture(cub, (t_point){drawx , y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->brick, SCALE);
			if (cub->map[y][x] == 'P')
				drawtexture(cub, (t_point){drawx , y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->powerup, SCALE);

		}
	}
}

