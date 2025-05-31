/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:03:20 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 19:35:24 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	cub_init(t_cub *cub)
{
	int i = 0;

	while (i < 4)
	{
		cub->textures[i].path = NULL;
		cub->textures[i++].img = NULL;
	}
	cub->fd = 0;
	cub->image.img = NULL;
	cub->player.direction = (t_point){0, 0};
	cub->player.pos = (t_point){0, 0};
	cub->player.plane = (t_point){0, 0};
	cub->player.camera = (t_point){0, 0};
	cub->player.camerax = 0;
	cub->map = NULL;
	cub->parsed_map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->delta = 0;
	cub->last_frame_time = get_time();
	cub->found.floor = false;
	cub->found.ceiling = false;
	cub->found.player = false;
	cub->found.map = false;
	cub->debug = false;
	cub->fps_string = NULL;
	cub->fps = 0;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->running = 1.0;
}

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
				cub->player.pos.x = x + 0.5f;
				cub->player.pos.y = y + 0.5f;
				cub->player.camera = get_camera(cub, cub->map[y][x]);
			}
			x++;
		}
		y++;
	}
}
