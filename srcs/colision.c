/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:44:23 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/05/31 19:39:14 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	get_colision(t_point mv, t_cub *cub)
{
	float	try_x;
	float	try_y;
	float	length;
	float	vel;

	length = sqrt((mv.x * mv.x) + (mv.y * mv.y));
	vel = MOVE_SPEED * cub->running;
	if (length != 0)
	{
		mv.x /= length;
		mv.y /= length;
		try_x = cub->player.pos.x + mv.x * vel * cub->delta;
		if (cub->map[(int)(cub->player.pos.y)][(int)(try_x + mv.x * F)] != '1')
			cub->player.pos.x = try_x;
		try_y = cub->player.pos.y + mv.y * vel * cub->delta;
		if (cub->map[(int)(try_y + mv.y * F)][(int)(cub->player.pos.x)] != '1')
			cub->player.pos.y = try_y;
	}
}
