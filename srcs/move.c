/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:55:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/23 20:26:46 by rafaelfe         ###   ########.fr       */
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
		cub->player.plane.x = -cub->player.camera.y * ((float)FOV / 100.0f);
		cub->player.plane.y = cub->player.camera.x * ((float)FOV / 100.0f);
	}
	if (cub->player.camerax == 1)
	{
		double oldDirX = cub->player.camera.x;
		cub->player.camera.x = cub->player.camera.x * cos(rot_speed) - cub->player.camera.y * sin(rot_speed);
		cub->player.camera.y = oldDirX * sin(rot_speed) + cub->player.camera.y * cos(rot_speed);
		cub->player.plane.x = -cub->player.camera.y * ((float)FOV / 100.0f);
		cub->player.plane.y = cub->player.camera.x * ((float)FOV / 100.0f);
	}
}

void	move(t_cub *cub)
{
	if (cub->player.direction.y == -1)
	{
		cub->player.pos.x += 5 * cub->player.camera.x * cub->delta;
		cub->player.pos.y += 5 * cub->player.camera.y * cub->delta;
		printf("player.pos.x = %f\n", cub->player.pos.x);
		printf("player.pos.y = %f\n", cub->player.pos.y);
	}
	if (cub->player.direction.y == 1)
	{
		cub->player.pos.x -= 5 * cub->player.camera.x * cub->delta;
		cub->player.pos.y -= 5 * cub->player.camera.y * cub->delta;
		printf("player.pos.x = %f\n", cub->player.pos.x);
		printf("player.pos.y = %f\n", cub->player.pos.y);
	}
}
