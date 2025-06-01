/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:26:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/01 17:09:10 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_window(t_cub *cub)
{
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3D");
}

void	init_mlx(t_cub *cub)
{
	(*cub).mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
		ft_putstr_fd("Error\nCould not initialize cub window!\n", 2);
	}
}
