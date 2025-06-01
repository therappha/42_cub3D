/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 16:01:51 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	update(t_cub *cub)
{
	calculate_delta(cub);
	move_camera(cub);
	move(cub);
	return (1);
}

int	renderer(t_cub *cub)
{
	drawbackground(cub);
	raycast(cub);
	if (cub->debug)
		debug_directions(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	if (cub->debug)
	{
		print_fps(cub);
	}
	return (1);
}

int	game_loop(t_cub *cub)
{
	update(cub);
	renderer(cub);
	return (1);
}
