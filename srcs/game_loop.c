/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/28 19:15:02 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	drawplayer(t_cub *cub, t_point pos, t_point size, t_image *text, float scale);

int	update(t_cub *cub)
{
	calculate_Delta(cub);
	move(cub);
	animation_times(cub);
	return (1);
}

int	renderer(t_cub *cub)
{
	memcpy(cub->image.addr, cub->background.addr, cub->background.line_length * SCREEN_SIZE_Y );
	drawmap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	return (1);
}

int	game_loop(t_cub *cub)
{
	update(cub);
	renderer(cub);
	return (1);
}
