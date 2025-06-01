/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:15:22 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 16:14:29 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	start_game(t_cub *cub)
{
	mlx_hook(cub->win_ptr, DestroyNotify, (1L << 17), free_displays, cub);
	mlx_hook(cub->win_ptr, 02, (1L << 0), key_pressed, cub);
	mlx_hook(cub->win_ptr, 03, (1L << 1), key_released, cub);
	mlx_loop_hook(cub->mlx_ptr, game_loop, cub);
	mlx_loop(cub->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (0);
	if (!check_args(av[1]))
	{
		ft_putstr_fd("Error\n Could not read file!\n", 2);
		return (0);
	}
	cub_init(&cub);
	ft_load_map(av[1], &cub, 0, NULL);
	check_parser(&cub);
	check_map(&cub);
	init_window(&cub);
	if (cub.error)
	{
		free_all(&cub);
		printf("ops, someting went wrong!\n");
		return (0);
	}
	if (!get_textures(&cub))
		return (0);
	get_player_pos(&cub);
	start_game(&cub);
}
