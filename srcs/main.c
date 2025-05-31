/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
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
		cub->ceiling_color == -1 || cub->floor_color == -1)
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
	if (cub.error)
	{
		free_all(&cub);
		printf("ops, someting went wrong!\n");
		return (0);
	}
	init_window(&cub);
	if (!get_textures(&cub))
		return (0);
	printf("map is:\n");
	for (int i = 0; cub.map[i]; i++)
	{
		printf("%s\n", cub.map[i]);
		cub.map_height++;
	}

	cub.map_width = ft_strlen(cub.map[0]);
	get_player_pos(&cub);
	mlx_hook(cub.win_ptr, DestroyNotify, (1L<<17), free_displays, &cub);
	mlx_hook(cub.win_ptr, 02, (1L<<0), key_pressed, &cub);
	mlx_hook(cub.win_ptr, 03, (1L<<1), key_released, &cub);
	mlx_loop_hook(cub.mlx_ptr, game_loop, &cub);
	mlx_loop(cub.mlx_ptr);
}



