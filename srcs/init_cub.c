/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:03:20 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/27 17:01:57 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	cub_init(t_cub *cub)
{
	cub->fd = 0;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->delta = 0;
	cub->last_frame_time = get_time();
}



void	get_player_pos(t_cub *cub)
{
	int x = 0;
	int	y = 0;

	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (ft_strchr("M", cub->map[y][x]))
			{
				cub->player.pos.x = x;
				cub->player.pos.y = y;
			}
			x++;
		}
		y++;
	}
}
