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

t_point	get_camera(t_cub *cub, char c)
{
	t_point	camera_dir;

	if (c == 'N')
	{
		camera_dir = (t_point){0, -1};
	}
	else if (c == 'S')
	{
		camera_dir =(t_point){0, 1};
	}
	else if (c == 'E')
	{
		camera_dir = (t_point){1, 0};
	}
	else if (c == 'W')
	{
		camera_dir = (t_point){-1, 0};
	}
	cub->player.plane.x = camera_dir.x * (float)(FOV / 100);
	cub->player.plane.y = camera_dir.y * (float)(FOV / 100);
	return (camera_dir);
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
			if (ft_strchr("NSEW", cub->map[y][x]))
			{
				cub->player.pos.x = x;
				cub->player.pos.y = y;
				cub->player.camera = get_camera(cub, cub->map[y][x]);
			}
			x++;
		}
		y++;
	}
}

void get_textures(t_cub *cub)
{
	int x = 64;
	int y = 64;


	cub->north_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/north.xpm", &x, &y);
	cub->north_texture.addr = mlx_get_data_addr(cub->north_texture.img, \
			&cub->north_texture.bits_per_pixel, &cub->north_texture.line_length, \
			&cub->north_texture.endian);
	cub->east_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/east.xpm", &x, &y);
	cub->east_texture.addr = mlx_get_data_addr(cub->east_texture.img, \
			&cub->east_texture.bits_per_pixel, &cub->east_texture.line_length, \
			&cub->east_texture.endian);
	cub->west_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/west.xpm", &x, &y);
	cub->west_texture.addr = mlx_get_data_addr(cub->west_texture.img, \
			&cub->west_texture.bits_per_pixel, &cub->west_texture.line_length, \
			&cub->west_texture.endian);
	cub->south_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/south.xpm", &x, &y);
	cub->south_texture.addr = mlx_get_data_addr(cub->south_texture.img, \
			&cub->south_texture.bits_per_pixel, &cub->south_texture.line_length, \
			&cub->south_texture.endian);

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
	init_window(&cub);
	get_textures(&cub);
	ft_load_map(av[1], &cub);
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



