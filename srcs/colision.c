/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:44:23 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/05/31 13:07:30 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	get_colision(t_point mv, t_cub *cub)
{
	float	try_x;
	float	try_y;
	float	length;

	length = sqrt((mv.x * mv.x) + (mv.y * mv.y));
	if (length != 0)
	{
		mv.x /= length;
		mv.y /= length;
		try_x = cub->player.pos.x + mv.x * MOVE_SPEED * cub->delta;
		if (cub->map[(int)(cub->player.pos.y)][(int)(try_x + mv.x * F)] != '1')
			cub->player.pos.x = try_x;
		try_y = cub->player.pos.y + mv.y * MOVE_SPEED * cub->delta;
		if (cub->map[(int)(try_y + mv.y * F)][(int)(cub->player.pos.x)] != '1')
			cub->player.pos.y = try_y;
	}
}
