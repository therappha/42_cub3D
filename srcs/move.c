/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:55:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/27 22:01:36 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


float move_towards(float start, float goal, float step);

void	move(t_cub *cub)
{
	float	ground = SCREEN_SIZE_Y - (TILE_SIZE * SCALE * 3);
	//gravity
	if (cub->player.pos.y * TILE_SIZE * SCALE < ground - 1)
	{
		cub->is_on_ground = false;
		cub->player.velocity.y += GRAVITY * cub->delta;
	}
	else
	{
		cub->player.velocity.y = 0;
		cub->is_on_ground = true;
	}
	if (cub->jump && cub->is_on_ground)
	{
		cub->player.velocity.y = -JUMP_SPEED;
		cub->jump = false;
	}

	if (cub->player.direction.x != 0)
	{
		cub->player.velocity.x += cub->player.direction.x * ACCEL * cub->delta;
		cub->player.velocity.x = clamp(cub->player.velocity.x, -MAX_SPEED, MAX_SPEED);
	}
	else if (fabs(cub->player.velocity.x) > 0)
	{
		if (cub->player.velocity.x > 0)
			cub->player.velocity.x = move_towards(cub->player.velocity.x, 0, FRICTION * cub->delta);
		else if (cub->player.velocity.x < 0)
		{
			cub->player.velocity.x = move_towards(cub->player.velocity.x, 0, FRICTION * cub->delta);
		}
	}
	else
		cub->player.velocity.x = 0;

	//cub->player.pos.x += cub->player.velocity.x * cub->delta;
	//cub->player.pos.y += cub->player.velocity.y * cub->delta;

	cub->player.pos.x += cub->player.velocity.x * cub->delta;
	cub->player.pos.y += cub->player.velocity.y * cub->delta;

}

float move_towards(float start, float goal, float step)
{
	if (start < goal)
		return (fminf(start + step, goal));
	else if (start > goal)
		return (fmaxf(start - step, goal));
	else
		return (start);
}

