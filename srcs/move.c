/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:55:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/24 16:56:27 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	move_camera(t_cub *cub)
{
	float rot_speed;

	rot_speed = cub->delta * CAMERA_SPEED;
	if (cub->player.camerax == -1)
	{
		double oldDirX = cub->player.camera.x;
		cub->player.camera.x = cub->player.camera.x * cos(-rot_speed) - cub->player.camera.y * sin(-rot_speed);
		cub->player.camera.y = oldDirX * sin(-rot_speed) + cub->player.camera.y * cos(-rot_speed);
	}
	if (cub->player.camerax == 1)
	{
		double oldDirX = cub->player.camera.x;
		cub->player.camera.x = cub->player.camera.x * cos(rot_speed) - cub->player.camera.y * sin(rot_speed);
		cub->player.camera.y = oldDirX * sin(rot_speed) + cub->player.camera.y * cos(rot_speed);
	}
	cub->player.plane.x = -cub->player.camera.y * ((float)FOV / 100.0f);
	cub->player.plane.y = cub->player.camera.x * ((float)FOV / 100.0f);
}

void	move(t_cub *cub)
{
	t_point	move;

	move = (t_point){0, 0};
	if (cub->player.direction.y == -1)
	{
		move.x += cub->player.camera.x;
		move.y += cub->player.camera.y;
	}
	if (cub->player.direction.y == 1)
	{
		move.x -= cub->player.camera.x;
		move.y -= cub->player.camera.y;
	}
	if (cub->player.direction.x == -1)
	{
		move.x -= cub->player.plane.x;
		move.y -= cub->player.plane.y;
	}
	if (cub->player.direction.x == 1)
	{
		move.x += cub->player.plane.x;
		move.y += cub->player.plane.y;
	}
	move = normalize(move);
	cub->player.pos.x += move.x * MOVE_SPEED * cub->delta;
	cub->player.pos.y += move.y * MOVE_SPEED * cub->delta;
}
