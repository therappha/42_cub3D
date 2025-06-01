/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:01:43 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 15:47:43 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	calculate_delta(t_cub *cub)
{
	static float	accumulator;
	static int		local_fps;

	local_fps++;
	cub->delta = (get_time() - cub->last_frame_time) / 1000.0f;
	accumulator += cub->delta;
	cub->last_frame_time = get_time();
	if (accumulator >= 1.0f)
	{
		cub->fps = local_fps;
		local_fps = 0;
		accumulator = 0;
	}
}
