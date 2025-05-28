/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:32:57 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/28 19:53:32 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	drawmap(t_cub *cub)
{
	float	drawx;
	float	startingx;
	float 	endingx;

	startingx = cub->player.pos.x - 16;
	startingx = clamp(startingx, 0, cub->map_width);
	endingx = cub->player.pos.x + 16;
	endingx = clamp(endingx, 0, cub->map_width);


	for (int y = 0; cub->map[y]; y++)
	{
		for (int x = startingx; x < endingx; x++)
		{
			drawx = x * (TILE_SIZE  * SCALE) -  cub->player.pos.x * (TILE_SIZE * SCALE) + SCREEN_SIZE_X / 2;
			if (cub->map[y][x] == '1')
				drawtexture(cub, (t_point){drawx, y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->ground, SCALE);
			if (cub->map[y][x] == 'B')
				drawtexture(cub, (t_point){drawx , y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->brick, SCALE);
			if (cub->map[y][x] == 'P')
				drawtexture(cub, (t_point){drawx , y * (TILE_SIZE * SCALE)},  (t_point){16, 16}, &cub->powerup[cub->power_up_frames], SCALE);
		}
	}
	drawplayer(cub, (t_point){SCREEN_SIZE_X / 2, cub->player.pos.y * (TILE_SIZE * SCALE)}, (t_point){TILE_SIZE, TILE_SIZE}, &cub->mario, SCALE);

}

