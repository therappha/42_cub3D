/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:48:48 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 16:13:38 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	print_fps(t_cub *cub)
{
	cub->fps_string = ft_itoa((int)cub->fps);
	mlx_string_put(cub->mlx_ptr, cub->win_ptr, 10, 10, 0xFFFFFF,
		cub->fps_string);
	free(cub->fps_string);
}

void	debug_directions(t_cub *cub)
{
	t_point	normalized_player;

	normalized_player = normalize(cub->player.direction);
	drawline(cub, (t_point){WIDTH / 4, HEIGHT - (HEIGHT / 4)},
		(t_point){WIDTH / 4 + normalized_player.x * CIRCLE_SIZE,
		HEIGHT - (HEIGHT / 4) + normalized_player.y * CIRCLE_SIZE});
	drawcircle(cub, WIDTH / 4, HEIGHT - (HEIGHT / 4), CIRCLE_SIZE + 1);
	drawcircle(cub, WIDTH / 4, HEIGHT - (HEIGHT / 4), CIRCLE_SIZE);
	drawline(cub, (t_point){WIDTH - WIDTH / 4, HEIGHT - (HEIGHT / 4)},
		(t_point){WIDTH - WIDTH / 4 + cub->player.camera.x * CIRCLE_SIZE,
		HEIGHT - (HEIGHT / 4) + cub->player.camera.y * CIRCLE_SIZE});
	drawcircle(cub, WIDTH - WIDTH / 4, HEIGHT - (HEIGHT / 4), CIRCLE_SIZE);
	drawcircle(cub, WIDTH - WIDTH / 4, HEIGHT - (HEIGHT / 4), CIRCLE_SIZE + 1);
}
