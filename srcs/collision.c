/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:44:23 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/07 20:36:53 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	get_collision(t_point mv, t_cub *cub)
{
	float	try_x;
	float	try_y;
	float	vel;
	int		new_x;
	int		new_y;

	vel = MOVE_SPEED * cub->running;
	try_x = cub->player.pos.x + mv.x * vel * cub->delta;
	try_y = cub->player.pos.y + mv.y * vel * cub->delta;
	new_x = (int)(try_x + mv.x * F);
	new_y = (int)(try_y + mv.y * F);
	//if (new_y >= 0 && new_y < cub->map_height + 2
	//	&& new_x >= 0 && new_x < cub->map_width + 2)
	//{
		//if (cub->map[(int)(cub->player.pos.y)][new_x] != '1')
			cub->player.pos.x = try_x;
		//if (cub->map[new_y][(int)(cub->player.pos.x)] != '1')
			cub->player.pos.y = try_y;
	//}
}
