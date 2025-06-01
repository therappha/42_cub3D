/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:15:22 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 17:16:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	start_game(t_cub *cub)
{
	init_window(cub);
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
		print_error("Error\nCould not read file!\n");
		return (0);
	}
	cub_init(&cub);
	ft_load_map(av[1], &cub, 0, NULL);
	check_parser(&cub);
	check_map(&cub);
	if (cub.error)
	{
		print_error("Error\nSomething whent wrong!\n");
		free_all(&cub);
		return (0);
	}
	init_mlx(&cub);
	if (!get_textures(&cub))
		return (0);
	get_player_pos(&cub);
	start_game(&cub);
}
