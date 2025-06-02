/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:27:53 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 16:33:57 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	map_dup(t_cub *cub)
{
	int	y;

	y = 0;
	ft_free_arr(cub->map);
	cub->map = ft_calloc(sizeof(char *), (cub->map_height + 3));
	if (!cub->map)
		return ;
	while (y < cub->map_height + 2)
	{
		cub->map[y] = ft_strdup(cub->parsed_map[y]);
		if (!cub->map[y])
		{
			while (--y >= 0)
				free(cub->map[y]);
			free(cub->map);
			return ;
		}
		y++;
	}
	cub->map[y] = NULL;
}
