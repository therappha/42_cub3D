/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:15:22 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/05/31 22:04:54 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

//	player.plane.x = -player.camera.y * 0.50;
//	player.plane.y = player.camera.x * 0.50;

void	check_parser(t_cub *cub)
{
	int	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].path == NULL)
		{
			cub->error = true;
			return ;
		}
		i++;
	}
	if (!cub->found.ceiling || !cub->found.floor || !cub->found.map ||
		cub->ceiling_color == -1 || cub->floor_color == -1
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
	for (i = 0; i < 4; i++)
	{
		if (cub->textures[i].path)
			free(cub->textures[i].path);
	}
}

void	copy_map(t_cub *cub)
{
	int	y;
	int	x;
	char **temp;

	temp = cub->parsed_map;
	x = 0;
	y = 0;
	while(cub->map[y])
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
		//cub->parsed_map[y + 2][x + 2] = '\0';
		y++;
	}
	for (int i = 0; i < cub->map_height + 2; i++)
	{
		//printf("%s\n", cub->parsed_map[i]);
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
	return cub->parsed_map;
}
void	check_map(t_cub *cub)
{
	if (cub->error)
		return;
	cub->parsed_map = malloc_map(cub);
	if (!cub->parsed_map)
	{
		cub->error = true;
		return ;
	}
	copy_map(cub);
	flood_fill_caller(cub);
}
int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (0);
	if (!check_args(av[1]))
	{
		ft_printf("Error, Could not read file!\n");
		return (0);
	}
	cub_init(&cub);
	ft_load_map(av[1], &cub);
	check_parser(&cub);
	check_map(&cub);
	if (cub.error)
	{
		free_all(&cub);
		printf("ops, someting went wrong!\n");
		return (0);
	}
	init_window(&cub);
	if (!get_textures(&cub))
		return (0);
	get_player_pos(&cub);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y, "cub3d");
	mlx_hook(cub.win_ptr, DestroyNotify, (1L<<17), free_displays, &cub);
	mlx_hook(cub.win_ptr, 02, (1L<<0), key_pressed, &cub);
	mlx_hook(cub.win_ptr, 03, (1L<<1), key_released, &cub);
	mlx_loop_hook(cub.mlx_ptr, game_loop, &cub);
	mlx_loop(cub.mlx_ptr);
}
