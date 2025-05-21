/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:55:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 18:57:51 by rafaelfe         ###   ########.fr       */
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
}
