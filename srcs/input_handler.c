/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:09:07 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 15:44:08 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_pressed(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		free_displays(cub);
	if (keysym == XK_Left)
		cub->player.camerax -= 1;
	if (keysym == XK_Right)
		cub->player.camerax += 1;
	if (keysym == XK_w || keysym == XK_W)
		cub->player.direction.y = clamp(cub->player.direction.y -1, -1, 1);
	if (keysym == XK_s || keysym == XK_S)
		cub->player.direction.y = clamp(cub->player.direction.y +1, -1, 1);
	if (keysym == XK_A || keysym == XK_a)
		cub->player.direction.x = clamp(cub->player.direction.x -1, -1, 1);
	if (keysym == XK_d || keysym == XK_D)
		cub->player.direction.x = clamp(cub->player.direction.x +1, -1, 1);
	if (keysym == XK_F3)
	{
		if (!cub->debug)
			cub->debug = true;
		else
			cub->debug = false;
	}
	if (keysym == XK_Shift_L)
	{
		cub->running = 1.0;
	}
	return (1);
}

int	key_released(int keysym, t_cub *cub)
{

	if (keysym == XK_Left)
		cub->player.camerax += 1;
	if (keysym == XK_Right)
		cub->player.camerax -= 1;
	if (keysym == XK_w || keysym == XK_W)
	{
		cub->player.direction.y = clamp(cub->player.direction.y + 1, -1, 1);
	}
	if (keysym == XK_s || keysym == XK_S)
	{
		cub->player.direction.y = clamp(cub->player.direction.y - 1, -1, 1);
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		cub->player.direction.x = clamp(cub->player.direction.x + 1, -1, 1);
	}
	if (keysym == XK_d || keysym == XK_D)
	{
		cub->player.direction.x = clamp(cub->player.direction.x - 1, -1, 1);
	}
	if (keysym == XK_Shift_L)
		cub->running = 1.0;
	return (1);
}
