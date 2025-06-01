/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mouse_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:01:20 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 13:00:30 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_point get_mouse_position(t_cub *cub)
{
	int x = 0;
	int y = 0;

	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, \
			&x, &y);
	if (x > WIDTH)
		x = WIDTH;
	else if (x < 0)
		x = 0;
	if (y > HEIGHT)
		y = HEIGHT;
	else if (y < 0)
		y = 0;
	return ((t_point){x, y});
}
