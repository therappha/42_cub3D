/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:54:16 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 14:57:11 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_parser(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].path == NULL)
		{
			cub->error = true;
			return ;
		}
		i++;
	}
	if (!cub->found.ceiling || !cub->found.floor || !cub->found.map
		|| cub->ceiling_color == -1 || cub->floor_color == -1
		|| !cub->found.player)
		cub->error = true;
}

void	free_all(t_cub *cub)
{
	int	i;

	printf("freeing...\n");
	if (cub->map && cub->found.map)
	{
		printf("freeing map...\n");
		ft_free_arr(cub->map);
	}
	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].path)
			free(cub->textures[i].path);
		i++;
	}
}

void	copy_map(t_cub *cub)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (ft_strchr("10WENS", cub->map[y][x]))
			{
				cub->parsed_map[y + 1][x + 1] = cub->map[y][x];
			}
			x++;
		}
		y++;
	}
}

char	**malloc_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->parsed_map = ft_calloc(sizeof(char *), cub->map_height + 2);
	while (i < cub->map_height + 2)
	{
		cub->parsed_map[i] = ft_calloc(sizeof(char), cub->map_width + 3);
		ft_memset(cub->parsed_map[i], 'x', cub->map_width + 3);
		cub->parsed_map[i][cub->map_width + 2] = '\0';
		i++;
	}
	return (cub->parsed_map);
}

void	check_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->error)
		return ;
	cub->parsed_map = malloc_map(cub);
	if (!cub->parsed_map)
	{
		cub->error = true;
		return ;
	}
	copy_map(cub);
	flood_fill_caller(cub);
	if (cub->parsed_map)
	{
		while (i < cub->map_height + 2)
		{
			free(cub->parsed_map[i]);
			i++;
		}
		free(cub->parsed_map);
		cub->parsed_map = NULL;
	}
}
