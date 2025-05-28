/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:49:29 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/28 18:57:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	animation_times(t_cub *cub)
{
	static float accumulator;
	accumulator += cub->delta;

	if (accumulator > 0.3)
	{
		cub->power_up_frames++;
		if (cub->power_up_frames > 2)
			cub->power_up_frames = 0;
		accumulator = 0;
	}

}
