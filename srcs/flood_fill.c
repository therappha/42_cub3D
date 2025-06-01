/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:22:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 13:39:39 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	flood_fill(t_cub *cub, int x, int y)
{
	if (cub->error)
		return ;
	if (x < 0 || y < 0 || x > cub->map_width + 2 || y > cub->map_height + 2
		|| cub->parsed_map[y][x] == 'F')
		return ;
	if (!ft_strchr("NSEW0", cub->parsed_map[y][x]))
	{
		if (cub->parsed_map[y][x] == 'x')
		{
			cub->parsed_map[y][x] = 'F';
			cub->error = true;
			return ;
		}
		return ;
	}
	cub->parsed_map[y][x] = 'F';
	flood_fill(cub, x + 1, y);
	flood_fill(cub, x - 1, y);
	flood_fill(cub, x, y + 1);
	flood_fill(cub, x, y - 1);
}

void	flood_fill_caller(t_cub *cub)
{
	int	x;
	int	y;

	y = 1;
	while (y < cub->map_height + 2)
	{
		x = 1;
		while (x < cub->map_width + 2)
		{
			if (ft_strchr("NSEW0", cub->parsed_map[y][x]) != NULL)
			{
				flood_fill(cub, x, y);
				if (cub->error)
					return ;
			}
			x++;
		}
		y++;
	}
}
