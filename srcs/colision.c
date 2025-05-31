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

void	get_colision(t_point move, t_cub *cub)
{

float try_x;
float try_y;
float length;

length = sqrt((move.x * move.x) + (move.y * move.y));
if (length != 0)
{
	move.x /= length;
	move.y /= length;

	try_x = cub->player.pos.x + move.x * MOVE_SPEED * cub->delta;
	if (cub->map[(int)(cub->player.pos.y)][(int)(try_x + move.x * 0.1f)] != '1')
		cub->player.pos.x = try_x;

	try_y = cub->player.pos.y + move.y * MOVE_SPEED * cub->delta;
	if (cub->map[(int)(try_y + move.y * 0.1f)][(int)(cub->player.pos.x)] != '1')
		cub->player.pos.y = try_y;
}

}
